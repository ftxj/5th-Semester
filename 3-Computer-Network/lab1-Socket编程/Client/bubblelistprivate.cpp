#include "bubblelistprivate.h"

BubbleListPrivate::BubbleListPrivate(QWidget* parent):QWidget(parent){
    initVars();
    initSettings();
}

void BubbleListPrivate::initVars(){
    m_currIndex = 0;
    m_VisibleItemCnt = 0;
}

void BubbleListPrivate::initSettings(){
    setMouseTracking(this);
}

void BubbleListPrivate::calcGeo(){
    m_VisibleItemCnt = height() / (ITEM_HEIGHT + ITEM_SPACE + 10) + 1;
}

void BubbleListPrivate::wheelUp(){
    if(--m_currIndex < 0){
        m_currIndex = 0;
    }
    update();
}

void BubbleListPrivate::wheelDown(){
    if(++m_currIndex + m_VisibleItemCnt > m_IIVec.count()){
        m_currIndex = m_IIVec.count() - m_VisibleItemCnt;
    }
    if (m_currIndex < 0){
        m_currIndex = 0;
    }
    update();
}

void BubbleListPrivate::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing, true);
    drawItems(&painter);
}

void BubbleListPrivate::showEvent(QShowEvent *){
    calcGeo();
}

void BubbleListPrivate::wheelEvent(QWheelEvent *e){
    if(e->delta() > 0){
        wheelUp();
    }
    else{
        wheelDown();
    }
}

void BubbleListPrivate::drawItems(QPainter *painter){
    if(m_IIVec.count() == 0){
        return;
    }
    painter->save();
    int Guard = 0,  nWidth = this->width();
    qreal nItemY = 0;
    nWidth = (nWidth % 2 == 0) ? nWidth : nWidth + 1;

    for(int nIndex = m_currIndex;nIndex < m_IIVec.size(); nIndex++){
        if(Guard++ > m_VisibleItemCnt){
            break ;
        }
        int orientation = m_IIVec[nIndex].getOrientation();
        QString strText = m_IIVec[nIndex].getText();

        QPointF topLeft(0,nItemY);
        QPointF bottomRight(nWidth, nItemY + ITEM_HEIGHT + ITEM_SPACE);
        QRectF ItemRect(topLeft,bottomRight);
        painter->save();
        QTransform t;
        t.translate(ItemRect.center().x(),ItemRect.center().y());
        painter->setTransform(t);
        QPointF rectTopLeft;
        QPointF rectBottomRight;
        QRectF textRect(rectTopLeft,rectBottomRight);
        QLinearGradient itemGradient(textRect.topLeft(),textRect.bottomLeft());

        QFont font("幼圆", 10);
        painter->setFont(font);

        QFontMetrics fm(font);
        QPainterPath path;
        int pixelsWide = fm.width(strText);
        int pixelsHigh = fm.height();

        pixelsWide = pixelsWide < (nWidth * 2 / 3) ? pixelsWide: (nWidth * 2 / 3);
        pixelsHigh = pixelsWide < (nWidth * 2 / 3) ? ITEM_HEIGHT : (((pixelsWide / (nWidth / 2)) + 1) * ITEM_HEIGHT / 2);

        if (orientation == Right){
            itemGradient.setColorAt(0.0,ITEM_START_COLOR);
            itemGradient.setColorAt(1.0,ITEM_END_COLOR);

            painter->save();
            painter->setPen(Qt::red);
            painter->drawRoundedRect(nWidth / 2 - 55, -ITEM_HEIGHT / 2, 50, 50, 2, 2);
            painter->drawPixmap(nWidth / 2 - 54, -ITEM_HEIGHT / 2 + 1, 48, 48, QPixmap(":/images/zgl.png"));
            painter->restore();

            int nX = (nWidth / 2) - 85 - pixelsWide;
            if (nX < 0) {
                nX = -pixelsWide - 85 + nWidth / 2;
            }

            painter->save();
            textRect = QRectF(nX, -ITEM_HEIGHT / 2, pixelsWide + 20, pixelsHigh);
            path.addRoundedRect(textRect, 10, 10);
            path.moveTo(nWidth / 2 - 65, -ITEM_HEIGHT / 2 + 10);
            path.lineTo(nWidth / 2 - 55, -ITEM_HEIGHT / 2 + 16);
            path.lineTo(nWidth / 2 - 65, -ITEM_HEIGHT / 2 + 19);
            painter->fillPath(path, QColor("#3FA7EC"));
            painter->restore();

            painter->setPen(Qt::white);
            textRect = QRectF(nX + 10, -ITEM_HEIGHT / 2, pixelsWide, pixelsHigh);
        }
        else if(orientation == Left){
            itemGradient.setColorAt(0.0, ITEM_START_COLOR_A);
            itemGradient.setColorAt(1.0, ITEM_END_COLOR_A);

            painter->save();
            textRect = QRectF(-nWidth / 2 + 65, -ITEM_HEIGHT / 2, pixelsWide + 20, pixelsHigh);
            path.addRoundedRect(textRect, 5, 5);
            path.moveTo(-nWidth / 2 + 65, -ITEM_HEIGHT / 2 + 10);
            path.lineTo(-nWidth / 2 + 55, -ITEM_HEIGHT / 2 + 16);
            path.lineTo(-nWidth / 2 + 65, -ITEM_HEIGHT / 2 + 19);
            painter->fillPath(path, QColor("#E2E3E1"));
            painter->restore();

            painter->save();
            painter->setPen(Qt::red);
            painter->drawRoundedRect(-nWidth / 2 + 5, -ITEM_HEIGHT / 2, 50, 50, 2, 2);
            painter->drawPixmap(-nWidth/2 + 6, -ITEM_HEIGHT / 2 + 1, 48, 48, QPixmap(":/images/head-48.png"));
            painter->restore();

            painter->setPen(QColor("#666666"));
            textRect = QRectF(-nWidth / 2 + 65 + 10, -ITEM_HEIGHT / 2, pixelsWide, pixelsHigh);
        }
        else{
            textRect = QRectF(-pixelsWide/2,  -ITEM_HEIGHT / 2, pixelsWide + 2, pixelsHigh);
            painter->setPen(Qt::darkGray);
        }

        painter->drawText(textRect, strText, Qt::AlignVCenter |Qt::AlignLeft);
        painter->restore();

        nItemY += ITEM_HEIGHT + ITEM_SPACE;
    }
    painter->restore();
}

void BubbleListPrivate::addItem(const QString &str, const int &orientation){
    ItemInfo ID(str, orientation);
    m_IIVec.push_back(ID);
    calcGeo();
    wheelDown();
}

void BubbleListPrivate::addTime(const QString &str){
    ItemInfo ID(str, Middle);
    m_IIVec.push_back(ID);
    calcGeo();
    wheelDown();
}

void BubbleListPrivate::clear(){
    m_IIVec.clear();
    m_VisibleItemCnt = 0;
    m_currIndex = 0;
    update();
}

void BubbleListPrivate::render(){
    update();
}
