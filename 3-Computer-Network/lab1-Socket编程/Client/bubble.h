#ifndef BUBBLE_H
#define BUBBLE_H
#include "iteminfo.h"
#include "bubblelistprivate.h"

class BubbleList: public QWidget
{
    Q_OBJECT

public:
    BubbleList(QWidget* parent = 0);
    ~BubbleList();
    void addItem(const QString& str, const int &orientation);
    void addTime(const QString& str);
    void clear();
    void render();

protected:
    QSize sizeHint() const{
        return QSize(SIZE_HINT);
    }

private:
    void initWgts();
    void initStgs();

private:
    QHBoxLayout* mainLayout;
    BubbleListPrivate* d;

};
#endif // BUBBLE_H
