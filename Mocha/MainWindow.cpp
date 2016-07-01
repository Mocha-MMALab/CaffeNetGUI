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

#include "MainWindow.h"

const int InsertTextButton = 100;

MainWindow::MainWindow()
{
    createActions();
    createToolBox();
    createMenus();

    scene = new DiagramScene(itemMenu, this);
    scene->setSceneRect(QRectF(0, 0, 10000, 10000));
    scene->setStartPos(10000/2,100);
    connect(scene, SIGNAL(itemInserted(LayerDiagramItem*)),
            this, SLOT(itemInserted(LayerDiagramItem*)));
    connect(scene, SIGNAL(textInserted(QGraphicsTextItem*)),
            this, SLOT(textInserted(QGraphicsTextItem*)));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
            this, SLOT(itemSelected(QGraphicsItem*)));
    createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;
    /*layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);*/

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(toolBox);
    view = new QGraphicsView(scene);
    splitter->addWidget(view);

    layout->addWidget(splitter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(MochaVersionsInformation::TITLE);
    setUnifiedTitleAndToolBarOnMac(true);
    showMaximized();

    QDir dir;
    dir.setPath(dir.absolutePath() + "/Temp");
    dir.removeRecursively();
    dir.mkpath(dir.absolutePath());
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    int mainWindowReturn;
    mainWindowReturn = QMessageBox::question(NULL,
                                        tr("Close window"), tr("Do you want to export it?"),
                                        QMessageBox::Cancel | QMessageBox::Yes | QMessageBox::No, QMessageBox::Cancel);

    switch(mainWindowReturn)
    {
        case QMessageBox::Yes:
            if(exportNN() == QMessageBox::Cancel)
            {
                event->ignore();
                break;
            }
            else
            {
                emit sendMainWindowCloseSignal();
                event->accept();
                break;
            }
        case QMessageBox::No:
            emit sendMainWindowCloseSignal();
            event->accept();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
    }
}

void MainWindow::receiveIsSave(bool inputIsSave)
{
    isSave = inputIsSave;
}

void MainWindow::backgroundButtonGroupClicked(QAbstractButton *button)
{
    QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
    foreach (QAbstractButton *myButton, buttons)
    {
        if (myButton != button)
            button->setChecked(false);
    }
    QString text = button->text();
    if (text == tr("Blue Grid"))
    {
        scene->setBackgroundBrush(QPixmap(":/MainWindow/background1.png"));
    }
    else if (text == tr("White Grid"))
    {
        scene->setBackgroundBrush(QPixmap(":/MainWindow/background2.png"));
    }
    else if (text == tr("Gray Grid"))
    {
        scene->setBackgroundBrush(QPixmap(":/MainWindow/background3.png"));
    }
    else
    {
        scene->setBackgroundBrush(QPixmap(":/MainWindow/background4.png"));
    }

    scene->update();
    view->update();
}

void MainWindow::buttonGroupClicked(int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons)
    {
        if (buttonGroup->button(id) != button)
        {
            button->setChecked(false);
        }
    }
    if (id == InsertTextButton)
    {
        scene->setMode(DiagramScene::InsertText);
    } else
    {
        scene->setItemType(LayerGUI::Layers(id));
        scene->setMode(DiagramScene::InsertItem);
    }
}

void MainWindow::deleteItem()
{
    foreach (QGraphicsItem *item, scene->selectedItems())
    {
        if (item->type() == Arrow::Type)
        {
            scene->removeItem(item);
            Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
            arrow->startItem()->removeArrow(arrow);
            arrow->endItem()->removeArrow(arrow);
            delete item;
            isSave = false;
        }
    }

    foreach (QGraphicsItem *item, scene->selectedItems())
    {
         if (item->type() == LayerDiagramItem::Type)
         {
             qgraphicsitem_cast<LayerDiagramItem *>(item)->removeArrows();
         }
         scene->removeItem(item);
         delete item;
         isSave = false;
     }
}

void MainWindow::deleteAllItem()
{
    for(int i = 0; i < scene->items().size(); i++)
    {
        scene->items().at(i)->setSelected(true);
    }
    deleteItem();
}

