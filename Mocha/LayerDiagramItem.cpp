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

#include "LayerDiagramItem.h"
#include "Arrow.h"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>
#include "MMALib/include/Layers.h"

#include<QDebug>
static const char * gLayersStrings[] = {   //Other
                                           "DataBlob",

                                           //VisionLayer
                                          "Convolution Layer",
                                          "Pooling Layer",
                                          "SPP Layer",
                                          "LRN Layer",

                                          //CommonLayer
                                          "MVN Layer",
                                          "Reshape Layer",
                                          "Slice Layer",
                                          "Inner Product Layer",
                                          "Softmax Layer",
                                          "Flatten Layer",
                                          "Eltwise Layer",
                                          "Concat Layer",
                                          "Arg Max Layer",
                                          "Reduction Layer",

                                          //DataLayer
                                          "DummyData Layer",
                                          "HDF5Output Layer",
                                          "HDF5Data Layer",
                                          "WindowData Layer",
                                          "ImageData Layer",
                                          "MemoryData Layer",
                                          "Data Layer",

                                          //LossLayer
                                          "Hinge Loss Layer",
                                          "Infogain Loss Layer",
                                          "Contrastive Loss Layer",
                                          "MultinomialLogistic Loss Layer",
                                          "SigmoidCrossEntropy Loss Layer",
                                          "Euclidean Loss Layer",
                                          "SoftmaxWithLoss Layer",
                                          "Accuracy Layer",

                                          //NeuroLayer
                                          "PReLU Layer",
                                          "Threshold Layer",
                                          "TanH Layer",
                                          "ReLU Layer",
                                          "Sigmoid Layer",
                                          "Power Layer",
                                          "Dropout Layer",
                                          "Exp Layer",
                                          "Log Layer",
                                          "AbsVal Layer",
                                          "BNLL Layer",
                                      };

using namespace MMALab;


LayerDiagramItem::LayerDiagramItem(LayerGUI::Layers layer, QMenu *contextMenu, int itemNum,
                                   QGraphicsItem *parent): QGraphicsItemGroup(parent)
{
    mLayer = layer;
    mLayerType = initLayerType(layer, itemNum);
    mContextMenu = contextMenu;

    QPainterPath path;
    switch (mLayerType)
    {
        case LayerGUI::Other:
            mPolygon << QPointF(-50, -12.5) << QPointF(-50, 12.5)
                  << QPointF(-25, 25)  << QPointF(25, 25)
                  << QPointF(50, 12.5)   << QPointF(50, -12.5)
                  << QPointF(25, -25)    << QPointF(-25, -25)
                  << QPointF(-50, -12.5);
        break;

        case LayerGUI::VisionLayers:
            mPolygon << QPointF(-50, -50) << QPointF(50, -50)
                  << QPointF(50, 50) << QPointF(-50, 50)
                  << QPointF(-50, -50);
            break;

        case LayerGUI::CommonLayers:
            mPolygon << QPointF(-50, 0) << QPointF(0, 50)
                      << QPointF(50, 0) << QPointF(0, -50)
                      << QPointF(-50, 0);
            break;

        case LayerGUI::DataLayers:
            path.addEllipse(-50, -37.5, 100, 75);
            mPolygon = path.toFillPolygon();
            break;

        case LayerGUI::LossLayers:
        mPolygon << QPointF(-50, 0) << QPointF(-25, 43)
                 << QPointF(25, 43) << QPointF(50, 0)
                 << QPointF(25, -43) << QPointF(-25, -43)
                 << QPointF(-50, 0);
            break;

        default:
            mPolygon << QPointF(-60, -40) << QPointF(-35, 40)
                      << QPointF(60, 40) << QPointF(35, -40)
                      << QPointF(-60, -40);
            break;
    }


    mPolygonItem.setBrush(*mBrush);
    mPolygonItem.setPolygon(mPolygon);
    this->addToGroup(&mPolygonItem);
    this->addToGroup(&mLayerNameItem);
    this->addToGroup(&mLayerInfoItem);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setHandlesChildEvents(false);
}

