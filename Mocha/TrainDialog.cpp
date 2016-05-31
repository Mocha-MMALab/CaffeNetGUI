#include "TrainDialog.h"

TrainDialog::TrainDialog()
{
    profile = new QSettings("MMALab","trainProfile");

    regexTrain = new QRegExp("Iteration\\s(\\d*),\\s(\\w*)\\s=\\s(\\d*.*\\d*)");
    regexTest = new QRegExp("Test\\s*\\w*\\s*\\w*\\s*#\\d*:\\s*(\\w*)\\s*=\\s*(\\d*.\\d*)");
    regexFlag = new QRegExp("Iteration\\s*(\\d*),\\s*Testing net");

    int gpusCount = 0;
    cudaDeviceProp prop;

    mainLayout = new QGridLayout;
    gpusLayout = new QHBoxLayout;
    solverLayout = new QHBoxLayout;

    mainLayout->addWidget(new QLabel(tr("CaffeLocal:")), 0, 0);
    lineEditCaffeLocal = new QLineEdit(profile->value("CaffeLocal").toString());
    mainLayout->addWidget(lineEditCaffeLocal, 0, 1);
    pushButtonCaffeLocal = new QPushButton(tr("Open"), this);
    connect(pushButtonCaffeLocal, SIGNAL(clicked()), this, SLOT(getCaffeLocal()));
    mainLayout->addWidget(pushButtonCaffeLocal, 0, 2);

    mainLayout->addWidget(new QLabel(tr("SolverLocal:")), 1, 0);
    lineEditSolverLocal = new QLineEdit(profile->value("SolverLocal").toString());
    mainLayout->addWidget(lineEditSolverLocal, 1, 1);
    pushButtonSolverLocalOpen = new QPushButton(tr("Open"));
    connect(pushButtonSolverLocalOpen, SIGNAL(clicked()), this, SLOT(getSolverLocalOpen()));
    solverLayout->addWidget(pushButtonSolverLocalOpen);
    mainLayout->addLayout(solverLayout, 1, 2);

    mainLayout->addWidget(new QLabel(tr("SnapshotLocal:")), 2, 0);
    lineEditSnapshotLocal = new QLineEdit(profile->value("SnapshotLocal").toString());
    mainLayout->addWidget(lineEditSnapshotLocal, 2, 1);
    pushButtonSnapshotLocal = new QPushButton(tr("Open"));
    connect(pushButtonSnapshotLocal, SIGNAL(clicked()), this, SLOT(getSnapshotLocal()));
    mainLayout->addWidget(pushButtonSnapshotLocal, 2, 2);

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
    setWindowTitle(tr("TrainDialog"));
    setLayout(mainLayout);
    resize((QApplication::desktop()->width()*0.9), (QApplication::desktop()->height()*0.5));
}

void TrainDialog::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton dialogReturn;

    if(pushButtonRun->isEnabled() == false)
    {
        dialogReturn = QMessageBox::warning(NULL,
                                            tr("Close window"), tr("Training is not yet complete, do you want to close?"),
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
void TrainDialog::receiveMainWindowCloseSignal()
{
    close();
}

void TrainDialog::getCaffeLocal()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("select to caffe executable file"),
                                                    "../CaffeToolsLib/caffe/build/tools/",
                                                    tr("executable file(*)"));
    if (!fileUrl.isEmpty())
    {
        lineEditCaffeLocal->setText(fileUrl);
    }
}

void TrainDialog::getSolverLocalOpen()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("select to caffe solver prototxt file"),
                                                    "../CaffeToolsLib/testModel/",
                                                    tr("caffe prototxt file(*.prototxt)"));
    if (!fileUrl.isEmpty())
    {
        lineEditSolverLocal->setText(fileUrl);
    }
}

void TrainDialog::getSnapshotLocal()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("select to caffe snapshot solverstate file"),
                                                    "/home",
                                                    tr("caffe solverstate file(*.solverstate)"));

    if (!fileUrl.isEmpty())
    {
        lineEditSnapshotLocal->setText(fileUrl);
    }
}