void MainWindow::pointerGroupClicked(int)
{
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::bringToFront()
{
    if (scene->selectedItems().isEmpty())
    {
        return;
    }

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems)
    {
        if (item->zValue() >= zValue && item->type() == LayerDiagramItem::Type)
        {
            zValue = item->zValue() + 0.1;
        }
    }
    selectedItem->setZValue(zValue);
    isSave = false;
}

void MainWindow::sendToBack()
{
    if (scene->selectedItems().isEmpty())
    {
        return;
    }

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems)
    {
        if (item->zValue() <= zValue && item->type() == LayerDiagramItem::Type)
        {
            zValue = item->zValue() - 0.1;
        }
    }
    selectedItem->setZValue(zValue);
    isSave = false;
}

void MainWindow::itemInserted(LayerDiagramItem *item)
{
    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(int(item->getLayer()))->setChecked(false);

    isSave = false;
}

void MainWindow::textInserted(QGraphicsTextItem *)
{
    buttonGroup->button(InsertTextButton)->setChecked(false);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::currentFontChanged(const QFont &)
{
    handleFontChange();
}

void MainWindow::fontSizeChanged(const QString &)
{
    handleFontChange();
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::textColorChanged()
{
    textAction = qobject_cast<QAction *>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/MainWindow/textpointer.png",
                                     qvariant_cast<QColor>(textAction->data())));
    textButtonTriggered();
}

void MainWindow::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/MainWindow/floodfill.png",
                                     qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
}

void MainWindow::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/MainWindow/linecolor.png",
                                     qvariant_cast<QColor>(lineAction->data())));
    lineButtonTriggered();
}

void MainWindow::textButtonTriggered()
{
    scene->setTextColor(qvariant_cast<QColor>(textAction->data()));
}

void MainWindow::fillButtonTriggered()
{
    scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}

void MainWindow::lineButtonTriggered()
{
    scene->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}

void MainWindow::handleFontChange()
{
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    font.setItalic(italicAction->isChecked());
    font.setUnderline(underlineAction->isChecked());

    scene->setFont(font);
}

void MainWindow::itemSelected(QGraphicsItem *item)
{
    DiagramTextItem *textItem =
    qgraphicsitem_cast<DiagramTextItem *>(item);

    QFont font = textItem->font();
    fontCombo->setCurrentFont(font);
    fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
    boldAction->setChecked(font.weight() == QFont::Bold);
    italicAction->setChecked(font.italic());
    underlineAction->setChecked(font.underline());
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About MMALab DLNB"),
                       MochaVersionsInformation::COPYRIGHT_NOTICE);
}

