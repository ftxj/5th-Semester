#include "findpsw.h"
#include "ui_findpsw.h"
#include "globalvar.h"
findpsw::findpsw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findpsw)
{
    ui->setupUi(this);
}

findpsw::~findpsw()
{
    delete ui;
}

void findpsw::on_pushButton_clicked()
{
    std::string accontName = ui->lineEdit_accout->text().toStdString();
    std::string newpsw = ui->lineEdit_psw->text().toStdString();
    std::string ans = ui->lineEdit_ans->text().toStdString();
    std::string pro = std::to_string(ui->comboBox->currentIndex());
    pconnetcedServerSocket = new ClientSocket(this);
    pconnetcedServerSocket->bind();
    pconnetcedServerSocket->connect_server();
    pconnetcedServerSocket->send("find_psw");
    pconnetcedServerSocket->send(accontName + "#" + newpsw + "#" + pro + "#" + ans);
    std::vector<std::string> v = pconnetcedServerSocket->recv();
    if(v[0] == "true"){
        QMessageBox::information(this, "info", "success");
    }
    else{
        QMessageBox::information(this, "info", "fail");
    }
    emit display(0);
}

void findpsw::on_pushButton_2_clicked()
{
    emit display(0);
}
