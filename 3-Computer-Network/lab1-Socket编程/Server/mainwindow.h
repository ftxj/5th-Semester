#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <WinSock2.h>
#include <stdio.h>
#include <QMainWindow>
#include <fstream>
#include <thread>
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include "socketclass.h"
#include "user.h"
#include "datebase.h"
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    std::map<std::string, std::pair<std::string, int>> user_ip_port_vector;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void add_offline_msg(std::string self_id, std::string id, std::string t, std::string s);

    int findUser(std::string id);

    std::vector<std::string> split(std::string& src, std::string separate_character);

    void UserConnectedThread(UserSocket USocket);

    void run();
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