void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));

    QVBoxLayout *otherLayout = new QVBoxLayout;
    QVBoxLayout *visionLayersLayout = new QVBoxLayout;
    QVBoxLayout *commonLayersLayout = new QVBoxLayout;
    QVBoxLayout *dataLayersLayout = new QVBoxLayout;
    QVBoxLayout *lossLayersLayout = new QVBoxLayout;
    QVBoxLayout *neuroLayersLayout = new QVBoxLayout;
    QVBoxLayout *uitillyLayout = new QVBoxLayout;
    QVBoxLayout *backgroundLayout = new QVBoxLayout;

    otherLayout->addWidget(createCellWidget(tr("Blob"), LayerGUI::DataBlob));
    otherLayout->addStretch();
    otherLayout->setSpacing(3);

    visionLayersLayout->addWidget(createCellWidget(tr("Convolution"), LayerGUI::ConvolutionLayer));
    visionLayersLayout->addWidget(createCellWidget(tr("Pooling"), LayerGUI::PoolingLayer));
    visionLayersLayout->addWidget(createCellWidget(tr("SPP"), LayerGUI::SPPLayer));
    visionLayersLayout->addWidget(createCellWidget(tr("LRN"), LayerGUI::LRNLayer));
    visionLayersLayout->addStretch();
    visionLayersLayout->setSpacing(3);

    commonLayersLayout->addWidget(createCellWidget(tr("MVN"), LayerGUI::MVNLayer));
    commonLayersLayout->addWidget(createCellWidget(tr("Reshape"), LayerGUI::ReshapeLayer));
    commonLayersLayout->addWidget(createCellWidget(tr("Slice"), LayerGUI::SliceLayer));
    commonLayersLayout->addWidget(createCellWidget(tr("Inner Product"), LayerGUI::InnerProductLayer));
    commonLayersLayout->addWidget(createCellWidget(tr("Softmax"), LayerGUI::SoftmaxLayer));
    commonLayersLayout->addWidget(createCellWidget(tr("Flatten"), LayerGUI::FlattenLayer));
    commonLayersLayout->addWidget(createCellWidget(tr("Eltwise"), LayerGUI::EltwiseLayer));
    commonLayersLayout->addWidget(createCellWidget(tr("Concat"), LayerGUI::ConcatLayer));
    commonLayersLayout->addWidget(createCellWidget(tr("ArgMax"), LayerGUI::ArgMaxLayer));
    commonLayersLayout->addWidget(createCellWidget(tr("Reduction"), LayerGUI::ReductionLayer));
    commonLayersLayout->addStretch();
    commonLayersLayout->setSpacing(3);

    dataLayersLayout->addWidget(createCellWidget(tr("DummyData"), LayerGUI::DummyDataLayer));
    dataLayersLayout->addWidget(createCellWidget(tr("HDF5Output"), LayerGUI::HDF5OutputLayer));
    dataLayersLayout->addWidget(createCellWidget(tr("HDF5Data"), LayerGUI::HDF5DataLayer));
    dataLayersLayout->addWidget(createCellWidget(tr("WindowData"), LayerGUI::WindowDataLayer));
    dataLayersLayout->addWidget(createCellWidget(tr("ImageData"), LayerGUI::ImageDataLayer));
    dataLayersLayout->addWidget(createCellWidget(tr("MemoryData"), LayerGUI::MemoryDataLayer));
    dataLayersLayout->addWidget(createCellWidget(tr("Data"), LayerGUI::DataLayer));
    dataLayersLayout->addStretch();
    dataLayersLayout->setSpacing(3);

    lossLayersLayout->addWidget(createCellWidget(tr("Hinge Loss"), LayerGUI::HingeLossLayer));
    lossLayersLayout->addWidget(createCellWidget(tr("Infogain Loss"), LayerGUI::InfogainLossLayer));
    lossLayersLayout->addWidget(createCellWidget(tr("Contrastive Loss"), LayerGUI::ContrastiveLossLayer));
    lossLayersLayout->addWidget(createCellWidget(tr("MultinomialLogistic Loss"), LayerGUI::MultinomialLogisticLossLayer));
    lossLayersLayout->addWidget(createCellWidget(tr("SigmoidCrossEntropy Loss"), LayerGUI::SigmoidCrossEntropyLossLayer));
    lossLayersLayout->addWidget(createCellWidget(tr("Euclidean Loss"), LayerGUI::EuclideanLossLayer));
    lossLayersLayout->addWidget(createCellWidget(tr("SoftmaxWithLoss"), LayerGUI::SoftmaxWithLossLayer));
    lossLayersLayout->addWidget(createCellWidget(tr("Accuracy"), LayerGUI::AccuracyLayer));
    lossLayersLayout->addStretch();
    lossLayersLayout->setSpacing(3);

    neuroLayersLayout->addWidget(createCellWidget(tr("PReLU"), LayerGUI::PReLULayer));
    neuroLayersLayout->addWidget(createCellWidget(tr("Threshold"), LayerGUI::ThresholdLayer));
    neuroLayersLayout->addWidget(createCellWidget(tr("TanH"), LayerGUI::TanHLayer));
    neuroLayersLayout->addWidget(createCellWidget(tr("ReLU"), LayerGUI::ReLULayer));
    neuroLayersLayout->addWidget(createCellWidget(tr("Sigmoid"), LayerGUI::SigmoidLayer));
    neuroLayersLayout->addWidget(createCellWidget(tr("Power"), LayerGUI::PowerLayer));
    neuroLayersLayout->addWidget(createCellWidget(tr("Dropout"), LayerGUI::DropoutLayer));
    neuroLayersLayout->addWidget(createCellWidget(tr("Exp"), LayerGUI::ExpLayer));
    neuroLayersLayout->addWidget(createCellWidget(tr("Log"), LayerGUI::LogLayer));
    neuroLayersLayout->addWidget(createCellWidget(tr("AbsVal"), LayerGUI::AbsValLayer));
    neuroLayersLayout->addWidget(createCellWidget(tr("BNLL"), LayerGUI::BNLLLayer));
    neuroLayersLayout->addStretch();
    neuroLayersLayout->setSpacing(3);

    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/MainWindow/textpointer.png")));
    textButton->setIconSize(QSize(30, 30));

    QHBoxLayout  *textLayout = new QHBoxLayout;
    textLayout->addWidget(textButton);
    textLayout->addWidget(new QLabel(tr("Text")));
    textLayout->setContentsMargins(0,0,0,0);
    textLayout->setSpacing(6);

    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);

    uitillyLayout->addWidget(textWidget);
    uitillyLayout->addStretch();
    uitillyLayout->setSpacing(3);


    backgroundButtonGroup = new QButtonGroup(this);
    connect(backgroundButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(backgroundButtonGroupClicked(QAbstractButton*)));

    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Blue Grid"),
                                                           ":/MainWindow/background1.png"));
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Grid"),
                                                           ":/MainWindow/background2.png"));
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Gray Grid"),
                                                           ":/MainWindow/background3.png"));
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("No Grid"),
                                                           ":/MainWindow/background4.png"));

    backgroundLayout->addStretch();
    backgroundLayout->setSpacing(6);


    QWidget *otherWidget = new QWidget;
    QWidget *visionLayersWidget = new QWidget;
    QWidget *commonLayersWidget = new QWidget;
    QWidget *dataLayersWidget = new QWidget;
    QWidget *lossLayersWidget = new QWidget;
    QWidget *neuroLayersWidget = new QWidget;
    QWidget *uitillyWidget = new QWidget;
    QWidget *backgroundWidget = new QWidget;

    otherWidget->setLayout(otherLayout);
    visionLayersWidget->setLayout(visionLayersLayout);
    commonLayersWidget->setLayout(commonLayersLayout);
    dataLayersWidget->setLayout(dataLayersLayout);
    lossLayersWidget->setLayout(lossLayersLayout);
    neuroLayersWidget->setLayout(neuroLayersLayout);
    uitillyWidget->setLayout(uitillyLayout);
    backgroundWidget->setLayout(backgroundLayout);


    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(lossLayersWidget->sizeHint().width());
    toolBox->setMaximumWidth(lossLayersWidget->sizeHint().width());

    toolBox->addItem(otherWidget, tr("Other"));
    toolBox->addItem(visionLayersWidget, tr("Vision Layers"));
    toolBox->addItem(commonLayersWidget, tr("Common Layers"));
    toolBox->addItem(dataLayersWidget, tr("Data Layers"));
    toolBox->addItem(lossLayersWidget, tr("Loss Layers"));
    toolBox->addItem(neuroLayersWidget, tr("Neuro Layers"));
    toolBox->addItem(uitillyWidget, tr("Uitilly"));
    toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}