LayerDiagramItem::LayerDiagramItem(LayerGUI::Layers layer, QMenu *contextMenu, int topNum, LayerParameter  layerParam,
                                   QGraphicsItem *parent): QGraphicsItemGroup(parent)
{
    mLayer = layer;
    mLayerType = initLayerType(layer, layerParam, topNum);
    mContextMenu = contextMenu;

    QPainterPath path;
    switch (mLayerType)
    {
    case LayerGUI::Other:
        mPolygon << QPointF(-50, -12.5) << QPointF(-50, 12.5)
              << QPointF(-25, 25)  << QPointF(25, 25)
              << QPointF(50, 12.5)   << QPointF(50, -12.5)
              << QPointF(25, -25)    << QPointF(-25, -25)
              << QPointF(-50, -12.5);
        break;

        case LayerGUI::VisionLayers:
            mPolygon << QPointF(-50, -50) << QPointF(50, -50)
                  << QPointF(50, 50) << QPointF(-50, 50)
                  << QPointF(-50, -50);
            break;

        case LayerGUI::CommonLayers:
            mPolygon << QPointF(-50, 0) << QPointF(0, 50)
                      << QPointF(50, 0) << QPointF(0, -50)
                      << QPointF(-50, 0);
            break;

        case LayerGUI::DataLayers:
            path.addEllipse(-50, -37.5, 100, 75);
            mPolygon = path.toFillPolygon();
            break;

        case LayerGUI::LossLayers:
            mPolygon << QPointF(-50, -25) << QPointF(-50, 25)
                      << QPointF(-25, 50)  << QPointF(25, 50)
                      << QPointF(50, 25)   << QPointF(50, -25)
                      << QPointF(25, -50)    << QPointF(-25, -50)
                      << QPointF(-50, -25);/**/
            break;

        default:
            mPolygon << QPointF(-60, -40) << QPointF(-35, 40)
                      << QPointF(60, 40) << QPointF(35, -40)
                      << QPointF(-60, -40);
            break;
    }


    mPolygonItem.setBrush(*mBrush);
    mPolygonItem.setPolygon(mPolygon);
    this->addToGroup(&mPolygonItem);
    this->addToGroup(&mLayerNameItem);
    this->addToGroup(&mLayerInfoItem);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setHandlesChildEvents(false);
}

void LayerDiagramItem::removeArrow(Arrow *arrow)
{
    int index = mArrows.indexOf(arrow);
    if (index != -1)
    {
        mArrows.removeAt(index);
    }
}

void LayerDiagramItem::removeArrows()
{
    foreach (Arrow *arrow, mArrows)
    {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void LayerDiagramItem::addArrow(Arrow *arrow)
{
    mArrows.append(arrow);
}

QPixmap LayerDiagramItem::image() const
{
    QPixmap pixmap(130, 130);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 5));
    painter.translate(65, 65);
    painter.setBrush(*mBrush);
    painter.drawPolygon(mPolygon);
    return pixmap;
}

void LayerDiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    mContextMenu->exec(event->screenPos());
}

QVariant LayerDiagramItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange)
    {
        foreach (Arrow *arrow, mArrows)
        {
            arrow->updatePosition();
        }
    }

    return value;
}

