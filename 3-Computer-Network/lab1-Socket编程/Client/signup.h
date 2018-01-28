#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "globalvar.h"
#include "ClientSocket.h"
namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT
protected:
    QSize sizeHint() const{
        return QSize(400,300);
    }
public:
    explicit SignUp(QWidget *parent = 0);
    ~SignUp();
signals:
    void display(int number);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SignUp *ui;
    ClientSocket* pconnetcedServerSocket;
};

#endif // SIGNUP_H
