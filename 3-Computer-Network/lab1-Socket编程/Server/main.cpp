#include "mainwindow.h"
#include <QApplication>
#include <QCryptographicHash>
#include "lock.h"
#include "gg.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    lock l;
    QString c = QString("hahahaha\nhahaha我\n你");
    QString b = l.encryption(c);
    QString s= l.Deciphering(b);
    std::cout <<s.toStdString() << std::endl;
    w.show();

    return a.exec();
}