LayerGUI::LayerType LayerDiagramItem::initLayerType(LayerGUI::Layers layer, int itemNum)
{
    LayerGUI::LayerType layerType = LayerGUI::VisionLayers;
    mLayerName = gLayersStrings[layer] + QString::fromStdString(" ") + QString::number(itemNum);
    mLayerNameItem.setPlainText(mLayerName);
    mLayerNameItem.setTextInteractionFlags(Qt::TextEditorInteraction);
    mLayerNameItem.setPos(0, 50);
    mLayerInfoItem.setPos(-55, -73);

    switch (layer)
    {
    case LayerGUI::DataBlob:
        layerType = LayerGUI::Other;
        mBrush = new QBrush(QColor(192, 192, 192, 192));
        mLayerNameItem.setPos(0, 25);
        mLayerObject = new MMALab::ConvolutionLayer(mLayerName.toStdString());
        break;
    case LayerGUI::ConvolutionLayer:
        layerType = LayerGUI::VisionLayers;
        mBrush = new QBrush(QColor(255, 0, 0, 192));
        mLayerObject = new MMALab::ConvolutionLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ConvolutionLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "kerenl size: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getKernelSize()) + "\n";
        mLayerInfo += "stride: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getStride()) + "\n";
        mLayerInfo += "pad: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getPad()) + "\n";
        mLayerInfo += "num output: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getNumOutput());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::PoolingLayer:
        layerType = LayerGUI::VisionLayers;
        mBrush = new QBrush(QColor(255, 0, 0, 192));
        mLayerObject = new MMALab::PoolingLayer(mLayerName.toStdString());

        switch (((MMALab::PoolingLayer*)mLayerObject)->getPool())
        {
            case MMALab::PoolMethod::POOLMETHOD_MAX:
                mLayerInfo = "MAX ";
                break;
            case MMALab::PoolMethod::POOLMETHOD_AVE:
                mLayerInfo = "AVE ";
                break;
            case MMALab::PoolMethod::POOLMETHOD_STOCHASTIC:
                mLayerInfo = "STOCHASTIC ";
                break;
            default:
                break;
        }
        mLayerInfo += QString::fromStdString(((MMALab::PoolingLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "kerenl size: " + QString::number(((MMALab::PoolingLayer*)mLayerObject)->getKernelSize()) + "\n";
        mLayerInfo += "stride: " + QString::number(((MMALab::PoolingLayer*)mLayerObject)->getStride()) + "\n";
        mLayerInfo += "pad: " + QString::number(((MMALab::PoolingLayer*)mLayerObject)->getPad());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::SPPLayer:
        layerType = LayerGUI::VisionLayers;
        mBrush = new QBrush(QColor(255, 0, 0, 192));
        mLayerObject = new MMALab::SPPLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::SPPLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::LRNLayer:
        layerType = LayerGUI::VisionLayers;
        mBrush = new QBrush(QColor(255, 0, 0, 192));
        mLayerObject = new MMALab::LRNLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::LRNLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::MVNLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::MVNLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::MVNLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ReshapeLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::ReshapeLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::MVNLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::SliceLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::SliceLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::SliceLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::InnerProductLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::InnerProductLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::InnerProductLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "num output: " + QString::number(((MMALab::InnerProductLayer*)mLayerObject)->getNumOutput());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::SoftmaxLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::SoftmaxLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::SoftmaxLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::FlattenLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::FlattenLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::FlattenLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::EltwiseLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::EltwiseLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::EltwiseLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ConcatLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::ConcatLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ConcatLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ArgMaxLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::ArgMaxLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ArgMaxLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ReductionLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::ReductionLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ReductionLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::DummyDataLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::DummyDataLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::DummyDataLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::HDF5OutputLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::HDF5OutputLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::HDF5OutputLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "file name: " + QString::fromStdString(((MMALab::HDF5OutputLayer*)mLayerObject)->getFileName());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::HDF5DataLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::HDF5DataLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::HDF5DataLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "source: " + QString::fromStdString(((MMALab::HDF5DataLayer*)mLayerObject)->getSource()) + "\n";
        mLayerInfo += "batch: " + QString::number(((MMALab::HDF5DataLayer*)mLayerObject)->getBatchSize());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::WindowDataLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::WindowDataLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::WindowDataLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ImageDataLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::ImageDataLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ImageDataLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "source: " + QString::fromStdString(((MMALab::ImageDataLayer*)mLayerObject)->getSource()) + "\n";
        mLayerInfo += "batch: " + QString::number(((MMALab::ImageDataLayer*)mLayerObject)->getBatchSize());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::MemoryDataLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::MemoryDataLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::MemoryDataLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "batch: "+ QString::number(((MMALab::MemoryDataLayer*)mLayerObject)->getBatchSize()) + "\n";
        mLayerInfo += "channels: "+ QString::number(((MMALab::MemoryDataLayer*)mLayerObject)->getChannels()) + "\n";
        mLayerInfo += "height: "+ QString::number(((MMALab::MemoryDataLayer*)mLayerObject)->getHeight()) + "\n";
        mLayerInfo += "width: "+ QString::number(((MMALab::MemoryDataLayer*)mLayerObject)->getWidth());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::DataLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::DataLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::DataLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "source: "+ QString::fromStdString(((MMALab::DataLayer*)mLayerObject)->getSource()) + "\n";
        mLayerInfo += "batch: "+ QString::number(((MMALab::DataLayer*)mLayerObject)->getBatchSize());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::HingeLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::HingeLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::HingeLossLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::InfogainLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::InfogainLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::InfogainLossLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ContrastiveLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::ContrastiveLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ContrastiveLossLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::MultinomialLogisticLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::MultinomialLogisticLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::MultinomialLogisticLossLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::SigmoidCrossEntropyLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::SigmoidCrossEntropyLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::SigmoidCrossEntropyLossLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::EuclideanLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::EuclideanLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::EuclideanLossLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::SoftmaxWithLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::SoftmaxWithLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::SoftmaxWithLossLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::AccuracyLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::AccuracyLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::AccuracyLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::PReLULayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::PReLULayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::PReLULayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ThresholdLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::ThresholdLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ThresholdLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::TanHLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::TanHLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::TanHLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ReLULayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::ReLULayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ReLULayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::SigmoidLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::SigmoidLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::SigmoidLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::PowerLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::PowerLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::PowerLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::DropoutLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::DropoutLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::DropoutLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ExpLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::ExpLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ExpLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::LogLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::LogLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::LogLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::AbsValLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::AbsValLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::AbsValLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::BNLLLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::BNLLLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::BNLLLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    default:
        layerType = LayerGUI::VisionLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::ConvolutionLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ConvolutionLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "kerenl size: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getKernelSize()) + "\n";
        mLayerInfo += "stride: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getStride()) + "\n";
        mLayerInfo += "pad: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getPad()) + "\n";
        mLayerInfo += "num output: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getNumOutput());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    }

    LayerParameter  nullLayerParam;
    mProerties = new LayerProperties(mLayer, mLayerObject, nullLayerParam, &mLayerNameItem, &mLayerInfoItem);

    return layerType;
}

LayerGUI::LayerType LayerDiagramItem::initLayerType(LayerGUI::Layers layer, LayerParameter  layerParam, int topNum)
{
    LayerGUI::LayerType layerType = LayerGUI::VisionLayers;

    if(layer == LayerGUI::DataBlob)
    {
        mLayerName = QString::fromStdString(layerParam.top(topNum));
    }
    else
    {
        mLayerName = QString::fromStdString(layerParam.name());
    }
    mLayerNameItem.setPlainText(mLayerName);
    mLayerNameItem.setTextInteractionFlags(Qt::TextEditorInteraction);
    mLayerNameItem.setPos(0, 50);
    mLayerInfoItem.setPos(-55, -73);

    switch (layer)
    {
    case LayerGUI::DataBlob:
        layerType = LayerGUI::Other;
        mBrush = new QBrush(QColor(192, 192, 192, 192));
        mLayerNameItem.setPos(0, 25);
        mLayerObject = new MMALab::ConvolutionLayer(mLayerName.toStdString());
        break;
    case LayerGUI::ConvolutionLayer:
        layerType = LayerGUI::VisionLayers;
        mBrush = new QBrush(QColor(255, 0, 0, 192));
        mLayerObject = new MMALab::ConvolutionLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ConvolutionLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "kerenl size: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getKernelSize()) + "\n";
        mLayerInfo += "stride: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getStride()) + "\n";
        mLayerInfo += "pad: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getPad()) + "\n";
        mLayerInfo += "num output: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getNumOutput());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::PoolingLayer:
        layerType = LayerGUI::VisionLayers;
        mBrush = new QBrush(QColor(255, 0, 0, 192));
        mLayerObject = new MMALab::PoolingLayer(mLayerName.toStdString());

        switch (((MMALab::PoolingLayer*)mLayerObject)->getPool())
        {
            case MMALab::PoolMethod::POOLMETHOD_MAX:
                mLayerInfo = "MAX ";
                break;
            case MMALab::PoolMethod::POOLMETHOD_AVE:
                mLayerInfo = "AVE ";
                break;
            case MMALab::PoolMethod::POOLMETHOD_STOCHASTIC:
                mLayerInfo = "STOCHASTIC ";
                break;
            default:
                break;
        }
        mLayerInfo += QString::fromStdString(((MMALab::PoolingLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "kerenl size: " + QString::number(((MMALab::PoolingLayer*)mLayerObject)->getKernelSize()) + "\n";
        mLayerInfo += "stride: " + QString::number(((MMALab::PoolingLayer*)mLayerObject)->getStride()) + "\n";
        mLayerInfo += "pad: " + QString::number(((MMALab::PoolingLayer*)mLayerObject)->getPad());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::SPPLayer:
        layerType = LayerGUI::VisionLayers;
        mBrush = new QBrush(QColor(255, 0, 0, 192));
        mLayerObject = new MMALab::SPPLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::SPPLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::LRNLayer:
        layerType = LayerGUI::VisionLayers;
        mBrush = new QBrush(QColor(255, 0, 0, 192));
        mLayerObject = new MMALab::LRNLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::LRNLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::MVNLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::MVNLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::MVNLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ReshapeLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::ReshapeLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::MVNLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::SliceLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::SliceLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::SliceLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::InnerProductLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::InnerProductLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::InnerProductLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "num output: " + QString::number(((MMALab::InnerProductLayer*)mLayerObject)->getNumOutput());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::SoftmaxLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::SoftmaxLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::SoftmaxLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::FlattenLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::FlattenLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::FlattenLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::EltwiseLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::EltwiseLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::EltwiseLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ConcatLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::ConcatLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ConcatLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ArgMaxLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::ArgMaxLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ArgMaxLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ReductionLayer:
        layerType = LayerGUI::CommonLayers;
        mBrush = new QBrush(QColor(0, 255, 0, 192));
        mLayerObject = new MMALab::ReductionLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ReductionLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::DummyDataLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::DummyDataLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ReductionLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::HDF5OutputLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::HDF5OutputLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::HDF5OutputLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "file name: " + QString::fromStdString(((MMALab::HDF5OutputLayer*)mLayerObject)->getFileName());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::HDF5DataLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::HDF5DataLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::HDF5DataLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "source: " + QString::fromStdString(((MMALab::HDF5DataLayer*)mLayerObject)->getSource()) + "\n";
        mLayerInfo += "batch: " + QString::number(((MMALab::HDF5DataLayer*)mLayerObject)->getBatchSize());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::WindowDataLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::WindowDataLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::WindowDataLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ImageDataLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::ImageDataLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ImageDataLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "source: " + QString::fromStdString(((MMALab::ImageDataLayer*)mLayerObject)->getSource()) + "\n";
        mLayerInfo += "batch: " + QString::number(((MMALab::ImageDataLayer*)mLayerObject)->getBatchSize());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::MemoryDataLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::MemoryDataLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::MemoryDataLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "batch: "+ QString::number(((MMALab::MemoryDataLayer*)mLayerObject)->getBatchSize()) + "\n";
        mLayerInfo += "channels: "+ QString::number(((MMALab::MemoryDataLayer*)mLayerObject)->getChannels()) + "\n";
        mLayerInfo += "height: "+ QString::number(((MMALab::MemoryDataLayer*)mLayerObject)->getHeight()) + "\n";
        mLayerInfo += "width: "+ QString::number(((MMALab::MemoryDataLayer*)mLayerObject)->getWidth());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::DataLayer:
        layerType = LayerGUI::DataLayers;
        mBrush = new QBrush(QColor(0, 0, 255, 192));
        mLayerObject = new MMALab::DataLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::DataLayer*)mLayerObject)->getLayerType()) + "\n";
        mLayerInfo += "source: "+ QString::fromStdString(((MMALab::DataLayer*)mLayerObject)->getSource()) + "\n";
        mLayerInfo += "batch: "+ QString::number(((MMALab::DataLayer*)mLayerObject)->getBatchSize());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::HingeLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::HingeLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::HingeLossLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::InfogainLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::InfogainLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::InfogainLossLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ContrastiveLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::ContrastiveLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ContrastiveLossLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::MultinomialLogisticLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::MultinomialLogisticLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::MultinomialLogisticLossLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::SigmoidCrossEntropyLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::SigmoidCrossEntropyLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::SigmoidCrossEntropyLossLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::EuclideanLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::EuclideanLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::EuclideanLossLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::SoftmaxWithLossLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::SoftmaxWithLossLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::SoftmaxWithLossLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::AccuracyLayer:
        layerType = LayerGUI::LossLayers;
        mBrush = new QBrush(QColor(255, 255, 0, 192));
        mLayerObject = new MMALab::AccuracyLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::AccuracyLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::PReLULayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::PReLULayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::PReLULayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ThresholdLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::ThresholdLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ThresholdLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::TanHLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::TanHLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::TanHLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ReLULayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::ReLULayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ReLULayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::SigmoidLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::SigmoidLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::SigmoidLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::PowerLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::PowerLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::PowerLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::DropoutLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::DropoutLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::DropoutLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::ExpLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::ExpLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::ExpLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::LogLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::LogLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::LogLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::AbsValLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::AbsValLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::AbsValLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    case LayerGUI::BNLLLayer:
        layerType = LayerGUI::NeuroLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::BNLLLayer(mLayerName.toStdString());

        mLayerInfo = QString::fromStdString(((MMALab::BNLLLayer*)mLayerObject)->getLayerType());
        mLayerInfoItem.setPlainText(mLayerInfo);
        break;
    default:
        layerType = LayerGUI::VisionLayers;
        mBrush = new QBrush(QColor(0, 255, 255, 192));
        mLayerObject = new MMALab::ConvolutionLayer(mLayerName.toStdString());
        break;
    }

    mProerties = new LayerProperties(mLayer, mLayerObject, layerParam, &mLayerNameItem, &mLayerInfoItem);

    return layerType;
}

void LayerDiagramItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    mProerties->show();
    QGraphicsItemGroup::mouseDoubleClickEvent(event);
}

void LayerDiagramItem::setBlob()
{
    if(mLayer == LayerGUI::DataBlob)
    {
        mDataBlob = new MMALab::DataBlob(getLayerName());
    }
    else
    {
        ((MMALab::BaseLayer*)mLayerObject)->clearnBottomConnection();
        ((MMALab::BaseLayer*)mLayerObject)->clearnTopConnection();
    }
}

void LayerDiagramItem::setTopsBottoms()
{
    foreach (Arrow *arrow, mArrows)
    {
        if(arrow->startItem() == this)
        {
             if(mLayer != LayerGUI::DataBlob)
             {
                 ((MMALab::BaseLayer*)mLayerObject)->addTopConnection((MMALab::DataBlob*)((arrow->endItem())->mDataBlob));
             }
        }
        if(arrow->endItem() == this)
        {
             if(mLayer != LayerGUI::DataBlob)
             {
                 ((MMALab::BaseLayer*)mLayerObject)->addBottomConnection((MMALab::DataBlob*)((arrow->startItem())->mDataBlob));
             }
        }
    }
}

string LayerDiagramItem::getLayerName()
{
    return mLayerNameItem.toPlainText().toStdString();
}

bool LayerDiagramItem::computationIsInPlace(LayerGUI::Layers layer)
{
    switch(layer)
    {
        case LayerGUI::Layers::ReLULayer:
        case LayerGUI::Layers::DropoutLayer:
            return true;
        default:
            return false;
    }
}

bool LayerDiagramItem::arrowIsForbidden(Arrow* arrow)
{
    int startLayer = arrow->startItem()->getLayer();
    int endLayer = arrow->endItem()->getLayer();
    if((startLayer != LayerGUI::Layers::DataBlob && endLayer != LayerGUI::Layers::DataBlob) ||
            (startLayer == LayerGUI::Layers::DataBlob && endLayer == LayerGUI::Layers::DataBlob))
    {
        return true;
    }
    else
    {
        foreach (Arrow *mArrow, mArrows)
        {
            if(arrow->startItem() == mArrow->startItem() && arrow->endItem() == mArrow->endItem())
            {
               return true;
            }

            if(arrow->startItem() == mArrow->endItem() && arrow->endItem() == mArrow->startItem())
            {
                if(computationIsInPlace(LayerGUI::Layers(startLayer))||computationIsInPlace(LayerGUI::Layers(endLayer)))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }
        return false;
    }
}
