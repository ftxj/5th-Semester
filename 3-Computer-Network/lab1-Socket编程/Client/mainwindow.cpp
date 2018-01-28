#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globalvar.h"
#include <QTextEdit>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_md(MainDialog* d){
    mD = d;
}

void MainWindow::on_pushButton_login_clicked(){
    std::string username = ui->lineEdit_username->text().toStdString();
    std::string password = ui->lineEdit_password->text().toStdString();
    pconnectedSocket = new ClientSocket(this);
    pconnectedSocket->bind();
    pconnectedSocket->connect_server();
    pconnectedSocket->send("log_in");
    pconnectedSocket->send(username + "#" + password);
    std::string verify = pconnectedSocket->recv()[0];
    if(verify == "1"){
        mD->self_id = username;
        pconnectedSocket->send("1");
        emit do_log_in(pconnectedSocket);
        emit display(3);
    }
    else{
       QMessageBox::information(this, "info", "fail");
    }
}

void MainWindow::on_pushButton_SIgnUp_clicked()
{
    emit display(2);
}

void MainWindow::on_pushButton_findPWD_clicked()
{
    emit display(1);
}
