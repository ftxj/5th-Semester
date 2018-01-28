#ifndef PERSONLIST_H
#define PERSONLIST_H
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include "personitem.h"
class personList :public QListWidget
{
    Q_OBJECT
public:
    explicit personList(QWidget* person = 0);
    ~personList();

    personItem* add_Friend_Button(QString &id, QString &last_msg, QString &ic);
    personItem* return_personitem_from_listitem(QListWidgetItem*);
    int friend_num;
    QHBoxLayout* mainLayout;
};

#endif // PERSONLIST_H
