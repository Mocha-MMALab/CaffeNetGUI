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

#include "DiagramScene.h"
#include "Arrow.h"

#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>

DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = LayerGUI::ConvolutionLayer;
    line = 0;
    textItem = 0;
    mItemNum = 0;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;

    mMap.insert(StrLayerPair("Convolution", LayerGUI::Layers::ConvolutionLayer));
    mMap.insert(StrLayerPair("Pooling", LayerGUI::Layers::PoolingLayer));
    mMap.insert(StrLayerPair("SPP", LayerGUI::Layers::SPPLayer));
    mMap.insert(StrLayerPair("LRN", LayerGUI::Layers::LRNLayer));
    mMap.insert(StrLayerPair("MVN", LayerGUI::Layers::MVNLayer));
    mMap.insert(StrLayerPair("Reshape", LayerGUI::Layers::ReshapeLayer));
    mMap.insert(StrLayerPair("Slice", LayerGUI::Layers::SliceLayer));
    mMap.insert(StrLayerPair("InnerProduct", LayerGUI::Layers::InnerProductLayer));
    mMap.insert(StrLayerPair("Softmax", LayerGUI::Layers::SoftmaxLayer));
    mMap.insert(StrLayerPair("Flatten", LayerGUI::Layers::FlattenLayer));
    mMap.insert(StrLayerPair("Eltwise", LayerGUI::Layers::EltwiseLayer));
    mMap.insert(StrLayerPair("Concat", LayerGUI::Layers::ConcatLayer));
    mMap.insert(StrLayerPair("Argmax", LayerGUI::Layers::ArgMaxLayer));
    mMap.insert(StrLayerPair("Reduction", LayerGUI::Layers::ReductionLayer));

    mMap.insert(StrLayerPair("DummyData", LayerGUI::Layers::DummyDataLayer));
    mMap.insert(StrLayerPair("HDF5Output", LayerGUI::Layers::HDF5OutputLayer));
    mMap.insert(StrLayerPair("HDF5Data", LayerGUI::Layers::HDF5DataLayer));
    mMap.insert(StrLayerPair("WindowData", LayerGUI::Layers::WindowDataLayer));
    mMap.insert(StrLayerPair("ImageData", LayerGUI::Layers::ImageDataLayer));
    mMap.insert(StrLayerPair("MemoryData", LayerGUI::Layers::MemoryDataLayer));
    mMap.insert(StrLayerPair("Data", LayerGUI::Layers::DataLayer));

    mMap.insert(StrLayerPair("HingeLoss", LayerGUI::Layers::HingeLossLayer));
    mMap.insert(StrLayerPair("InfogainLoss", LayerGUI::Layers::InfogainLossLayer));
    mMap.insert(StrLayerPair("ContrastiveLoss", LayerGUI::Layers::ContrastiveLossLayer));
    mMap.insert(StrLayerPair("MultinomialLogisticLoss", LayerGUI::Layers::MultinomialLogisticLossLayer));
    mMap.insert(StrLayerPair("SigmoidCrossEntropyLoss", LayerGUI::Layers::SigmoidCrossEntropyLossLayer));
    mMap.insert(StrLayerPair("EuclideanLoss", LayerGUI::Layers::EuclideanLossLayer));
    mMap.insert(StrLayerPair("SoftmaxWithLoss", LayerGUI::Layers::SoftmaxWithLossLayer));
    mMap.insert(StrLayerPair("Accuracy", LayerGUI::Layers::AccuracyLayer));

    mMap.insert(StrLayerPair("PReLU", LayerGUI::Layers::PReLULayer));
    mMap.insert(StrLayerPair("Threshold", LayerGUI::Layers::ThresholdLayer));
    mMap.insert(StrLayerPair("TanH", LayerGUI::Layers::TanHLayer));
    mMap.insert(StrLayerPair("ReLU", LayerGUI::Layers::ReLULayer));
    mMap.insert(StrLayerPair("Sigmoid", LayerGUI::Layers::SigmoidLayer));
    mMap.insert(StrLayerPair("Power", LayerGUI::Layers::PowerLayer));
    mMap.insert(StrLayerPair("Dropout", LayerGUI::Layers::DropoutLayer));
    mMap.insert(StrLayerPair("Exp", LayerGUI::Layers::ExpLayer));
    mMap.insert(StrLayerPair("Log", LayerGUI::Layers::LogLayer));
    mMap.insert(StrLayerPair("AbsVal", LayerGUI::Layers::AbsValLayer));
    mMap.insert(StrLayerPair("BNLL", LayerGUI::Layers::BNLLLayer));

}

