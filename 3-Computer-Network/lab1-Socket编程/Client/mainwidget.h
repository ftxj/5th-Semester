#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QStackedLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include "signup.h"
#include "findpsw.h"
#include "mainwindow.h"
#include "maindialog.h"

class mainWidget : public QWidget
{
     Q_OBJECT
public:
    explicit mainWidget(QWidget* parent = 0);
    ~mainWidget();
private:
    SignUp* sD;
    findpsw* fD;
    MainWindow* mW;
    MainDialog* mD;
    QStackedLayout *stackLayout;
    QVBoxLayout *mainLayout;
};

#endif // MAINWIDGET_H
