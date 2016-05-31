#include "TestDialog.h"

TestDialog::TestDialog()
{
    profile = new QSettings("MMALab","testProfile");

    regex = new QRegExp("Batch\\s(\\d*),\\s(\\w*)\\s=\\s(\\d*.*\\d*)");

    int gpusCount = 0;
    cudaDeviceProp prop;

    mainLayout = new QGridLayout;
    gpusLayout = new QHBoxLayout;
    modelLayout = new QHBoxLayout;

    mainLayout->addWidget(new QLabel(tr("CaffeLocal:")), 0, 0);
    lineEditCaffeLocal = new QLineEdit(profile->value("CaffeLocal").toString());
    mainLayout->addWidget(lineEditCaffeLocal, 0, 1);
    pushButtonCaffeLocal = new QPushButton(tr("Open"), this);
    connect(pushButtonCaffeLocal, SIGNAL(clicked()), this, SLOT(getCaffeLocal()));
    mainLayout->addWidget(pushButtonCaffeLocal, 0, 2);

    mainLayout->addWidget(new QLabel(tr("ModelLocal:")), 1, 0);
    lineEditModelLocal = new QLineEdit(profile->value("ModelLocal").toString());
    mainLayout->addWidget(lineEditModelLocal, 1, 1);
    pushButtonModelLocalOpen = new QPushButton(tr("Open"));
    connect(pushButtonModelLocalOpen, SIGNAL(clicked()), this, SLOT(getModelLocalOpen()));
    modelLayout->addWidget(pushButtonModelLocalOpen);
    mainLayout->addLayout(modelLayout, 1, 2);

    mainLayout->addWidget(new QLabel(tr("WeightsLocal:")), 2, 0);
    lineEditWeightsLocal = new QLineEdit(profile->value("WeightsLocal").toString());
    mainLayout->addWidget(lineEditWeightsLocal, 2, 1);
    pushButtonWeightsLocal = new QPushButton(tr("Open"));
    connect(pushButtonWeightsLocal, SIGNAL(clicked()), this, SLOT(getWeightsLocal()));
    mainLayout->addWidget(pushButtonWeightsLocal, 2, 2);

    mainLayout->addWidget(new QLabel(tr("GpuSelect:")), 3, 0);
    cudaGetDeviceCount(&gpusCount);
    for(int i = 0 ; i < gpusCount ; i++)
    {
        cudaGetDeviceProperties(&prop, i);
        checkBoxGpus.push_back(new QCheckBox(prop.name));
        gpusLayout->addWidget(checkBoxGpus.at(i));
    }
    mainLayout->addLayout(gpusLayout, 3, 1);

    mainLayout->addWidget(new QLabel(tr("SaveLogLocal:")), 4, 0);
    lineEditSaveLogLocal = new QLineEdit(profile->value("SaveLogLocal").toString());
    mainLayout->addWidget(lineEditSaveLogLocal, 4, 1);
    pushButtonSaveLogLocal = new QPushButton(tr("Open"));
    connect(pushButtonSaveLogLocal, SIGNAL(clicked()), this, SLOT(getSaveLogLocal()));
    mainLayout->addWidget(pushButtonSaveLogLocal, 4, 2);

    pushButtonRun = new QPushButton(tr("Run"));
    connect(pushButtonRun, SIGNAL(clicked()), this, SLOT(run()));
    mainLayout->addWidget(pushButtonRun, 5, 0);
    pushButtonSaveProfile = new QPushButton(tr("Save Profile"));
    connect(pushButtonSaveProfile, SIGNAL(clicked()), this, SLOT(saveProfile()));
    mainLayout->addWidget(pushButtonSaveProfile, 5, 2);

    createQwt();

    plainTextEditShowLog = new QPlainTextEdit;
    mainLayout->addWidget(plainTextEditShowLog, 6, 2);

    setWindowFlags(Qt::Widget);
    setWindowTitle(tr("TestDialog"));
    setLayout(mainLayout);
    resize((QApplication::desktop()->width()*0.9), (QApplication::desktop()->height()*0.5));
}