void MainWindow::createActions()
{
    toFrontAction = new QAction(QIcon(":/MainWindow/bringtofront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, SIGNAL(triggered()), this, SLOT(bringToFront()));

    sendBackAction = new QAction(QIcon(":/MainWindow/sendtoback.png"), tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+B"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, SIGNAL(triggered()), this, SLOT(sendToBack()));

    deleteAction = new QAction(QIcon(":/MainWindow/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    boldAction = new QAction(tr("Bold"), this);
    boldAction->setCheckable(true);
    QPixmap pixmap(":/MainWindow/bold.png");
    boldAction->setIcon(QIcon(pixmap));
    boldAction->setShortcut(tr("Ctrl+B"));
    connect(boldAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    italicAction = new QAction(QIcon(":/MainWindow/italic.png"), tr("Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    underlineAction = new QAction(QIcon(":/MainWindow/underline.png"), tr("Underline"), this);
    underlineAction->setCheckable(true);
    underlineAction->setShortcut(tr("Ctrl+U"));
    connect(underlineAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    aboutAction = new QAction(QIcon(":/MainWindow/about.png"), tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    //export NN
    exportAction = new QAction(QIcon(":/MainWindow/export.png"),
                                tr("Export NN"), this);
    exportAction->setShortcut(tr("Ctrl+S"));
    exportAction->setStatusTip(tr("Export NN"));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportNN()));

    //import NN
    importAction = new QAction(QIcon(":/MainWindow/import.png"),
                                tr("Import NN"), this);
    importAction->setShortcut(tr("Ctrl+O"));
    importAction->setStatusTip(tr("Import NN"));
    connect(importAction, SIGNAL(triggered()), this, SLOT(importNN()));

    //time
    timeAction = new QAction(QIcon(":/MainWindow/time.png"),
                                tr("Performance"), this);
    timeAction->setShortcut(tr("Ctrl+1"));
    timeAction->setStatusTip(tr("Performance"));
    connect(timeAction, SIGNAL(triggered()), this, SLOT(time()));

    //train
    trainAction = new QAction(QIcon(":/MainWindow/train.png"),
                                tr("Train"), this);
    trainAction->setShortcut(tr("Ctrl+2"));
    trainAction->setStatusTip(tr("Train"));
    connect(trainAction, SIGNAL(triggered()), this, SLOT(train()));

    //test
    testAction = new QAction(QIcon(":/MainWindow/test.png"),
                                tr("Test"), this);
    testAction->setShortcut(tr("Ctrl+3"));
    testAction->setStatusTip(tr("Test"));
    connect(testAction, SIGNAL(triggered()), this, SLOT(test()));

    //solver
    solverAction = new QAction(QIcon(":/MainWindow/solver.png"),
                                tr("Solver"), this);
    solverAction->setShortcut(tr("Ctrl+4"));
    solverAction->setStatusTip(tr("Solver"));
    connect(solverAction, SIGNAL(triggered()), this, SLOT(solver()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(importAction);
    fileMenu->addAction(exportAction);
    fileMenu->addAction(timeAction);
    fileMenu->addAction(trainAction);
    fileMenu->addAction(testAction);
    fileMenu->addAction(solverAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolbars()
{
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(importAction);
    editToolBar->addAction(exportAction);
    editToolBar->addAction(timeAction);
    editToolBar->addAction(trainAction);
    editToolBar->addAction(testAction);
    editToolBar->addAction(solverAction);
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);

    fontCombo = new QFontComboBox();
    connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(currentFontChanged(QFont)));

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
    {
        fontSizeCombo->addItem(QString().setNum(i));
    }
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(fontSizeChanged(QString)));

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(":/MainWindow/textpointer.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    connect(fontColorToolButton, SIGNAL(clicked()),
            this, SLOT(textButtonTriggered()));

    fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()), Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/MainWindow/floodfill.png", Qt::white));
    connect(fillColorToolButton, SIGNAL(clicked()),
            this, SLOT(fillButtonTriggered()));

    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()), Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/MainWindow/linecolor.png", Qt::black));
    connect(lineColorToolButton, SIGNAL(clicked()),
            this, SLOT(lineButtonTriggered()));/**/

    textToolBar = addToolBar(tr("Font"));
    textToolBar->addWidget(fontCombo);
    textToolBar->addWidget(fontSizeCombo);
    textToolBar->addAction(boldAction);
    textToolBar->addAction(italicAction);
    textToolBar->addAction(underlineAction);

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fontColorToolButton);
    //colorToolBar->addWidget(fillColorToolButton);
    //colorToolBar->addWidget(lineColorToolButton);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/MainWindow/pointer.png"));
    pointerButton->setToolTip(tr("Pointer"));
    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/MainWindow/linepointer.png"));
    linePointerButton->setToolTip(tr("LinePointer : the bottom and the top blob could not be the same"));
//    QToolButton *dottedlinePointerButton = new QToolButton;
//    dottedlinePointerButton->setCheckable(true);
//    dottedlinePointerButton->setIcon(QIcon(":/MainWindow/dottedlinepointer.png"));
//    dottedlinePointerButton->setToolTip(tr("DotLinePointer : the bottom and the top blob could be the same"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton, int(DiagramScene::InsertLine));
//    pointerTypeGroup->addButton(dottedlinePointerButton, int(DiagramScene::InsertDottedLine));
    connect(scene, SIGNAL(sendIsSave(bool)), this, SLOT(receiveIsSave(bool)));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
//    pointerToolbar->addWidget(dottedlinePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);
}

QWidget *MainWindow::createBackgroundCellWidget(const QString &text, const QString &image)
{
    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(30, 30));
    button->setCheckable(true);
    backgroundButtonGroup->addButton(button);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(button);
    layout->addWidget(new QLabel(text));
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(6);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

QWidget *MainWindow::createCellWidget(const QString &text, LayerGUI::Layers type)
{

    LayerDiagramItem item(type, itemMenu, 0);
    QIcon icon(item.image());

    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(30, 30));
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));

    QHBoxLayout  *layout = new QHBoxLayout;
    layout->addWidget(button);
    layout->addWidget(new QLabel(text));
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(6);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i)
    {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
        {
            colorMenu->setDefaultAction(action);
        }
    }
    return colorMenu;
}

QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}

int MainWindow::exportNN()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("export to caffe prototxt file"),
                                                    "./NN",
                                                    tr("caffe prototxt file(*.prototxt)"));
    if (!fileName.isEmpty())
    {
        MMALab::NNModel* model = new MMALab::NNModel("NN");
        for(int i = scene->items().count()-1; i >= 0; i--)
        {
            QGraphicsItem *item = scene->items().at(i);
            if (item->type() == LayerDiagramItem::Type)
            {
                LayerDiagramItem *layerItem = qgraphicsitem_cast<LayerDiagramItem *>(item);
                layerItem->setBlob();
            }
        }
        for(int i = 0; i < scene->items().count(); i++)
        {
            QGraphicsItem *item = scene->items().at(i);
            if (item->type() == LayerDiagramItem::Type)
            {
                //scene->removeItem(item);
                LayerDiagramItem *layerItem = qgraphicsitem_cast<LayerDiagramItem *>(item);
                layerItem->setTopsBottoms();
            }
        }
        for(int i = scene->items().count()-1; i >= 0; i--)
        {
            QGraphicsItem *item = scene->items().at(i);
            if (item->type() == LayerDiagramItem::Type)
            {
                LayerDiagramItem *layerItem = qgraphicsitem_cast<LayerDiagramItem *>(item);
                if(layerItem->getLayer() != LayerGUI::Layers::DataBlob)
                    model->addLayer((MMALab::BaseLayer*)layerItem->getLayerObject());
            }
        }
        model->convert2CaffeFormat(fileName.toStdString());
        isSave = true;
    }
    else
    {
        return QMessageBox::Cancel;
    }
}

