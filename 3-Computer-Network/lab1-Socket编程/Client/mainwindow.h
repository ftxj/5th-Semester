#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ClientSocket.h"
#include "Listensocket.h"
#include "Usersocket.h"
#include "findpsw.h"
#include "signup.h"
#include "maindialog.h"
#include "FriendInfo.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    QSize sizeHint() const{
        return QSize(400,300);
    }
public:
    explicit MainWindow(QWidget *parent = 0);
    void get_md(MainDialog *d);
    ~MainWindow();
signals:
    void display(int number);
    void do_log_in(ClientSocket*);
private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_SIgnUp_clicked();

    void on_pushButton_findPWD_clicked();

private:
    Ui::MainWindow *ui;
    ClientSocket* pconnectedSocket;
    MainDialog* mD;
};

#endif // MAINWINDOW_H