void TrainDialog::getSaveLogLocal()
{
    QString fileUrl = QFileDialog::getExistingDirectory(this, tr("select to log file save local"),
                                                    "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!fileUrl.isEmpty())
    {
        lineEditSaveLogLocal->setText(fileUrl);
    }
}

void TrainDialog::run()
{
    QDir dir;
    dir.setPath(dir.absolutePath() + "/Temp");

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeInfo = currentDateTime.toString("yyyyMMddhhmmss");
    logFileLocalTemp = dir.absolutePath() + "/" + currentDateTimeInfo + ".log";

    QCheckBox* tempCheckBox;
    QString gpusSelect = "";

    lossRunCount = 0;
    lrRunCount = 0;

    plainTextEditShowLog->clear();
    pointsTrainLoss.clear();
    pointsTrainLr.clear();
    pointsTestAccuracy.clear();
    pointsTestLoss.clear();
    curveTestAccuracy->setSamples(pointsTestAccuracy);
    curveTestLoss->setSamples(pointsTestLoss);
    curveTrainLoss->setSamples(pointsTrainLoss);
    curveTrainLr->setSamples(pointsTrainLr);
    plot->replot();

    pushButtonRun->setEnabled(false);
    lineEditSaveLogLocal->setEnabled(false);
    pushButtonSaveLogLocal->setEnabled(false);

    mShowLogMessageThread = new ParseLog(lineEditSaveLogLocal->text() + "/CaffeTrain.log",
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

    ct->train(lineEditCaffeLocal->text().toStdString(), lineEditSolverLocal->text().toStdString(),
              lineEditSnapshotLocal->text().toStdString(), gpusSelect.toStdString(),
              logFileLocalTemp.toStdString());
}

void TrainDialog::saveProfile()
{
    profile->setValue("CaffeLocal", QVariant(lineEditCaffeLocal->text()));
    profile->setValue("SolverLocal", QVariant(lineEditSolverLocal->text()));
    profile->setValue("SnapshotLocal", QVariant(lineEditSnapshotLocal->text()));
    profile->setValue("SaveLogLocal", QVariant(lineEditSaveLogLocal->text()));

    QMessageBox::about(NULL, "Remind", "Save profile done.");
}

void TrainDialog::receiveLogMessage(QString message)
{
    plainTextEditShowLog->insertPlainText(message+'\n');
    plainTextEditShowLog->moveCursor(QTextCursor::End);

    position = message.indexOf(*regexTrain);
    if(position!=-1)
    {
        if(regexTrain->cap(2)=="loss")
        {
            lossRunCount++;
            if(lossRunCount % 5 == 0 || lossRunCount == 1)
            {
                pointsTrainLoss << QPointF(regexTrain->cap(1).toInt(), regexTrain->cap(3).toDouble());
                curveTrainLoss->setSamples(pointsTrainLoss);
                plot->replot();
            }
        }
        else if(regexTrain->cap(2)=="lr")
        {
            lrRunCount++;
            if(lrRunCount% 5 == 0 || lrRunCount == 1)
            {
                pointsTrainLr << QPointF(regexTrain->cap(1).toInt(), regexTrain->cap(3).toDouble());
                curveTrainLr->setSamples(pointsTrainLr);
                plot->replot();
            }
        }
    }

    position = message.indexOf(*regexFlag);
    if(position!=-1)
    {
        currentNumber = regexFlag->cap(1).toInt();
    }

    position = message.indexOf(*regexTest);
    if(position!=-1)
    {
        if(regexTest->cap(1)=="accuracy")
        {
            pointsTestAccuracy << QPointF(currentNumber, (regexTest->cap(2).toDouble())*100);
            curveTestAccuracy->setSamples(pointsTestAccuracy);
            plot->replot();
        }
        else if(regexTest->cap(1)=="loss")
        {
            pointsTestLoss << QPointF(currentNumber, regexTest->cap(2).toDouble());
            curveTestLoss->setSamples(pointsTestLoss);
            plot->replot();
        }
    }
}
void TrainDialog::receiveEndSignal(bool signal)
{
    pushButtonRun->setEnabled(signal);
    lineEditSaveLogLocal->setEnabled(signal);
    pushButtonSaveLogLocal->setEnabled(signal);
}

void TrainDialog::createQwt()
{
    QwtLegend *legend = new QwtLegend;
    legend->setDefaultItemMode(QwtLegendData::Checkable);

    plot = new QwtPlot();
    plot->setTitle("Train Plot");
    plot->setCanvasBackground(Qt::white);
    plot->insertLegend(legend, QwtPlot::RightLegend);

    plot->setAxisTitle(QwtPlot::xBottom, tr("Iteration"));
    plot->setAxisTitle(QwtPlot::yLeft, tr("Others"));
    plot->setAxisTitle(QwtPlot::yRight, tr("Accuracy(%)"));
    plot->enableAxis(QwtPlot::yRight, true);

    connect(legend, SIGNAL(checked(const QVariant &, bool, int)),
            this, SLOT(legendChecked(const QVariant &, bool)));

    grid = new QwtPlotGrid();
    grid->attach(plot);

    curveTrainLoss = new QwtPlotCurve();
    curveTrainLoss->setTitle("Train Loss Points");
    curveTrainLoss->setPen("#FF8C00", 4);
    curveTrainLoss->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    curveTrainLr = new QwtPlotCurve();
    curveTrainLr->setTitle("Train Lr Points");
    curveTrainLr->setPen("#483D8B", 4);
    curveTrainLr->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    curveTestAccuracy = new QwtPlotCurve();
    curveTestAccuracy->setTitle("Test Accuracy Points");
    curveTestAccuracy->setPen("#00CED1", 4);
    curveTestAccuracy->setYAxis(QwtPlot::yRight);
    curveTestAccuracy->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    curveTestLoss = new QwtPlotCurve();
    curveTestLoss->setTitle("Test Loss Points");
    curveTestLoss->setPen("#FF1493", 4);
    curveTestLoss->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    symbolTrainLoss = new QwtSymbol(QwtSymbol::Ellipse,
        QBrush(Qt::darkRed), QPen(Qt::darkRed, 2), QSize(5, 5));
    curveTrainLoss->setSymbol(symbolTrainLoss);

    symbolTrainLr = new QwtSymbol(QwtSymbol::Ellipse,
        QBrush(Qt::darkMagenta), QPen(Qt::darkMagenta, 2), QSize(5, 5));
    curveTrainLr->setSymbol(symbolTrainLr);

    symbolTestAccuracy = new QwtSymbol(QwtSymbol::Ellipse,
        QBrush(Qt::blue), QPen(Qt::blue, 2), QSize(5, 5));
    curveTestAccuracy->setSymbol(symbolTestAccuracy);

    symbolTestLoss = new QwtSymbol(QwtSymbol::Ellipse,
        QBrush(Qt::gray), QPen(Qt::gray, 2), QSize(5, 5));
    curveTestLoss->setSymbol(symbolTestLoss);

    picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
                                   QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
                                   plot->canvas());

    picker->setStateMachine(new QwtPickerDragPointMachine());
    picker->setRubberBandPen(QPen(QColor(Qt::black)));
    picker->setTrackerPen(QColor(Qt::black));

    curveTrainLoss->attach(plot);
    curveTrainLr->attach(plot);
    curveTestAccuracy->attach(plot);
    curveTestLoss->attach(plot);

    showCurve(curveTrainLoss, true);
    showCurve(curveTrainLr, true);
    showCurve(curveTestAccuracy, true);
    showCurve(curveTestLoss, true);

    mainLayout->addWidget(plot, 6, 0, 1, 2);
}
void TrainDialog::legendChecked(const QVariant &itemInfo, bool isOn)
{
    QwtPlotItem *plotItem = plot->infoToItem(itemInfo);
    if(plotItem)
    {
        plotItem->setVisible(isOn);
    }
    plot->replot();
}
void TrainDialog::showCurve(QwtPlotItem *item, bool IsOn)
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