void MainWindow::importNN()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("import to caffe prototxt file"),
                                                    "./NN",
                                                    tr("caffe prototxt file(*.prototxt)"));
    if (!fileName.isEmpty())
    {
        deleteAllItem();
        mLayerNode.clear();
        myNodeMap.clear();
        vector<LayerNode>().swap(mLayerNode);
        scene->clearPosVector();

        CaffeTools* ct = new CaffeTools();
        ct->parseNetProTextFile(fileName.toStdString());
        NetParameter* mNetParam = new NetParameter();
        *mNetParam = ct->getNetParam();
        for (int i = 0; i < mNetParam->layer_size(); i++)
        {
            LayerNode layerNodeTemp;
            layerNodeTemp.mLayerName = mNetParam->layer(i).name();
            layerNodeTemp.mLayerType = mNetParam->layer(i).type();
            for(int j = 0; j < mNetParam->layer(i).top_size(); j++)
            {
                layerNodeTemp.mLayerTop.push_back(mNetParam->layer(i).top(j));
            }
            for(int j = 0; j < mNetParam->layer(i).bottom_size(); j++)
            {
                layerNodeTemp.mLayerBottom.push_back(mNetParam->layer(i).bottom(j));
            }
            mLayerNode.push_back(layerNodeTemp);
            myNodeMap.insert(IntIntPair(i,0));
        }

        //Sorting
        for (int i = 0; i < mNetParam->layer_size(); i++)
        {
            sortLayers(i);
        }
        deleteSpacing();
        reviseSorting();

        for (int i = 0; i < mNetParam->layer_size(); i++)
        {
            scene->addNeuralNetwork(mNetParam->layer(i), i, myNodeMap.at(i));
        }

        for(unsigned int i = 0; i < myNodeMap.size(); i++)
        {
            LayerNode layerNodeTemp;
            layerNodeTemp = mLayerNode.at(i);
            for(unsigned int j = 0 ; j < layerNodeTemp.mLayerTop.size(); j++)
            {
                scene->addLine(i, layerNodeTemp.mLayerTop[j]);
            }
            for(unsigned int j = 0 ; j < layerNodeTemp.mLayerBottom.size(); j++)
            {
                scene->addLine(layerNodeTemp.mLayerBottom[j], i);
            }
        }
        view->centerOn(10000/2,0);
        isSave = true;
    }
}

