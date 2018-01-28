#-------------------------------------------------
#
# Project created by QtCreator 2017-10-10T12:51:53
#
#-------------------------------------------------

QT       += core gui




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
LIBS += -lws2_32
TARGET = Login
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    maindialog.cpp \
    ClientSocket.cpp \
    Basicsocket.cpp \
    Listensocketh.cpp \
    Usersocket.cpp \
    friendinfo.cpp \
    bubble.cpp \
    myapp.cpp \
    bubblelistprivate.cpp \
    formattime.cpp \
    personitem.cpp \
    personlist.cpp \
    signup.cpp \
    findpsw.cpp \
    mainwidget.cpp \
    udpFileTrans.cpp \
    udpfiletrans_recv.cpp



HEADERS += \
        mainwindow.h \
    maindialog.h \
    ClientSocket.h \
    Usersocket.h \
    Listensocket.h \
    BasicSocket.h \
    SelfManage.h \
    FriendInfo.h \
    globalvar.h \
    bubble.h \
    myapp.h \
    bubblelistprivate.h \
    iteminfo.h \
    formattime.h \
    personitem.h \
    personlist.h \
    signup.h \
    findpsw.h \
    mainwidget.h \
    udpFileTrans.h \
    udpfiletrans_recv.h

FORMS += \
        mainwindow.ui \
    maindialog.ui \
    signup.ui \
    findpsw.ui

RESOURCES += \
    images.qrc
