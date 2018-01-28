#include "maindialog.h"
#include "bubble.h"
#include "ui_maindialog.h"
#include <QPushButton>
#include <QProgressBar>
#include <QString>
#include <QLabel>
#include <QObject>
#include <QListWidgetItem>
#include "formattime.h"
#include "personlist.h"
#include "udpFileTrans.h"
#include "udpfiletrans_recv.h"
#include <QFileDialog>
MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    ui->lable_speed->hide();
}


MainDialog::~MainDialog()
{
    delete ui;
}


void MainDialog::PrintWarning(std::string s){
    QMessageBox::warning(this, "warning", s.c_str());
}

void MainDialog::display_old_msg(){
    ui->bubbl_widget->clear();

    if(IdtoFrd[chating_id].friendinfoMsg.size() != IdtoFrd[chating_id].friendtimeMsg.size()
            ||IdtoFrd[chating_id].mytimeMsg.size() != IdtoFrd[chating_id].myinfoMsg.size()){
        PrintWarning("error in msg time size and msg size");
        return;
    }
    formatTime last_t;

    auto timei = IdtoFrd[chating_id].friendtimeMsg.begin();
    auto endi = IdtoFrd[chating_id].friendtimeMsg.end();
    auto timej = IdtoFrd[chating_id].mytimeMsg.begin();
    auto endj = IdtoFrd[chating_id].mytimeMsg.end();

    auto datai = IdtoFrd[chating_id].friendinfoMsg.begin();
    auto dataj = IdtoFrd[chating_id].myinfoMsg.begin();

    while(timei != endi || timej != endj){
        if(timei == endi || (timej != endj && timej->isearly(*timei))){
            if(timej->islater_than_one_day(last_t)){
                ui->bubbl_widget->addTime(timej->return_time_from_year().c_str());
            }
            else if(timej->islater_than_four_min(last_t)){
                ui->bubbl_widget->addTime(timej->return_time_from_hour().c_str());
            }
            last_t = *timej;
            ui->bubbl_widget->addItem((*dataj).c_str(), Right);
            dataj++;
            timej++;
        }
        else{
            if(timei->islater_than_one_day(last_t)){
                ui->bubbl_widget->addTime(timei->return_time_from_year().c_str());
            }
            else if(timei->islater_than_four_min(last_t)){
                ui->bubbl_widget->addTime(timei->return_time_from_hour().c_str());
            }
            last_t = *timei;
            ui->bubbl_widget->addItem((*datai).c_str(), Left);
            datai++;
            timei++;
        }
    }
}

void MainDialog::on_friendList_widget_itemClicked(QListWidgetItem *item)
{
    personItem *qw = ui->friendList_widget->return_personitem_from_listitem(item);

    std::string id = qw->name->text().toStdString();

    UserSocket* us = IdtoFrd[id].pus;
    if(chating_id != id){
        chating_id = id;
        display_old_msg();
    }
    if(IdtoFrd[id].pus->isConnected == false){
        std::vector<std::string> info;
        std::string dois = "|id|" + id;
        pconnetcedServerSocket->send(dois);
        while(info.size() < 3){
            std::vector<std::string> temp = pconnetcedServerSocket->recv();
            for(auto i = temp.begin(); i != temp.end(); ++i){
                info.push_back(*i);
            }
        }
        if(info[2] != "#end#"){
            PrintWarning("error when ask ip&port");
        }
        else if(info[1] != "not online"){
            std::string ip = info[0];
            int port = std::stoi(info[1]);

            IdtoFrd[id].ip = ip;
            IdtoFrd[id].port = port;
            us->bind();
            us->connect(port, ip);
            us->send(self_id);
            us->isConnected = true;

            chating_socket = *us;
            chating_id = id;
            std::thread userthread(thread_function_TCP_user, this, &IdtoFrd[id]);
            userthread.detach();
        }
    }

    chating_socket = *us;
    chating_id = id;
}