void TestDialog::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton dialogReturn;

    if(pushButtonRun->isEnabled() == false)
    {
        dialogReturn = QMessageBox::warning(NULL,
                                            tr("Close window"), tr("Testing is not yet complete, do you want to close?"),
                                            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        if(dialogReturn == QMessageBox::Yes)
        {
            receiveEndSignal(true);
            emit closeSignal(true);
            ct->cancelAction(logFileLocalTemp.toStdString());
            mShowLogMessageThread->msleep(1);
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        event->accept();
    }
}
void TestDialog::receiveMainWindowCloseSignal()
{
    close();
}

void TestDialog::getCaffeLocal()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("select to caffe executable file"),
                                                    "../CaffeToolsLib/caffe/build/tools/",
                                                    tr("executable file(*)"));
    if (!fileUrl.isEmpty())
    {
        lineEditCaffeLocal->setText(fileUrl);
    }
}

void TestDialog::getModelLocalOpen()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("select to caffe model prototxt file"),
                                                    "../CaffeToolsLib/testModel/",
                                                    tr("caffe prototxt file(*.prototxt)"));

    if (!fileUrl.isEmpty())
    {
        lineEditModelLocal->setText(fileUrl);
    }
}

void TestDialog::getWeightsLocal()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("select to caffe weights model file"),
                                                    "/home",
                                                    tr("caffe model file(*.caffemodel)"));

    if (!fileUrl.isEmpty())
    {
        lineEditWeightsLocal->setText(fileUrl);
    }
}

