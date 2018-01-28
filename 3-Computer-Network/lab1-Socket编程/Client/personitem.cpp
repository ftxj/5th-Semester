#include "personitem.h"

personItem::personItem(QWidget* parent) : QWidget(parent)
{
    initUI();
}

personItem::personItem(QWidget *parent, QString &id, QString &msg): QWidget(parent){
    initUI();
    name->setText(id);
    last_msg->setText(msg);
}

personItem::personItem(QWidget *parent, QString &ic, QString &id, QString &msg): QWidget(parent){
    initUI();
    name->setText(id);
    last_msg->setText(msg);
    headpath = ic;
}

personItem::~personItem(){
    delete head;
    delete name;
    delete last_msg;
}

bool personItem::set_last_msg(std::string &s){
    last_msg->setText(s.c_str());
    return true;
}

void personItem::initUI(){
    head = new QWidget(this);
    name = new QLabel(this);
    last_msg = new QLabel(this);

    head->setFixedSize(40, 40);
    head->move(7,7);

    QFont font;
    font.setFamily("Monospace");
    font.setPixelSize(20);
    font.setBold(true);
    font.setLetterSpacing(QFont::PercentageSpacing,100);
    name->setFont(font);
    name->move(60,7);

    QPalette color;
    color.setColor(QPalette::Text,Qt::red);
    last_msg->setPalette(color);
    last_msg->setFixedWidth(100);
    last_msg->move(60, 30);

    head->installEventFilter(this);
}

bool personItem::eventFilter(QObject *obj, QEvent *event){
    if(obj == head){
        if(event->type() == QEvent::Paint){
            QPainter painter(head);
            painter.drawPixmap(head->rect(), QPixmap(":images/psu.png"));
        }
    }
    return QWidget::eventFilter(obj, event);
}