void MainDialog::on_send_button_clicked(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    formatTime t(*ltm);
    formatTime last_t = IdtoFrd[chating_id].last_send_or_recv;
    std::string text_str = ui->input_Edit->toPlainText().toStdString();

    if(text_str.empty()){
        QMessageBox::information(this, "注意", "不可以发送空内容");
    }
    else{
        ui->input_Edit->setPlainText("");
        if(t.islater_than_four_min(last_t)){
            ui->bubbl_widget->addTime(t.return_time_from_hour().c_str());
        }
        ui->bubbl_widget->addItem(text_str.c_str(), Right);

        IdtoFrd[chating_id].myinfoMsg.push_back(text_str);
        IdtoFrd[chating_id].mytimeMsg.push_back(t);
        IdtoFrd[chating_id].last_send_or_recv = t;
        set_IdLastMsg(chating_id, text_str);
        if(chating_socket.isConnected){
            chating_socket.send("|time|" + t.return_time_from_year());
            chating_socket.send("|text|" + text_str);
        }
        else{
            pconnetcedServerSocket->send("offline msg");
            pconnetcedServerSocket->send(chating_id);
            pconnetcedServerSocket->send("|time|" + t.return_time_from_year());
            pconnetcedServerSocket->send("|text|" + text_str);
            pconnetcedServerSocket->send("offline msg end");
        }
    }
}

void MainDialog::add_new_IdtoFrd(std::string &id, personItem* item){
    Myfriend temp;
    temp.id = id;
    temp.vec = item;
    temp.pus = new UserSocket();
    temp.pus->isConnected = false;
    temp.pus->parent = this;
    IdtoFrd[id] = temp;
}

void MainDialog::set_IdLastMsg(std::string &id, std::string &str){
    IdtoFrd[id].vec->set_last_msg(str);
}

void MainDialog::add_new_friend_button(std::string &id){
    QString name(id.c_str());
    QString last_msg = IdtoFrd[id].last_msg.c_str();
    QString Icon = ":images/psu.jpg";
    personItem* item = ui->friendList_widget->add_Friend_Button(name, last_msg, Icon);
    add_new_IdtoFrd(id, item);
}

void MainDialog::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainDialog::thread_function_TCP_user(Myfriend *mf){
    while(mf->pus->isConnected){
        std::vector<std::string> v = mf->pus->recv();
        formatTime last_t = mf->last_send_or_recv;

        for(auto i = v.begin(); i != v.end(); ++i){
            if(i->find("|text|") == 0){
                if(mf->id == chating_id){
                    ui->bubbl_widget->addItem((*i).substr((*i).find('|') + 6).c_str(), Left);
                }
                mf->friendinfoMsg.push_back((*i).substr((*i).find('|') + 6));
                mf->last_msg = *i;
                set_IdLastMsg(mf->id, *i);
            }
            else{
                std::string ss = (*i).substr((*i).find('|') + 6);
                formatTime tem(ss);
                if(mf->id == chating_id){
                    if(tem.islater_than_four_min(last_t)){
                        ui->bubbl_widget->addItem(tem.return_time_from_hour().c_str(), Left);
                    }
                }
                mf->last_send_or_recv = tem;
                last_t = tem;
                mf->friendtimeMsg.push_back(tem);
            }
        }
    }
}

void MainDialog::thread_recv_file(UserSocket* US, std::string s_id, std::string s_len, int tm_p){
    std::string id = s_id.substr((s_id).find('|') + 6);
    long filelen = std::stol(s_len.substr((s_len).find('|') + 6));
    rdt_recv::udpFileTrans_Recv rdtRecv;
    rdtRecv.get_fileLen(filelen);
    rdtRecv.get_port(tm_p);
    rdtRecv.begin();
}

