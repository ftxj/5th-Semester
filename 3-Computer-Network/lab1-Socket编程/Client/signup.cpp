#include "signup.h"
#include "ui_signup.h"
SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_clicked()
{
    std::string accontName = ui->lineEdit_accout->text().toStdString();
    std::string newpsw = ui->lineEdit_password->text().toStdString();
    std::string ans = ui->lineEdit_proAns->text().toStdString();
    std::string pro = std::to_string(ui->comboBox->currentIndex());
    pconnetcedServerSocket = new ClientSocket(this);
    pconnetcedServerSocket->bind();
    pconnetcedServerSocket->connect_server();
    pconnetcedServerSocket->send("sign_up");
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

void SignUp::on_pushButton_2_clicked()
{
    emit display(0);
}