void MainWindow::time()
{
    TimeDialog* mTimeDialog = new TimeDialog();
    connect (this, SIGNAL(sendMainWindowCloseSignal()), mTimeDialog, SLOT(receiveMainWindowCloseSignal()));
    mTimeDialog->show();
}

void MainWindow::train()
{
    TrainDialog* mTrainDialog = new TrainDialog();
    connect (this, SIGNAL(sendMainWindowCloseSignal()), mTrainDialog, SLOT(receiveMainWindowCloseSignal()));
    mTrainDialog->show();
}

void MainWindow::test()
{
    TestDialog* mTestDialog = new TestDialog();
    connect (this, SIGNAL(sendMainWindowCloseSignal()), mTestDialog, SLOT(receiveMainWindowCloseSignal()));
    mTestDialog->show();
}

void MainWindow::solver()
{
    SolverDialog* mSolverDialog = new SolverDialog();
    connect (this, SIGNAL(sendMainWindowCloseSignal()), mSolverDialog, SLOT(receiveMainWindowCloseSignal()));
    mSolverDialog->show();
}

void MainWindow::sortLayers(int num)
{
    LayerNode layerNodeTemp = mLayerNode.at(num);
    myNodeMap.at(num) += 1;
    for(unsigned int i = 0 ; i < layerNodeTemp.mLayerBottom.size(); i++)
    {
        for(unsigned int j = 0 ; j < myNodeMap.size(); j++)
        {
            LayerNode layerNodeTemp2 = mLayerNode.at(j);

            if(!scene->computationIsInPlace(layerNodeTemp2.mLayerType))
            {
                for(unsigned int k = 0 ; k < layerNodeTemp2.mLayerTop.size(); k++)
                {
                    if(layerNodeTemp.mLayerBottom[i] == layerNodeTemp2.mLayerTop[k])
                    {
                        sortLayers(j);
                    }
                }
            }
        }
    }


}
void MainWindow::deleteSpacing()
{
    int maxCount = findMaxCount();
    for(int i = 1; i <= maxCount; i++)
    {
        bool hasCount = false;
        for(unsigned int j = 0; j < myNodeMap.size(); j++)
        {
            if(myNodeMap.at(j) == i)
            {
                hasCount = true;
                break;
            }
        }
        if(!hasCount)
        {
            for(unsigned int j = 0; j < myNodeMap.size(); j++)
            {
                if(myNodeMap.at(j) > i)
                {
                    myNodeMap.at(j) -= 1;
                }
            }
            maxCount -= 1;
            i -= 1;
        }
    }
    maxCount = findMaxCount();
    for(unsigned int i = 0; i < myNodeMap.size(); i++)
    {
        myNodeMap.at(i) = abs(myNodeMap.at(i) - maxCount);
    }
}