void MainDialog::thread_function_TCP_listen(){
    std::string id;
    plistenedUserSocket->listen();
    plistenedUserSocket->isConnected = true;

    UserSocket* us = new UserSocket();
    while(plistenedUserSocket->isConnected){
        *us = plistenedUserSocket->accept();
        us->isConnected = true;
        std::vector<std::string> v = us->recv();
        if(v[0].find("|file|") == std::string::npos){
            id = v[0];
            IdtoFrd[id].ip = us->ip;
            if(id == chating_id){
                chating_socket = *us;
            }
            IdtoFrd[id].pus = us;
            Myfriend *userinfo = &IdtoFrd[id];
            std::thread userthread(thread_function_TCP_user, this, userinfo);
            userthread.detach();
        }
        else{
            while(v.size()!=2){
                std::vector<std::string> tt = us->recv();
                for(int i = 0; i < tt.size(); ++i){
                    v.push_back(tt[i]);
                }
            }
            unsigned short tm_p = 0;
            if(getAvaliablePort(tm_p) == true && tm_p != 0){
                std::thread recvThread(thread_recv_file, this, us, v[0], v[1], tm_p);
                recvThread.detach();
                Sleep(100);
                us->send("|ok|");
                us->send(std::to_string(tm_p));
            }
        }
    }
}

void MainDialog::do_login(ClientSocket* pS){
    pconnetcedServerSocket = pS;
    ui->friendList_widget->setFocusPolicy(Qt::NoFocus);
    ui->friendList_widget->setStyleSheet(
                "QListWidget{border:none; outline:0px; background:white; color:black;}"
                "QListWidget::Item{bordor:none; height:80px}"
                "QListWidget::Item:hover{background:darkGray;}"
                "QListWidget::item:selected{background:darkGray;}"
                               );
    enum Condition {start = 0, Msgbegin, friendslist, offlinebegin, offmsging,offmsgnum,
                      Msgend, firendslistend, offlineend, stop};
    Condition recvCondition = start;
    std::string name, friendid;
    int msgnum = 0;
    while(recvCondition != stop){
        std::vector<std::string> revStrings = pconnetcedServerSocket->recv();
        for(auto i = revStrings.begin(); i != revStrings.end(); ++i){
            std::string tmp = *i;
            switch(recvCondition){
                case start:{
                    if(tmp == "login message"){
                        recvCondition = Msgbegin;
                        break;
                    }
                    break;
                }
                case Msgbegin:{
                    if(tmp == "% friend list %"){
                         recvCondition = friendslist;
                         break;
                    }
                    break;
                }
                case friendslist:{
                    if(tmp == "% friend list end %"){
                        recvCondition = firendslistend;
                        break;
                    }
                    friendid = tmp.substr(0, tmp.length() - 1);
                    add_new_friend_button(friendid);
                    break;
                }
                case firendslistend:
                    if(tmp == "% Msg list %"){
                        recvCondition = offlinebegin;
                        break;
                    }
                    break;
                case offlinebegin:
                    name = tmp;
                    if(tmp == "% Msg list end %"){
                        recvCondition = offlineend;
                    }
                    else
                        recvCondition = offmsgnum;
                    break;
                case offmsgnum:
                    msgnum = std::stoi(tmp);
                    recvCondition = offmsging;
                    break;
                case offmsging:
                    if(msgnum == 0 && tmp == "% Msg list end %"){
                        recvCondition = offlineend;
                        break;
                    }
                    msgnum -= 1;
                    if(msgnum == 0){
                        recvCondition = offlinebegin;
                    }
                    else{
                        recvCondition = offmsging;
                    }
                    if(tmp != ""){
                        IdtoFrd[name].get_new_msg(tmp);
                    }
                    break;
                case offlineend:
                    if(tmp == "% login message end %"){
                        recvCondition = stop;
                    }
                default:
                    recvCondition = stop;
                    break;
            }
        }
    }
    plistenedUserSocket = new ListenSocket(this);
    pconnetcedServerSocket->send(std::to_string(plistenedUserSocket->get_port()));
    std::thread listenServer(thread_function_TCP_listen, this);
    listenServer.detach();
    resize(744, 520);
    //this->show();
}

void MainDialog::on_friendList_widget_clicked(const QModelIndex &index)
{

}