bool DiagramScene::computationIsInPlace(string layerType)
{
    switch(mMap[layerType])
    {
        case LayerGUI::Layers::ReLULayer:
        case LayerGUI::Layers::DropoutLayer:
            return true;
        default:
            return false;
    }
}

void DiagramScene::setLineColor(const QColor &color)
{
    myLineColor = color;
    if (isItemChange(Arrow::Type))
    {
        Arrow *item = qgraphicsitem_cast<Arrow *>(selectedItems().first());
        item->setColor(myLineColor);
        update();
    }
}

void DiagramScene::setTextColor(const QColor &color)
{
    myTextColor = color;
    if (isItemChange(DiagramTextItem::Type))
    {
        DiagramTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        item->setDefaultTextColor(myTextColor);
    }
}

void DiagramScene::setItemColor(const QColor &color)
{
    myItemColor = color;
    if (isItemChange(LayerDiagramItem::Type))
    {
        LayerDiagramItem *item = qgraphicsitem_cast<LayerDiagramItem *>(selectedItems().first());
        //item->setBrush(myItemColor);
    }
}

void DiagramScene::setFont(const QFont &font)
{
    myFont = font;

    if (isItemChange(DiagramTextItem::Type))
    {
        QGraphicsTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        //At this point the selection can change so the first selected item might not be a DiagramTextItem
        if (item)
        {
            item->setFont(myFont);
        }
    }
}

void DiagramScene::setMode(Mode mode)
{
    myMode = mode;
}

void DiagramScene::setItemType(LayerGUI::Layers type)
{
    myItemType = type;
}

void DiagramScene::editorLostFocus(DiagramTextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty())
    {
        removeItem(item);
        item->deleteLater();
    }
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
    {
        return;
    }

    LayerDiagramItem *item;
    switch (myMode)
    {
        case InsertItem:
            item = new LayerDiagramItem(myItemType, myItemMenu, mItemNum);
            //item->setBrush(myItemColor);
            addItem(item);
            item->setPos(mouseEvent->scenePos());
            emit itemInserted(item);
            mItemNum++;
            if(myItemType!=LayerGUI::Layers::DataBlob && !item->computationIsInPlace(myItemType))
            {
                item = new LayerDiagramItem(LayerGUI::Layers::DataBlob, myItemMenu, mItemNum);
                //item->setBrush(myItemColor);
                addItem(item);
                int x = mouseEvent->scenePos().x();
                int y = mouseEvent->scenePos().y() + 150;
                item->setPos(x, y);
                emit itemInserted(item);
                mItemNum++;
                line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), item->pos()));
                addLineItem();
            }
            break;
        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(myLineColor, 2));
            addItem(line);
            break;
        case InsertText:
            textItem = new DiagramTextItem();
            textItem->setFont(myFont);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setZValue(1000.0);
            connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                    this, SLOT(editorLostFocus(DiagramTextItem*)));
            connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                    this, SIGNAL(itemSelected(QGraphicsItem*)));
            addItem(textItem);
            textItem->setDefaultTextColor(myTextColor);
            textItem->setPos(mouseEvent->scenePos());
            emit textInserted(textItem);
            break;
        default:
            ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != 0)
    {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
        emit(sendIsSave(false));
    } else if (myMode == MoveItem)
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != 0)
    {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
        {
            startItems.removeFirst();
        }
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
        {
            endItems.removeFirst();
        }
        removeItem(line);
        delete line;

        //remove other item to ensure the first item is DiagramItem by Aaron.
        for(int i = 0; i < startItems.count(); i++)
        {
            if(startItems.first()->type() != LayerDiagramItem::Type)
            {
                startItems.removeFirst();
            }
        }

        for(int i = 0; i < endItems.count(); i++)
        {
            if(endItems.first()->type() != LayerDiagramItem::Type)
            {
                endItems.removeFirst();
            }
        }

        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first()->type() == LayerDiagramItem::Type &&
            endItems.first()->type() == LayerDiagramItem::Type &&
            startItems.first() != endItems.first())
        {
            LayerDiagramItem *startItem = qgraphicsitem_cast<LayerDiagramItem *>(startItems.first());
            LayerDiagramItem *endItem = qgraphicsitem_cast<LayerDiagramItem *>(endItems.first());
            Arrow *arrow = new Arrow(startItem, endItem);
            if(!startItem->arrowIsForbidden(arrow))
            {
                startItem->addArrow(arrow);
                endItem->addArrow(arrow);
                arrow->setColor(myLineColor);
                arrow->setZValue(-1000.0);
                addItem(arrow);
                arrow->updatePosition();
            }
            else
            {
                delete arrow;
            }
        }
        emit(sendIsSave(false));
    }
    line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool DiagramScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems())
    {
        if (item->type() == type)
            return true;
    }
    return false;
}

