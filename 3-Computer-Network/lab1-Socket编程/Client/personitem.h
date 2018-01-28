#ifndef PERSONITEM_H
#define PERSONITEM_H
#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QPainter>

class personItem : public QWidget
{
    Q_OBJECT

public:
    explicit personItem(QWidget *parent = 0);
    personItem(QWidget *parent, QString &id, QString &msg);
    personItem(QWidget *parent, QString &ic, QString &id, QString &msg);
    ~personItem();

    void initUI();
    QWidget* head;
    QLabel* name;
    QLabel* last_msg;

    QString headpath;
    bool eventFilter(QObject *obj, QEvent *event);
    bool set_last_msg(std::string &s);
};

#endif // PERSONITEM_H