void TestDialog::getSaveLogLocal()
{
    QString fileUrl = QFileDialog::getExistingDirectory(this, tr("select to log file save local"),
                                                    "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!fileUrl.isEmpty())
    {
        lineEditSaveLogLocal->setText(fileUrl);
    }
}

void TestDialog::run()
{
    QDir dir;
    dir.setPath(dir.absolutePath() + "/Temp");

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeInfo = currentDateTime.toString("yyyyMMddhhmmss");
    logFileLocalTemp = dir.absolutePath() + "/" + currentDateTimeInfo + ".log";

    QCheckBox* tempCheckBox;
    QString gpusSelect = "";

    accuracyRunCount = 0;
    lossRunCount = 0;

    plainTextEditShowLog->clear();
    pointsAccuracy.clear();
    pointsLoss.clear();
    curveLoss->setSamples(pointsLoss);
    curveAccuracy->setSamples(pointsAccuracy);
    plot->replot();

    pushButtonRun->setEnabled(false);
    lineEditSaveLogLocal->setEnabled(false);
    pushButtonSaveLogLocal->setEnabled(false);

    mShowLogMessageThread = new ParseLog(lineEditSaveLogLocal->text() + "/CaffeTest.log",
                                         logFileLocalTemp,
                                         *ct);

    connect (mShowLogMessageThread,SIGNAL(sendLogMessage(QString)),this,SLOT(receiveLogMessage(QString)));
    connect (mShowLogMessageThread,SIGNAL(sendEndSignal(bool)),this,SLOT(receiveEndSignal(bool)));
    connect(this,SIGNAL(closeSignal(bool)),mShowLogMessageThread,SLOT(closeSlot(bool)));
    connect(mShowLogMessageThread,SIGNAL(finished()),mShowLogMessageThread,SLOT(deleteLater()));

    mShowLogMessageThread->start();

    for(int i = 0 ; i < checkBoxGpus.size(); i++)
    {
        tempCheckBox = checkBoxGpus.at(i);
        if(tempCheckBox->isChecked())
        {
            gpusSelect += QString::number(i);
            gpusSelect += ",";
        }
    }
    gpusSelect.remove((gpusSelect.length()-1), 1);

    ct->test(lineEditCaffeLocal->text().toStdString(), lineEditModelLocal->text().toStdString(),
             lineEditWeightsLocal->text().toStdString(), gpusSelect.toStdString(),
             logFileLocalTemp.toStdString());
}

void TestDialog::saveProfile()
{
    profile->setValue("CaffeLocal", QVariant(lineEditCaffeLocal->text()));
    profile->setValue("ModelLocal", QVariant(lineEditModelLocal->text()));
    profile->setValue("WeightsLocal", QVariant(lineEditWeightsLocal->text()));
    profile->setValue("SaveLogLocal", QVariant(lineEditSaveLogLocal->text()));

    QMessageBox::about(NULL, "Remind", "Save profile done.");
}

void TestDialog::receiveLogMessage(QString message)
{
    plainTextEditShowLog->insertPlainText(message+'\n');
    plainTextEditShowLog->moveCursor(QTextCursor::End);

    position = message.indexOf(*regex);
    if(position!=-1)
    {
        if(regex->cap(2)=="accuracy")
        {
            accuracyRunCount++;
            if(accuracyRunCount%10 == 0 || accuracyRunCount == 1)
            {
                pointsAccuracy << QPointF(regex->cap(1).toInt(), (regex->cap(3).toDouble())*100);
                curveAccuracy->setSamples(pointsAccuracy);
                plot->replot();
            }
        }
        else if(regex->cap(2)=="loss")
        {
            lossRunCount++;
            if(lossRunCount %10 == 0 || lossRunCount == 1)
            {
                pointsLoss << QPointF(regex->cap(1).toInt(), regex->cap(3).toDouble());
                curveLoss->setSamples(pointsLoss);
                plot->replot();
            }
        }
    }
}
void TestDialog::receiveEndSignal(bool signal)
{
    pushButtonRun->setEnabled(signal);
    lineEditSaveLogLocal->setEnabled(signal);
    pushButtonSaveLogLocal->setEnabled(signal);
}

void TestDialog::createQwt()
{
    QwtLegend *legend = new QwtLegend;
    legend->setDefaultItemMode(QwtLegendData::Checkable);

    plot = new QwtPlot();
    plot->setTitle("Test Plot");
    plot->setCanvasBackground(Qt::white);
    plot->insertLegend(legend, QwtPlot::RightLegend);

    plot->setAxisTitle(QwtPlot::xBottom, tr("Batch"));
    plot->setAxisTitle(QwtPlot::yLeft, tr("Loss"));
    plot->setAxisTitle(QwtPlot::yRight, tr("Accuracy(%)"));
    plot->enableAxis(QwtPlot::yRight, true);

    connect(legend, SIGNAL(checked(const QVariant &, bool, int)),
            this, SLOT(legendChecked(const QVariant &, bool)));

    grid = new QwtPlotGrid();
    grid->attach(plot);

    curveAccuracy = new QwtPlotCurve();
    curveAccuracy->setTitle("Accuracy Points");
    curveAccuracy->setPen(Qt::blue, 4);
    curveAccuracy->setYAxis(QwtPlot::yRight);
    curveAccuracy->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    curveLoss = new QwtPlotCurve();
    curveLoss->setTitle("Loss Points");
    curveLoss->setPen(Qt::green, 4);
    curveLoss->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    symbolAccuracy = new QwtSymbol(QwtSymbol::Ellipse,
        QBrush(Qt::red), QPen(Qt::red, 2), QSize(5, 5));
    curveAccuracy->setSymbol(symbolAccuracy);

    symbolLoss = new QwtSymbol(QwtSymbol::Ellipse,
        QBrush(Qt::gray), QPen(Qt::gray, 2), QSize(5, 5));
    curveLoss->setSymbol(symbolLoss);

    picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
                                   QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
                                   plot->canvas());

    picker->setStateMachine(new QwtPickerDragPointMachine());
    picker->setRubberBandPen(QPen(QColor(Qt::black)));
    picker->setTrackerPen(QColor(Qt::black));

    curveAccuracy->attach(plot);
    curveLoss->attach(plot);

    showCurve(curveAccuracy, true);
    showCurve(curveLoss, true);

    mainLayout->addWidget(plot, 6, 0, 1, 2);
}
void TestDialog::legendChecked(const QVariant &itemInfo, bool isOn)
{
    QwtPlotItem *plotItem = plot->infoToItem(itemInfo);
    if(plotItem)
    {
        plotItem->setVisible(isOn);
    }
    plot->replot();
}
void TestDialog::showCurve(QwtPlotItem *item, bool IsOn)
{
    QwtLegend *legend = qobject_cast<QwtLegend *>(plot->legend());

    QList<QWidget *> legendWidgets =
        legend->legendWidgets(plot->itemToInfo(item));

    if (legendWidgets.size() == 1)
    {
        QwtLegendLabel *legendLabel =
            qobject_cast<QwtLegendLabel *>(legendWidgets[0]);

        if (legendLabel)
            legendLabel->setChecked(IsOn);
    }
}