void DiagramScene::addNeuralNetwork(LayerParameter mLayerParam, int layerNum, int areaNum)
{
    LayerDiagramItem *item = new LayerDiagramItem(mMap[mLayerParam.type()], myItemMenu, 0, mLayerParam);

    int x = startPosX ;
    int y = startPosY + areaNum * 2 * 150;
    for(int i = 0; i < mLayerItemPositions.size(); i++)
    {
        if(x == mLayerItemPositions[i].first && y == mLayerItemPositions[i].second)
        {
            x += 150;
        }
    }
    IntIntPair temp;
    temp.first = x;
    temp.second = y;
    mLayerItemPositions.insert(layerNum, temp);

    addItem(item);
    item->setPos(x, y);
    emit itemInserted(item);
    mItemNum++;

    y = y + 150;
    for(int i = 0;i<mLayerParam.top_size();i++)
    {
        if(!mBlobItemPositions.contains(mLayerParam.top(i)))
        {
            item = new LayerDiagramItem(LayerGUI::Layers::DataBlob, myItemMenu, i, mLayerParam);
            foreach(string blobItem,mBlobItemPositions.keys())
            {
                if(x==mBlobItemPositions[blobItem].first && y==mBlobItemPositions[blobItem].second)
                {
                    x += 150;
                }
            }
            temp.first=x;
            temp.second=y;
            mBlobItemPositions.insert(mLayerParam.top(i), temp);

            addItem(item);
            item->setPos(x, y);
            emit itemInserted(item);
            mItemNum++;
        }
    }
}

void DiagramScene::setStartPos(int x, int y)
{
    startPosX = x;
    startPosY = y;
}

void DiagramScene::clearPosVector()
{
    mLayerItemPositions.clear();
    mBlobItemPositions.clear();
}

void DiagramScene::addLine(int startItemNum, string endItemName)
{
    line = new QGraphicsLineItem(QLineF(QPointF(mLayerItemPositions[startItemNum].first, mLayerItemPositions[startItemNum].second),
                                                                      QPointF(mBlobItemPositions[endItemName].first, mBlobItemPositions[endItemName].second)));
    addLineItem();
}

void DiagramScene::addLine(string startItemName, int endItemNum)
{
    line = new QGraphicsLineItem(QLineF(QPointF(mBlobItemPositions[startItemName].first, mBlobItemPositions[startItemName].second),
                                                                      QPointF(mLayerItemPositions[endItemNum].first, mLayerItemPositions[endItemNum].second)));
    addLineItem();
}

void DiagramScene::addLineItem()
{
    line->setPen(QPen(myLineColor, 2));
    addItem(line);

    QLineF newLine(line->line().p1(), line->line().p2());
    line->setLine(newLine);

    QList<QGraphicsItem *> startItems = items(line->line().p1());
    if (startItems.count() && startItems.first() == line)
    {
        startItems.removeFirst();
    }
    QList<QGraphicsItem *> endItems = items(line->line().p2());
    if (endItems.count() && endItems.first() == line)
    {
        endItems.removeFirst();
    }
    removeItem(line);
    delete line;

    //remove other item to ensure the first item is DiagramItem by Aaron.
    for(int i = 0; i < startItems.count(); i++)
    {
        if(startItems.first()->type() != LayerDiagramItem::Type)
        {
            startItems.removeFirst();
        }
    }

    for(int i = 0; i < endItems.count(); i++)
    {
        if(endItems.first()->type() != LayerDiagramItem::Type)
        {
            endItems.removeFirst();
        }
    }

    if (startItems.count() > 0 && endItems.count() > 0 &&
        startItems.first()->type() == LayerDiagramItem::Type &&
        endItems.first()->type() == LayerDiagramItem::Type &&
        startItems.first() != endItems.first())
    {
        LayerDiagramItem *startItem = qgraphicsitem_cast<LayerDiagramItem *>(startItems.first());
        LayerDiagramItem *endItem = qgraphicsitem_cast<LayerDiagramItem *>(endItems.first());
        Arrow *arrow = new Arrow(startItem, endItem);
        if(!startItem->arrowIsForbidden(arrow))
        {
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setColor(myLineColor);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            arrow->updatePosition();
        }
        else
        {
            delete arrow;
        }
    }
    line = 0;
}
