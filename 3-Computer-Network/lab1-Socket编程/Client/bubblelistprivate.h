#ifndef BUBBLELISTPRIVATE_H
#define BUBBLELISTPRIVATE_H
#include "iteminfo.h"

class BubbleListPrivate : public QWidget
{
    Q_OBJECT

public:
    explicit BubbleListPrivate(QWidget *parent = 0);

public:
    void addItem(const QString& str, const int &orientation);
    void addTime(const QString& str);
    void calcGeo();
    void clear();
    void render();

protected:
    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *);
    void wheelEvent(QWheelEvent *);

private:
    void initVars();
    void initSettings();
    void wheelUp();
    void wheelDown();

private:
    void drawItems(QPainter* painter);

private:
    QVector<ItemInfo> m_IIVec;

    int m_currIndex;
    int m_VisibleItemCnt;
};

#endif // BUBBLELISTPRIVATE_H