void MainWindow::reviseSorting()
{
    //int maxCount = findMaxCount();
    for(unsigned int i = 0; i < myNodeMap.size(); i++)
    {
        if(myNodeMap.at(i) > 0)
        {
            LayerNode layerNodeTemp;
            layerNodeTemp = mLayerNode.at(i);
            if(layerNodeTemp.mLayerBottom.size() > 0)
            {
                 for(unsigned int j = 0; j < myNodeMap.size(); j++)
                 {
                     LayerNode layerNodeTemp2 = mLayerNode.at(j);
                     if(layerNodeTemp2.mLayerType != "ReLU"  && layerNodeTemp2.mLayerType !=  "Dropout")
                     {
                         for(unsigned int k = 0 ; k < layerNodeTemp2.mLayerTop.size(); k++)
                         {
                             if(layerNodeTemp.mLayerBottom[0] == layerNodeTemp2.mLayerTop[k])
                             {
                                 myNodeMap.at(i) = myNodeMap.at(j) + 1;
                                 break;
                             }
                         }
                     }
                 }
            }
            else
            {
                myNodeMap.at(i) = 0;
            }
        }
    }
}

int MainWindow::findMaxCount()
{
    int maxCount = 0;
    for(unsigned int i = 0; i < myNodeMap.size(); i++)
    {
        if(myNodeMap.at(i) > maxCount)
        {
            maxCount = myNodeMap.at(i);
        }
    }
    return maxCount;
}

