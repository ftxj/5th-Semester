#ifndef ITEMINFO_H
#define ITEMINFO_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QTimer>
#include "myapp.h"

#define ITEM_START_ANGLE 270
#define ITEM_D_ANGLE 2
#define ITEM_D_ZOOMING_FACTOR 0.05
#define UPDATE_TIMER_INTERVAL 10 // ms
#define ITEM_COUNTER_TIMER_INTERVAL 200
#define SIZE_HINT QSize(300,300)

#define ITEM_HEIGHT 50
#define BG_START_COLOR QColor(179,179,183)
#define BG_END_COLOR QColor(187,193,207)

#define ITEM_START_COLOR ITEM_END_COLOR.lighter()
#define ITEM_END_COLOR QColor(62,135,166)

#define ITEM_START_COLOR_A ITEM_END_COLOR_A.lighter()
#define ITEM_END_COLOR_A QColor(221,221,221)

#define HOVER_OPACITY 0.2
#define HOVER_START_COLOR HOVER_END_COLOR.lighter()
#define HOVER_END_COLOR QColor(98,139,21)

#define HOVER_TEXT_COLOR Qt::red
#define SELECT_TEXT_COLOR Qt::white
#define NORMAL_TEXT_COLOR Qt::black

#define RECT_RADIUS 4

#define ITEM_SPACE  10

enum Orientation{
    Middle,
    Left,
    Right
};

class ItemInfo{
public:
    ItemInfo(const QString& str):
        m_strData(str),
        m_orientation(Left)
    {
    }

    ItemInfo(const QString& str,const int &orientation):
        m_strData(str),
        m_orientation(orientation)
    {
    }

    ItemInfo():m_orientation(Left){}
    ~ItemInfo(){}

public:
    /// public interfaces
    void setText(const QString& str){
        m_strData = str;
    }

    QString getText() const{
        return m_strData;
    }

    int getOrientation() const{
        return m_orientation;
    }

    void setOrientation(int orientation){
        m_orientation = orientation;
    }

private:
    QString m_strData;
    int m_orientation;
};
#endif // ITEMINFO_H
