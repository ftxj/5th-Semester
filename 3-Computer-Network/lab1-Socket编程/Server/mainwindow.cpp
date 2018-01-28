#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gg.h"
#include <thread>
#include "lock.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::thread do_it(run, this);
    do_it.detach();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_offline_msg(std::string self_id, std::string id, std::string t, std::string s) {
    ofstream fin;
    lock l;
    fin.open(gg::dataAddr + id + ".msg", ios::trunc);
    std::string st = "@";
    std::string stx = "!";
    std::string ss;
    ss += "#";
    ss += self_id;
    st += t;
    stx += s;

    cout << st << stx << ss << "oo" << endl;
    ss = l.encryption(ss.c_str()).toStdString();
    st = l.encryption(st.c_str()).toStdString();
    stx = l.encryption(stx.c_str()).toStdString();

    fin << ss << endl;
    fin << st << endl;
    fin << stx << endl;
    fin.close();
}

int MainWindow::findUser(std::string id) {
    std::ifstream fin;
    lock l;
    fin.open(gg::dataAddr + "all");
    std::string s;
    while (getline(fin, s)) {
        s = l.Deciphering(s.c_str()).toStdString();
        if(s != id){
            continue;
        }
        else{
            break;
        }
    }
    if (s == id) {
        return 1;
    }
    fin.close();
    return 0;
}

std::vector<std::string> MainWindow::split(std::string& src, std::string separate_character)
{
    std::vector<std::string> strs;
    int separate_characterLen = separate_character.size();
    int lastPosition = 0, index = -1;
    while (-1 != (index = src.find(separate_character, lastPosition)))
    {
        strs.push_back(src.substr(lastPosition, index - lastPosition));
        lastPosition = index + separate_characterLen;
    }
    std::string lastString = src.substr(lastPosition);
    if (!lastString.empty())
        strs.push_back(lastString);
    return strs;
}

void MainWindow::UserConnectedThread(UserSocket USocket) {
    std::vector<std::string> tempV;
    std::vector<std::string> recvinfo;
    std::string temp;
    int port;
    if (USocket.s == SOCKET_ERROR) {
        printf("Accept failed : %d", WSAGetLastError());
    }
    else {
        printf("accept success\n");
        recvinfo = USocket.recv();
        std::string s = recvinfo[0];
        if (s == "log_in") {
            if (recvinfo.size() == 1) {
                tempV = USocket.recv();
            }
            for (int i = 0; i < tempV.size(); ++i) {
                recvinfo.push_back(tempV[i]);
            }
            s = recvinfo[1];
            User user1(s.substr(0, s.find('#', 0)), s.substr(s.find('#', 0) + 1), USocket);
            if (user1.verify()) {
                USocket.send("1");
                std::string x = USocket.recv()[0];
                if (x != "1") {
                    return;
                }
                //printf("log success, welcome %s\n", USocket.ip.c_str());
                user1.dosign_in();
                std::vector<std::string> v = user1.Us.recv();
                user_ip_port_vector[user1.id] = make_pair(user1.Us.ip, std::stoi(v[0]));
                int rowIndex = ui->tableWidget->rowCount();
                ui->tableWidget->setRowCount(rowIndex + 1);

                cout << user1.id << " " << user1.Us.port << " " << user1.Us.ip << endl;
                QString s1 = std::to_string(rowIndex + 1).c_str();
                QString s2 = user1.id.c_str();
                QString s3 = user1.Us.ip.c_str();
                QString s4 = std::to_string(user1.Us.port).c_str();

                ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(QString(s1)));
                ui->tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(QString(s2)));
                ui->tableWidget->setItem(rowIndex, 2, new QTableWidgetItem(QString(s3)));
                ui->tableWidget->setItem(rowIndex, 3, new QTableWidgetItem(QString(s4)));

                while (true) {
                    recvinfo = USocket.recv();
                    if (recvinfo.empty()) {
                        break;
                    }
                    for(int i = 0; i < recvinfo.size(); ++i){
                        cout << recvinfo[i] << "\n";
                    }
                    if (recvinfo[0].find("|id|") != string::npos) {
                        cout << recvinfo[0] << endl;
                        temp = recvinfo[0].substr(recvinfo[0].find("|id|") + 4);
                        if ( user_ip_port_vector.find(temp) ==  user_ip_port_vector.end()) {
                            USocket.send("f");
                            USocket.send("not online");
                            USocket.send("#end#");
                        }
                        else {
                            printf("find id %s\n is ip %s port %d", temp.c_str(),  user_ip_port_vector[temp].first.c_str(),  user_ip_port_vector[temp].second);
                            USocket.send( user_ip_port_vector[temp].first);
                            USocket.send("" + to_string( user_ip_port_vector[temp].second));
                            USocket.send("#end#");
                        }
                    }
                    else if (recvinfo[0].find("offline msg") != string::npos) {
                        while(recvinfo.size() < 5){
                            vector<string> temp = USocket.recv();
                            for (auto i = temp.begin(); i != temp.end(); ++i) {
                                recvinfo.push_back(*i);
                            }
                        }
                        add_offline_msg(user1.id, recvinfo[1], recvinfo[2].substr(recvinfo[2].find_last_of('|') + 1),
                            recvinfo[3].substr(recvinfo[3].find_last_of('|') + 1));
                    }
                    else if (recvinfo[0].find("add_friend") != string::npos) {
                        while (recvinfo.size() < 2) {
                            vector<string> temp = USocket.recv();
                            for (auto i = temp.begin(); i != temp.end(); ++i) {
                                recvinfo.push_back(*i);
                            }
                        }
                        if (findUser(recvinfo[1]) == 1) {
                            user1.addFriend(recvinfo[1]);
                            USocket.send("1");
                        }
                        else {
                            USocket.send("-1");
                        }
                    }
                }
            }
            else {
                USocket.send("-1");
            }
        }
        else if (s == "sign_up") {
            if (recvinfo.size() == 1) {
                tempV = USocket.recv();
            }
            for (int i = 0; i < tempV.size(); ++i) {
                recvinfo.push_back(tempV[i]);
            }
            vector<string> split_str = split(recvinfo[1], "#");
            User newUser;
            newUser.addUser(split_str[0], split_str[1], split_str[2], split_str[3]);
            USocket.send("true");
        }
        else if (s == "find_psw") {
            if (recvinfo.size() == 1) {
                tempV = USocket.recv();
            }
            for (int i = 0; i < tempV.size(); ++i) {
                recvinfo.push_back(tempV[i]);
            }
            vector<string> split_str = split(recvinfo[1], "#");
            User newUser;
            newUser.setNewPsw(split_str[0], split_str[1], split_str[2], split_str[3]);
            USocket.send("true");
        }
    }
    USocket.kill();
    user_ip_port_vector.erase(USocket.id);
    cout << USocket.id << " is loyout" << endl;
    return;
}

void MainWindow::run(){
    ListenSocket LSocket;
    LSocket.bind();
    LSocket.listen();
    while (1) {
        UserSocket USocket = LSocket.accept();
        std::thread newConnect(UserConnectedThread, this, USocket);
        newConnect.detach();
    }
}
