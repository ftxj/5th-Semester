#include "bubble.h"
#include "myapp.h"
BubbleList::BubbleList(QWidget *parent) :
    QWidget(parent)
{
    initWgts();
    initStgs();
}

BubbleList::~BubbleList(){
    d->clear();
}

void BubbleList::initWgts(){
    mainLayout = new QHBoxLayout(this);
    d = new BubbleListPrivate(this);
    this->setMinimumWidth(300);
    mainLayout->addWidget(d);
    setLayout(mainLayout);
}

void BubbleList::initStgs(){
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
}


void BubbleList::addItem(const QString &str, const int &orientation){
    d->addItem(str, orientation);
}
void BubbleList::addTime(const QString& str){
    d->addTime(str);
}
void BubbleList::clear(){
    d->clear();
}

void BubbleList::render(){
    d->render();
}
