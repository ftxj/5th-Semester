#include "personlist.h"

personList::personList(QWidget* person) : QListWidget(person){
    mainLayout = new QHBoxLayout(this);
    setLayout(mainLayout);
}
personList::~personList(){
    delete mainLayout;
}

personItem* personList::add_Friend_Button(QString &id, QString &last_msg, QString &ic){
    personItem *buddy = new personItem(this, ic, id, last_msg);
    QListWidgetItem *m_FrdItem = new QListWidgetItem(this);
    m_FrdItem->setSizeHint(QSize(53, 53));
    addItem(m_FrdItem);
    setItemWidget(m_FrdItem, buddy);
    return buddy;
}

personItem* personList::return_personitem_from_listitem(QListWidgetItem *item){
    return qobject_cast<personItem*>(itemWidget(item));
}
