/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "Arrow.h"

Arrow::Arrow(LayerDiagramItem *startItem, LayerDiagramItem *endItem, QGraphicsItem *parent)
    : QGraphicsLineItem(parent)
{
    mStartItem = startItem;
    mEndItem = endItem;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    mColor = Qt::black;
    setPen(QPen(mColor, PEN_SIZE, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(mArrowHead);
    return path;
}

void Arrow::updatePosition()
{
    QLineF line(mapFromItem(mStartItem, 0, 0), mapFromItem(mEndItem, 0, 0));
    setLine(line);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
          QWidget *)
{
    if (mStartItem->collidesWithItem(mEndItem))
    {
        return;
    }

    QPen myPen = pen();
    setPen(QPen(mColor, PEN_SIZE, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    myPen.setColor(mColor);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(mColor);

    //compute the intersect point of polygon and line for mEndItem
    QLineF centerLine(mStartItem->pos(), mEndItem->pos());
    QPolygonF endPolygon = mEndItem->polygon();
    QPointF p1 = endPolygon.first() + mEndItem->pos();
    QPointF p2;
    QPointF endIntersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); ++i)
    {
        p2 = endPolygon.at(i) + mEndItem->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &endIntersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
        {
            break;
        }
        p1 = p2;
    }

    //compute the intersect point of polygon and line for mStartItem
    QPolygonF startPolygon = mStartItem->polygon();
    p1 = startPolygon.first() + mStartItem->pos();
    p2;
    QPointF stratIntersectPoint;
    for (int i = 1; i < startPolygon.count(); ++i)
    {
        p2 = startPolygon.at(i) + mStartItem->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &stratIntersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
        {
            break;
        }
        p1 = p2;
    }

    setLine(QLineF(endIntersectPoint, stratIntersectPoint));

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
    {
        angle = (PI* 2) - angle;
    }

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + PI / 3) * arrowSize,
                                    cos(angle + PI / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + PI - PI / 3) * arrowSize,
                                    cos(angle + PI - PI / 3) * arrowSize);

    mArrowHead.clear();
    mArrowHead << line().p1() << arrowP1 << arrowP2;

    if(isSelected())
    {
        painter->setPen(QPen(Qt::darkCyan, PEN_SIZE, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawLine(line());
        painter->drawPolygon(mArrowHead);
    }
    else
    {
        painter->drawLine(line());
        painter->drawPolygon(mArrowHead);
    }

//    if (isSelected())
//    {
//        painter->setPen(QPen(Qt::darkCyan, 1.5, Qt::DashLine));
//        QLineF myLine = line();
//        myLine.translate(0, 4.0);
//        painter->drawLine(myLine);
//        myLine.translate(0,-8.0);
//        painter->drawLine(myLine);
//    }
}