void MainDialog::on_pushButton_addFriend_clicked()
{
    std::string addName = ui->lineEdit_search->text().toStdString();
    if(addName != ""){
        pconnetcedServerSocket->send("add_friend");
        pconnetcedServerSocket->send(addName);
        std::string s = pconnetcedServerSocket->recv()[0];
        if(s == "1"){
            add_new_friend_button(addName);
        }
        else{
            QMessageBox::information(this, "info", "no user");
        }
    }
}

void MainDialog::thread_function_File_Send(std::string filename){
    rdt_send::UdpFileTrans* ptrans = new rdt_send::UdpFileTrans;

    ptrans->setFile(filename);
    long len = ptrans->getFileLen();

    total_bytes = len;
    now_bytes = 0;

    std::vector<std::string> info;
    std::string dois = "|id|" + chating_id;
    pconnetcedServerSocket->send(dois);
    while(info.size() < 3){
        std::vector<std::string> temp = pconnetcedServerSocket->recv();
        for(auto i = temp.begin(); i != temp.end(); ++i){
            info.push_back(*i);
        }
    }
    if(info[2] != "#end#"){
        PrintWarning("error when ask ip&port");
    }
    else if(info[1] != "not online"){
        std::string ip = info[0];
        int port = std::stoi(info[1]);
        IdtoFrd[chating_id].ip = ip;
        IdtoFrd[chating_id].port = port;
    }
    UserSocket newS;
    newS.bind();
    newS.connect(IdtoFrd[chating_id].port, IdtoFrd[chating_id].ip);
    newS.send("|file|" + (self_id));
    newS.send("|file|" + std::to_string(len));

    std::vector<std::string> v = newS.recv();
    while(v.size() != 2){
        std::vector<std::string> temp = newS.recv();
        for(auto i = temp.begin(); i != temp.end(); ++i){
            v.push_back(*i);
        }
    }
    if(v[0] == "|ok|"){
        int tm_p = std::stoi(v[1]);
        ptrans->setIpPort(IdtoFrd[chating_id].ip, tm_p);

        std::thread set_fuck_shit(set_now_bytes, this, &(ptrans->ack), len);
        ptrans->begin();
        set_fuck_shit.join();
    }
}

void MainDialog::set_now_bytes(long *x, long y){
    while(*x < y){
        Sleep(1000);
        now_bytes = *x;
    }
    now_bytes = y;
}

void MainDialog::set_bar(long *x, long y){
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(y);
    ui->progressBar->setValue(0);
    int last = 0;
    while(*x < y){
        Sleep(1000);
        std::string s = std::to_string((*x - last)/ 1e6);
        const QString ss = (s + "MB/s").c_str();
        last = *x;
        emit SetNum(*x);
        emit SetSpeedText(ss);
    }
    emit SetNum(y);
    emit SetSpeedText("success");
}

void MainDialog::on_file_send_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File打开文件"),"",tr("(*)"));
    if(filename.length() > 0){
        if(chating_socket.isConnected){
           connect(this, &MainDialog::SetNum, ui->progressBar, &QProgressBar::setValue, Qt::QueuedConnection);
           connect(this, &MainDialog::SetSpeedText, ui->lable_speed, &QLabel::setText, Qt::QueuedConnection);

           std::thread send_file_thread(thread_function_File_Send, this, filename.toStdString());
           send_file_thread.detach();

           std::thread set_now_bar(set_bar, this, &now_bytes, total_bytes);
           set_now_bar.detach();

           ui->progressBar->show();
           ui->lable_speed->setText("Waiting...");
           ui->lable_speed->show();
        }
    }
    return;
}

bool MainDialog::getAvaliablePort(unsigned short &p){
    bool result = true;
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(ADDR_ANY);
    int ret = bind(sock, (SOCKADDR*)&addr, sizeof addr);

    if (0 != ret) {
        result = false;
        closesocket(sock);
        return false;
    }
    struct sockaddr_in connAddr;
    int len = sizeof connAddr;
    ret = getsockname(sock, (SOCKADDR*)&connAddr, &len);

    if (0 != ret) {
        closesocket(sock);
        return false;
    }

    p = ntohs(connAddr.sin_port); // 获取端口号

    if (0 != closesocket(sock))
        result = false;
    return result;
}
