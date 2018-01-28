#ifndef MAINDIALOG_H
#define MAINDIALOG_H
#include <QDialog>
#include <QListView>
#include <QListWidget>
#include <QListWidgetItem>
#include <QProgressBar>
#include "FriendInfo.h"
#include "ClientSocket.h"
#include "Listensocket.h"
#include "Usersocket.h"
#include "FriendInfo.h"
#include "udpFileTrans.h"
namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();
    void set_now_bytes(long *x, long y);
    void do_login(ClientSocket* pconnetcedServerSocket);
    void on_pushButton_friends_clicked();
    void set_IdLastMsg(std::string &id, std::string &str);

    std::string self_id;
    long total_bytes = 0;
    long now_bytes = 0;
signals:
    void fileRecv_SendSize(int sum, int n);
    void SetNum(int x);
    void SetSpeedText(const QString s);
private slots:
    void on_send_button_clicked();
    void set_bar(long *x, long y);
    void on_friendList_widget_itemClicked(QListWidgetItem *item);

    void on_friendList_widget_clicked(const QModelIndex &index);

    void on_pushButton_addFriend_clicked();

    void on_file_send_clicked();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainDialog *ui;
    std::map<std::string, Myfriend> IdtoFrd;
    ClientSocket *pconnetcedServerSocket;
    ListenSocket *plistenedUserSocket;
    std::string chating_id;
    UserSocket chating_socket;



    void thread_function_File_Send(std::string filename);
    void thread_recv_file(UserSocket* US, std::string s_id, std::string s_len, int tm_p);
    bool getAvaliablePort(unsigned short &);
    void on_send_buttom_clicked();
    void thread_function_TCP_listen();
    void thread_function_TCP_user(Myfriend*);
    void get_new_message(std::string&, std::string&);
    void PrintWarning(std::string s);
    void display_old_msg();
    void add_new_friend_button(std::string &s);
    void add_new_IdtoFrd(std::string &id, personItem* item);
    void add_offsite_msg(std::string &s, std::vector<std::string> &v);

};

#endif // MAINDIALOG_H
