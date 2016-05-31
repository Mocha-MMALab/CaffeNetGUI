#include "TimeDialog.h"

TimeDialog::TimeDialog()
{
    profile = new QSettings("MMALab","timeProfile");

    regex = new QRegExp("Iteration:\\s(\\d*)\\s\\w*\\-\\w*\\stime:\\s(\\d*\\.*\\d*)\\s\\w*");

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

    mainLayout->addWidget(new QLabel(tr("GpuSelect:")), 2, 0);
    cudaGetDeviceCount(&gpusCount);
    for(int i = 0 ; i < gpusCount ; i++)
    {
        cudaGetDeviceProperties(&prop, i);
        checkBoxGpus.push_back(new QCheckBox(prop.name));
        gpusLayout->addWidget(checkBoxGpus.at(i));
    }
    mainLayout->addLayout(gpusLayout, 2, 1);

    mainLayout->addWidget(new QLabel(tr("SaveLogLocal:")), 3, 0);
    lineEditSaveLogLocal = new QLineEdit((profile->value("SaveLogLocal").toString()));
    mainLayout->addWidget(lineEditSaveLogLocal, 3, 1);
    pushButtonSaveLogLocal = new QPushButton(tr("Open"));
    connect(pushButtonSaveLogLocal, SIGNAL(clicked()), this, SLOT(getSaveLogLocal()));
    mainLayout->addWidget(pushButtonSaveLogLocal, 3, 2);

    pushButtonRun = new QPushButton(tr("Run"));
    connect(pushButtonRun, SIGNAL(clicked()), this, SLOT(run()));
    mainLayout->addWidget(pushButtonRun, 4, 0);
    pushButtonSaveProfile = new QPushButton(tr("Save Profile"));
    connect(pushButtonSaveProfile, SIGNAL(clicked()), this, SLOT(saveProfile()));
    mainLayout->addWidget(pushButtonSaveProfile, 4, 2);

    createQwt();

    plainTextEditShowLog = new QPlainTextEdit;
    mainLayout->addWidget(plainTextEditShowLog, 5, 2);

    setWindowFlags(Qt::Widget);
    setWindowTitle(tr("TimeDialog"));
    setLayout(mainLayout);
    resize((QApplication::desktop()->width()*0.9), (QApplication::desktop()->height()*0.5));
}

void TimeDialog::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton dialogReturn;

    if(pushButtonRun->isEnabled() == false)
    {
        dialogReturn = QMessageBox::warning(NULL,
                                            tr("Close window"), tr("Timing is not yet complete, do you want to close?"),
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
void TimeDialog::receiveMainWindowCloseSignal()
{
    close();
}

void TimeDialog::getCaffeLocal()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("select to caffe executable file"),
                                                    "../CaffeToolsLib/caffe/build/tools/",
                                                    tr("executable file(*)"));
    if (!fileUrl.isEmpty())
    {
        lineEditCaffeLocal->setText(fileUrl);
    }
}

void TimeDialog::getModelLocalOpen()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("select to caffe model prototxt file"),
                                                    "../CaffeToolsLib/testModel/",
                                                    tr("caffe prototxt file(*.prototxt)"));
    if (!fileUrl.isEmpty())
    {
        lineEditModelLocal->setText(fileUrl);
    }
}

void TimeDialog::getSaveLogLocal()
{
    QString fileUrl = QFileDialog::getExistingDirectory(this, tr("select to log file save local"),
                                                    "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!fileUrl.isEmpty())
    {
        lineEditSaveLogLocal->setText(fileUrl);
    }
}

void TimeDialog::run()
{
    QDir dir;
    dir.setPath(dir.absolutePath() + "/Temp");

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeInfo = currentDateTime.toString("yyyyMMddhhmmss");
    logFileLocalTemp = dir.absolutePath() + "/" + currentDateTimeInfo + ".log";

    QCheckBox* tempCheckBox;
    QString gpusSelect = "";

    runCount = 0;

    plainTextEditShowLog->clear();
    points.clear();
    curve->setSamples(points);
    plot->replot();

    pushButtonRun->setEnabled(false);
    lineEditSaveLogLocal->setEnabled(false);
    pushButtonSaveLogLocal->setEnabled(false);

    mShowLogMessageThread = new ParseLog(lineEditSaveLogLocal->text() + "/CaffeTime.log",
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

    ct->time(lineEditCaffeLocal->text().toStdString(), lineEditModelLocal->text().toStdString(),
             gpusSelect.toStdString(), logFileLocalTemp.toStdString());
}

void TimeDialog::saveProfile()
{
    profile->setValue("CaffeLocal", QVariant(lineEditCaffeLocal->text()));
    profile->setValue("ModelLocal", QVariant(lineEditModelLocal->text()));
    profile->setValue("SaveLogLocal", QVariant(lineEditSaveLogLocal->text()));

    QMessageBox::about(NULL, "Remind", "Save profile done.");
}

void TimeDialog::receiveLogMessage(QString message)
{
    plainTextEditShowLog->insertPlainText(message+'\n');
    plainTextEditShowLog->moveCursor(QTextCursor::End);

    position = message.indexOf(*regex);
    if(position!=-1)
    {
        runCount++;
        if(runCount % 10 == 0 || runCount == 1)
        {
            points << QPointF(regex->cap(1).toDouble(), regex->cap(2).toDouble());
            curve->setSamples(points);
            plot->replot();
        }
    }
}
void TimeDialog::receiveEndSignal(bool signal)
{
    pushButtonRun->setEnabled(signal);
    lineEditSaveLogLocal->setEnabled(signal);
    pushButtonSaveLogLocal->setEnabled(signal);
}

void TimeDialog::createQwt()
{
    QwtLegend *legend = new QwtLegend;
    legend->setDefaultItemMode(QwtLegendData::Checkable);

    plot = new QwtPlot();
    plot->setTitle("Time Plot");
    plot->setCanvasBackground(Qt::white);
    plot->insertLegend(legend, QwtPlot::RightLegend);
    connect(legend, SIGNAL(checked(const QVariant &, bool, int)),
            this, SLOT(legendChecked(const QVariant &, bool)));

    grid = new QwtPlotGrid();
    grid->attach(plot);

    curve = new QwtPlotCurve();
    curve->setTitle("Forward-Backward Time Points(ms)");
    curve->setPen(Qt::blue, 4),
    curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    symbol = new QwtSymbol(QwtSymbol::Ellipse,
        QBrush(Qt::red), QPen(Qt::red, 2), QSize(5, 5));
    curve->setSymbol(symbol);

    picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
                                   QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
                                   plot->canvas());

    picker->setStateMachine(new QwtPickerDragPointMachine());
    picker->setRubberBandPen(QPen(QColor(Qt::black)));
    picker->setTrackerPen(QColor(Qt::black));

    curve->attach(plot);

    showCurve(curve, true);

    mainLayout->addWidget(plot, 5, 0, 1, 2);
}
void TimeDialog::legendChecked(const QVariant &itemInfo, bool isOn)
{
    QwtPlotItem *plotItem = plot->infoToItem(itemInfo);
    if(plotItem)
    {
        plotItem->setVisible(isOn);
    }
    plot->replot();
}
void TimeDialog::showCurve(QwtPlotItem *item, bool IsOn)
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
