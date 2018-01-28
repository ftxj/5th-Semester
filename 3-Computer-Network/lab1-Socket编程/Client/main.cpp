#include "ClientSocket.h"
//#include "Listensocket.h"
//#include "Usersocket.h"
#include "globalvar.h"
#include "mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication MyApp(argc, argv);
    mainWidget w;
    w.show();
    return MyApp.exec();
}
