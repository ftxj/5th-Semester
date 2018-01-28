#include "mainwidget.h"

mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent)
{
    fD = new findpsw;
    mW = new MainWindow;
    sD = new SignUp;
    mD = new MainDialog;

    mW->get_md(mD);

    stackLayout = new QStackedLayout(this);
    stackLayout->addWidget(mW);
    stackLayout->addWidget(fD);
    stackLayout->addWidget(sD);
    stackLayout->addWidget(mD);

    connect(mW, &MainWindow::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(fD, &findpsw::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(sD, &SignUp::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(mW, &MainWindow::do_log_in, mD, &MainDialog::do_login);
    //mainLayout = new QVBoxLayout;
    //mainLayout->addLayout(stackLayout);
    setLayout(stackLayout);
    stackLayout->setCurrentIndex(0);
}

mainWidget::~mainWidget()
{

}
