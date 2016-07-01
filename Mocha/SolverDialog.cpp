#include "SolverDialog.h"
#include <float.h>
#include <iostream>
using namespace std;
SolverDialog::SolverDialog()
{
    intValidator = new QIntValidator(-INT_MAX, INT_MAX, this);
    doubleValidator = new QDoubleValidator(-FLT_MAX, FLT_MAX, 5, this);

    mFileName = "";
    mainLayout = new QGridLayout;

    QHBoxLayout* hboxFileName = new QHBoxLayout;
    hboxFileName->addWidget(new QLabel(tr("File :")));
    lineEditFileName = new QLineEdit();
    lineEditFileName->setReadOnly(true);
    hboxFileName->addWidget(lineEditFileName);
    QWidget* widgetFileName = new QWidget;
    widgetFileName->setLayout(hboxFileName);

    groupBoxNet = new QGroupBox(tr("Net"));
    QGridLayout* netLayout = new QGridLayout;
    netLayout->addWidget(new QLabel(tr("Net :")), 0, 0);
    lineEditNet = new QLineEdit();
    netLayout->addWidget(lineEditNet,0,1);
    pushButtonNetLocal = new QPushButton(tr("Open"), this);
    connect(pushButtonNetLocal, SIGNAL(clicked()), this, SLOT(getNetLocal()));
    netLayout->addWidget(pushButtonNetLocal,0,2);
    groupBoxNet->setLayout(netLayout);
    groupBoxNet->setCheckable(true);
    connect(groupBoxNet, SIGNAL(clicked()), this, SLOT(selectNet()));

    groupBoxTrainTestNet = new QGroupBox(tr("Train, Test"));
    QGridLayout* trainTestNetLayout = new QGridLayout;
    trainTestNetLayout->addWidget(new QLabel(tr("Train Net :")), 0, 0);
    trainTestNetLayout->addWidget(new QLabel(tr("Test Net :")), 1, 0);
    lineEditTrainNet = new QLineEdit();
    lineEditTestNet = new QLineEdit();
    trainTestNetLayout->addWidget(lineEditTrainNet,0,1);
    trainTestNetLayout->addWidget(lineEditTestNet,1,1);
    pushButtonTrainNetLocal = new QPushButton(tr("Open"), this);
    pushButtonTestNetLocal = new QPushButton(tr("Open"), this);
    connect(pushButtonTrainNetLocal, SIGNAL(clicked()), this, SLOT(getNetLocal()));
    connect(pushButtonTestNetLocal, SIGNAL(clicked()), this, SLOT(getNetLocal()));
    trainTestNetLayout->addWidget(pushButtonTrainNetLocal,0,2);
    trainTestNetLayout->addWidget(pushButtonTestNetLocal,1,2);
    groupBoxTrainTestNet->setLayout(trainTestNetLayout);
    groupBoxTrainTestNet->setCheckable(true);
    groupBoxTrainTestNet->setChecked(false);
    connect(groupBoxTrainTestNet, SIGNAL(clicked()), this, SLOT(selectTrainTestNet()));

    QHBoxLayout* hboxTestIter = new QHBoxLayout;
    hboxTestIter->addWidget(new QLabel(tr("Test_Iter :")));
    lineEditTestIter = new QLineEdit();
    lineEditTestIter->setValidator(intValidator);
    hboxTestIter->addWidget(lineEditTestIter);
    QWidget* widgetTestIter = new QWidget;
    widgetTestIter->setLayout(hboxTestIter);

    QHBoxLayout* hboxTestInterval = new QHBoxLayout;
    hboxTestInterval->addWidget(new QLabel(tr("Test_Interval :")));
    lineEditTestInterval = new QLineEdit();
    lineEditTestInterval->setValidator(intValidator);
    hboxTestInterval->addWidget(lineEditTestInterval);
    QWidget* widgetTestInterval = new QWidget;
    widgetTestInterval->setLayout(hboxTestInterval);

    QHBoxLayout* hboxBaseLr = new QHBoxLayout;
    hboxBaseLr->addWidget(new QLabel(tr("Base_Lr :")));
    lineEditBaseLr = new QLineEdit();
    lineEditBaseLr->setValidator(doubleValidator);
    hboxBaseLr->addWidget(lineEditBaseLr);
    QWidget* widgetBaseLr = new QWidget;
    widgetBaseLr->setLayout(hboxBaseLr);

    QHBoxLayout* hboxMomentum = new QHBoxLayout;
    hboxMomentum->addWidget(new QLabel(tr("Momentum :")));
    lineEditMomentum = new QLineEdit();
    lineEditMomentum->setValidator(doubleValidator);
    hboxMomentum->addWidget(lineEditMomentum);
    QWidget* widgetMomentum = new QWidget;
    widgetMomentum->setLayout(hboxMomentum);

    QHBoxLayout* hboxWeightDecay = new QHBoxLayout;
    hboxWeightDecay->addWidget(new QLabel(tr("Weight_Decay :")));
    lineEditWeightDecay = new QLineEdit();
    lineEditWeightDecay->setValidator(doubleValidator);
    hboxWeightDecay->addWidget(lineEditWeightDecay);
    QWidget* widgetWeightDecay = new QWidget;
    widgetWeightDecay->setLayout(hboxWeightDecay);

    QHBoxLayout* hboxLrPolicy = new QHBoxLayout;
    hboxLrPolicy->addWidget(new QLabel(tr("Lr_Policy :")));
    comboBoxLrPolicy = new QComboBox;
    comboBoxLrPolicy->addItem("fixed");
    comboBoxLrPolicy->addItem("step");
    comboBoxLrPolicy->addItem("exp");
    comboBoxLrPolicy->addItem("inv");
    comboBoxLrPolicy->addItem("multistep");
    comboBoxLrPolicy->addItem("poly");
    comboBoxLrPolicy->addItem("sigmoid");
    connect(comboBoxLrPolicy, SIGNAL(currentIndexChanged(int)), this, SLOT(changeLrPolicy(int)));
    hboxLrPolicy->addWidget(comboBoxLrPolicy);
    hboxLrPolicy->addSpacing(120);
    QWidget* widgetLrPolicy = new QWidget;
    widgetLrPolicy->setLayout(hboxLrPolicy);

    widgetLrPolicyParam = new QWidget;

    QHBoxLayout* hboxDisplay = new QHBoxLayout;
    hboxDisplay->addWidget(new QLabel(tr("Display :")));
    lineEditDisplay = new QLineEdit();
    lineEditDisplay->setValidator(intValidator);
    hboxDisplay->addWidget(lineEditDisplay);
    QWidget* widgetDisplay = new QWidget;
    widgetDisplay->setLayout(hboxDisplay);

    QHBoxLayout* hboxMaxIter = new QHBoxLayout;
    hboxMaxIter->addWidget(new QLabel(tr("Max_Iter :")));
    lineEditMaxIter = new QLineEdit();
    lineEditMaxIter->setValidator(intValidator);
    hboxMaxIter->addWidget(lineEditMaxIter);
    QWidget* widgetMaxIter = new QWidget;
    widgetMaxIter->setLayout(hboxMaxIter);

    QHBoxLayout* hboxSnapshot = new QHBoxLayout;
    hboxSnapshot->addWidget(new QLabel(tr("Snapshot :")));
    lineEditSnapshot = new QLineEdit();
    lineEditSnapshot->setValidator(intValidator);
    hboxSnapshot->addWidget(lineEditSnapshot);
    QWidget* widgetSnapshot = new QWidget;
    widgetSnapshot->setLayout(hboxSnapshot);

    QHBoxLayout* hboxSnapshotPrefix = new QHBoxLayout;
    hboxSnapshotPrefix->addWidget(new QLabel(tr("Snapshot_Prefix :")));
    lineEditSnapshotPrefix = new QLineEdit();
    hboxSnapshotPrefix->addWidget(lineEditSnapshotPrefix);
    pushButtonSnapshotPrefix = new QPushButton(tr("Open"), this);
    connect(pushButtonSnapshotPrefix, SIGNAL(clicked()), this, SLOT(getSaveLocal()));
    hboxSnapshotPrefix->addWidget(pushButtonSnapshotPrefix);
    QWidget* widgetSnapshotPrefix = new QWidget;
    widgetSnapshotPrefix->setLayout(hboxSnapshotPrefix);

    QHBoxLayout* hboxTypeSolverMode = new QHBoxLayout;
    hboxTypeSolverMode->addWidget(new QLabel(tr("Type :")));
    comboBoxType = new QComboBox();
    comboBoxType->addItem("SGD");
    comboBoxType->addItem("Nesterov");
    comboBoxType->addItem("AdaGrad");
    comboBoxType->addItem("RMSProp");
    comboBoxType->addItem("AdaDelta");
    comboBoxType->addItem("Adam");
    hboxTypeSolverMode->addWidget(comboBoxType);
    hboxTypeSolverMode->addSpacing(20);
    hboxTypeSolverMode->addWidget(new QLabel(tr("SolverMode :")));
    comboBoxSolverMode = new QComboBox();
    comboBoxSolverMode->addItem("CPU");
    comboBoxSolverMode->addItem("GPU");
    hboxTypeSolverMode->addWidget(comboBoxSolverMode);
    hboxTypeSolverMode->addSpacing(20);
    QWidget* widgetTypeSolverMode = new QWidget;
    widgetTypeSolverMode->setLayout(hboxTypeSolverMode);

    QHBoxLayout* hboxFunction = new QHBoxLayout;
    pushButtonImport = new QPushButton(tr("Load"), this);
    pushButtonSave = new QPushButton(tr("Save"), this);
    pushButtonExport = new QPushButton(tr("Save as"), this);
    connect(pushButtonImport, SIGNAL(clicked()), this, SLOT(importSolver()));
    connect(pushButtonSave, SIGNAL(clicked()), this, SLOT(saveSolver()));
    connect(pushButtonExport, SIGNAL(clicked()), this, SLOT(exportSolver()));
    hboxFunction->addWidget(pushButtonImport);
    hboxFunction->addWidget(pushButtonSave);
    hboxFunction->addWidget(pushButtonExport);
    QWidget* widgetFunction = new QWidget;
    widgetFunction->setLayout(hboxFunction);


    mainLayout->addWidget(widgetFileName, 0, 0);
    mainLayout->addWidget(groupBoxNet, 1, 0);
    mainLayout->addWidget(groupBoxTrainTestNet, 2, 0);
    mainLayout->addWidget(widgetTestIter, 3, 0);
    mainLayout->addWidget(widgetTestInterval, 4, 0);
    mainLayout->addWidget(widgetBaseLr, 5, 0);
    mainLayout->addWidget(widgetMomentum, 6, 0);
    mainLayout->addWidget(widgetWeightDecay, 7, 0);
    mainLayout->addWidget(widgetLrPolicy, 1, 1);
    mainLayout->addWidget(widgetLrPolicyParam, 2, 1);
    mainLayout->addWidget(widgetDisplay, 3, 1);
    mainLayout->addWidget(widgetMaxIter, 4, 1);
    mainLayout->addWidget(widgetSnapshot, 5, 1);
    mainLayout->addWidget(widgetSnapshotPrefix, 6, 1);
    mainLayout->addWidget(widgetTypeSolverMode, 0, 1);
    mainLayout->addWidget(widgetFunction, 8, 1);

    setWindowFlags(Qt::Window);
    setWindowTitle(tr("SolverDialog"));
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);


}

SolverDialog::~SolverDialog()
{

}

void SolverDialog::selectNet()
{
    if(groupBoxNet->isChecked())
    {
        groupBoxTrainTestNet->setChecked(false);
        lineEditTrainNet->setText("");
        lineEditTestNet->setText("");

    }
}

void SolverDialog::selectTrainTestNet()
{
    if(groupBoxTrainTestNet->isChecked())
    {
        groupBoxNet->setChecked(false);
        lineEditNet->setText("");
    }
}

void SolverDialog::getNetLocal()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("select prototxt file"),
                                                    ".",
                                                    tr("caffe prototxt file(*.prototxt)"));
    if (!fileUrl.isEmpty())
    {
        lineEditNet->setText(fileUrl);
    }
}

void SolverDialog::changeLrPolicy(int policy)
{
    delete widgetLrPolicyParam;
    widgetLrPolicyParam = new QWidget;
    mainLayout->removeWidget(widgetLrPolicyParam);
    switch(policy)
    {
        case 0:
        {
            QGridLayout* fixedLayout = new QGridLayout;
            widgetLrPolicyParam->setLayout(fixedLayout);
            break;
        }
        case 1:
        {
            QGridLayout* stepLayout = new QGridLayout;
            stepLayout->addWidget(new QLabel(tr("    StepSize :")), 0, 0);
            stepLayout->addWidget(new QLabel(tr("    Gamma :")), 1, 0);
            lineEditStepSize = new QLineEdit();
            lineEditGamma = new QLineEdit();
            lineEditStepSize->setValidator(intValidator);
            lineEditGamma->setValidator(doubleValidator);
            stepLayout->addWidget(lineEditStepSize, 0, 1);
            stepLayout->addWidget(lineEditGamma, 1, 1);
            widgetLrPolicyParam->setLayout(stepLayout);
            break;
        }
        case 2:
        {
            QGridLayout* expLayout = new QGridLayout;
            expLayout->addWidget(new QLabel(tr("    Gamma :")), 0, 0);
            lineEditGamma = new QLineEdit();
            lineEditGamma->setValidator(doubleValidator);
            expLayout->addWidget(lineEditGamma, 0, 1);
            widgetLrPolicyParam->setLayout(expLayout);
            break;
        }
        case 3:
        {
            QGridLayout* invLayout = new QGridLayout;
            invLayout->addWidget(new QLabel(tr("    Gamma :")), 0, 0);
            invLayout->addWidget(new QLabel(tr("    Power :")), 1, 0);
            lineEditGamma = new QLineEdit();
            lineEditPower = new QLineEdit();
            lineEditGamma->setValidator(doubleValidator);
            lineEditPower->setValidator(doubleValidator);
            invLayout->addWidget(lineEditGamma, 0, 1);
            invLayout->addWidget(lineEditPower, 1, 1);
            widgetLrPolicyParam->setLayout(invLayout);
            break;
        }
        case 4:
        {
            QGridLayout* multistepLayout = new QGridLayout;
            multistepLayout->addWidget(new QLabel(tr("    StepValue :")), 0, 0);
            multistepLayout->addWidget(new QLabel(tr("    Gamma :")), 1, 0);
            lineEditStepValue = new QLineEdit();
            lineEditGamma = new QLineEdit();
            lineEditGamma->setValidator(doubleValidator);
            multistepLayout->addWidget(lineEditStepValue, 0, 1);
            multistepLayout->addWidget(lineEditGamma, 1, 1);
            widgetLrPolicyParam->setLayout(multistepLayout);
            break;
        }
        case 5:
        {
            QGridLayout* polyLayout = new QGridLayout;
            polyLayout->addWidget(new QLabel(tr("    Power :")), 0, 0);
            lineEditPower = new QLineEdit();
            lineEditPower->setValidator(doubleValidator);
            polyLayout->addWidget(lineEditPower, 0, 1);
            widgetLrPolicyParam->setLayout(polyLayout);
            break;
        }
        case 6:
        {
            QGridLayout* sigmoidLayout = new QGridLayout;
            sigmoidLayout->addWidget(new QLabel(tr("    StepSize :")), 0, 0);
            sigmoidLayout->addWidget(new QLabel(tr("    Gamma :")), 1, 0);
            lineEditStepSize = new QLineEdit();
            lineEditGamma = new QLineEdit();
            lineEditStepSize->setValidator(intValidator);
            lineEditGamma->setValidator(doubleValidator);
            sigmoidLayout->addWidget(lineEditStepSize, 0, 1);
            sigmoidLayout->addWidget(lineEditGamma, 1, 1);
            widgetLrPolicyParam->setLayout(sigmoidLayout);
            break;
        }
    }
    mainLayout->addWidget(widgetLrPolicyParam, 2, 1);
}

void SolverDialog::getSaveLocal()
{
    QString fileUrl = QFileDialog::getExistingDirectory(this, tr("select filelocal to save"),
                                                    ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!fileUrl.isEmpty())
    {
        lineEditSnapshotPrefix->setText(fileUrl);
    }
}

void SolverDialog::importSolver()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("import prototxt file"),
                                                    ".",
                                                    tr("caffe prototxt file(*.prototxt)"));
    if (!fileUrl.isEmpty())
    {
        mFileName = fileUrl;
        lineEditFileName->setText(mFileName);

        CaffeTools* ct = new CaffeTools();
        ct->parseSolverProTextFile(fileUrl.toStdString());
        mSolverParam = new SolverParameter();
        *mSolverParam = ct->getSolverParam();

        lineEditNet->setText(QString::fromStdString(mSolverParam->net()));
        lineEditTrainNet->setText(QString::fromStdString(mSolverParam->train_net()));
        for(int i = 0; i < mSolverParam->test_net_size(); i++)
        {
            lineEditTestNet->setText(QString::fromStdString(mSolverParam->test_net(0)));
        }
        if(mSolverParam->net() == "")
        {
            groupBoxTrainTestNet->setChecked(true);
            selectTrainTestNet();
        }
        else
        {
            groupBoxNet->setChecked(true);
            selectNet();
        }
        for(int i = 0; i < mSolverParam->test_iter_size(); i++)
        {
            lineEditTestIter->setText(QString::number(mSolverParam->test_iter(0)));
        }
        lineEditTestInterval->setText(QString::number(mSolverParam->test_interval()));
        lineEditBaseLr->setText(QString::number(mSolverParam->base_lr()));
        lineEditMomentum->setText(QString::number(mSolverParam->momentum()));
        lineEditWeightDecay->setText(QString::number(mSolverParam->weight_decay()));
        comboBoxLrPolicy->setCurrentIndex(comboBoxLrPolicy->findText(QString::fromStdString(mSolverParam->lr_policy())));
        switch((LrPolicy)comboBoxLrPolicy->currentIndex())
        {
            case LrPolicy::LRPOLICY_FIXED:
            {
                break;
            }
            case LrPolicy::LRPOLICY_STEP:
            {
                lineEditStepSize->setText(QString::number(mSolverParam->stepsize()));
                lineEditGamma->setText(QString::number(mSolverParam->gamma()));
                break;
            }
            case LrPolicy::LRPOLICY_EXP:
            {
                lineEditGamma->setText(QString::number(mSolverParam->gamma()));
                break;
            }
            case LrPolicy::LRPOLICY_INV:
            {
                lineEditGamma->setText(QString::number(mSolverParam->gamma()));
                lineEditPower->setText(QString::number(mSolverParam->power()));
                break;
            }
            case LrPolicy::LRPOLICY_MULTISTEP:
            {
                QString str = "";
                for(int i = 0; i < mSolverParam->stepvalue_size(); i ++)
                {
                    str += QString::number(mSolverParam->stepvalue(i));
                    if(i != (mSolverParam->stepvalue_size() - 1))
                    {
                        str += ",";
                    }
                }
                lineEditStepValue->setText(str);
                lineEditGamma->setText(QString::number(mSolverParam->gamma()));
                break;
            }
            case LrPolicy::LRPOLICY_POLY:
            {
                lineEditPower->setText(QString::number(mSolverParam->power()));
                break;
            }
            case LrPolicy::LRPOLICY_SIGMOID:
            {
                lineEditStepSize->setText(QString::number(mSolverParam->stepsize()));
                lineEditGamma->setText(QString::number(mSolverParam->gamma()));
                break;
            }
        }
        lineEditDisplay->setText(QString::number(mSolverParam->display()));
        lineEditMaxIter->setText(QString::number(mSolverParam->max_iter()));
        lineEditSnapshot->setText(QString::number(mSolverParam->snapshot()));
        lineEditSnapshotPrefix->setText(QString::fromStdString(mSolverParam->snapshot_prefix()));
        comboBoxType->setCurrentIndex(comboBoxType->findText(QString::fromStdString(mSolverParam->type())));
        comboBoxSolverMode->setCurrentIndex(mSolverParam->solver_mode());

        writeInSolver();

    }
}
void SolverDialog::saveSolver()
{
    if(mFileName != "")
    {
        writeInSolver();
        string exportName = mFileName.toStdString();
        ofstream file(exportName, ios::out);
        file << mSolver->convet2CaffeFormat() << endl << endl;
        file.close();
    }
    else
    {
        QMessageBox::information(this,"Save file","No file can be saved.");
    }
}
void SolverDialog::exportSolver()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("export prototxt file"),
                                                    "./solver",
                                                    tr("caffe prototxt file(*.prototxt)"));
    if (!fileName.isEmpty())
    {
        writeInSolver();
        string exportName = fileName.toStdString();
        string extension  = ".prototxt";
        exportName += extension;
        ofstream file(exportName, ios::out);
        file << mSolver->convet2CaffeFormat() << endl << endl;
        file.close();
    }
}

void SolverDialog::writeInSolver()
{
    mSolver = new MMALab::Solver();

    mSolver->setNet(lineEditNet->text().toStdString());
    mSolver->setTainNet(lineEditTrainNet->text().toStdString());
    mSolver->setTestNet(lineEditTestNet->text().toStdString());
    mSolver->setTestIter(lineEditTestIter->text().toInt());
    mSolver->setTestInterval(lineEditTestInterval->text().toInt());
    mSolver->setBaseLr(lineEditBaseLr->text().toFloat());
    mSolver->setMomentum(lineEditMomentum->text().toFloat());
    mSolver->setWeightDecay(lineEditWeightDecay->text().toFloat());
    mSolver->setLrPolicy((LrPolicy)comboBoxLrPolicy->currentIndex());
    switch(mSolver->getLrPolicy())
    {
        case LrPolicy::LRPOLICY_FIXED:
        {
            break;
        }
        case LrPolicy::LRPOLICY_STEP:
        {
            mSolver->setStepSize(lineEditStepSize->text().toInt());
            mSolver->setGamma(lineEditGamma->text().toFloat());
            break;
        }
        case LrPolicy::LRPOLICY_EXP:
        {
            mSolver->setGamma(lineEditGamma->text().toFloat());
            break;
        }
        case LrPolicy::LRPOLICY_INV:
        {
            mSolver->setGamma(lineEditGamma->text().toFloat());
            mSolver->setPower(lineEditPower->text().toFloat());
            break;
        }
        case LrPolicy::LRPOLICY_MULTISTEP:
        {
            mSolver->clearStepValue();
            string stepvalueStr = lineEditStepValue->text().toStdString();
            char *token = strtok(const_cast<char  *>(stepvalueStr.c_str()), ",");
            vector<int> v;
            while(token != NULL)
            {
                v.push_back(stoi(token));
                token = strtok(NULL, ",");
            }
            for(unsigned int i = 0; i < v.size(); i++)
            {
                mSolver->setStepValue(v[i]);
            }
            mSolver->setGamma(lineEditGamma->text().toFloat());
            break;
        }
        case LrPolicy::LRPOLICY_POLY:
        {
            mSolver->setPower(lineEditPower->text().toFloat());
            break;
        }
        case LrPolicy::LRPOLICY_SIGMOID:
        {
            mSolver->setStepSize(lineEditStepSize->text().toInt());
            mSolver->setGamma(lineEditGamma->text().toFloat());
            break;
        }
    }
    mSolver->setDisplay(lineEditDisplay->text().toInt());
    mSolver->setMaxIter(lineEditMaxIter->text().toInt());
    mSolver->setSnapshot(lineEditSnapshot->text().toInt());
    mSolver->setSnapshotPrefix(lineEditSnapshotPrefix->text().toStdString());
    mSolver->setType((SolverType)comboBoxType->currentIndex());
    mSolver->setSolverMode((SolverMode)comboBoxSolverMode->currentIndex());
}


LrPolicy SolverDialog::selectLrPolicy(string policy)
{
    if(policy == "fixed")
    {
        return LrPolicy::LRPOLICY_FIXED;
    }
    else if(policy == "step")
    {
        return LrPolicy::LRPOLICY_STEP;
    }
    else if(policy == "exp")
    {
        return LrPolicy::LRPOLICY_EXP;
    }
    else if(policy == "inv")
    {
        return LrPolicy::LRPOLICY_INV;
    }
    else if(policy == "multistep")
    {
        return LrPolicy::LRPOLICY_MULTISTEP;
    }
    else if(policy == "poly")
    {
        return LrPolicy::LRPOLICY_POLY;
    }
    else if(policy == "sigmoid")
    {
        return LrPolicy::LRPOLICY_SIGMOID;
    }
    else
    {
        return LrPolicy::LRPOLICY_FIXED;
    }
}

SolverType SolverDialog::selectType(string type)
{
    if(type == "SGD")
    {
        return SolverType::SGD;
    }
    else if(type == "Nesterov")
    {
        return SolverType::NESTEROV;
    }
    else if(type == "AdaGrad")
    {
        return SolverType::ADAGRAD;
    }
    else if(type == "RMSProp")
    {
        return SolverType::RMSPROP;
    }
    else if(type == "AdaDelta")
    {
        return SolverType::ADADELTA;
    }
    else if(type == "Adam")
    {
        return SolverType::ADAM;
    }
    else
    {
        return SolverType::SGD;
    }
}

SolverMode SolverDialog::selectSolverMode(string mode)
{
    if(mode == "CPU")
    {
        return SolverMode::CPU;
    }
    else if(mode == "GPU")
    {
        return SolverMode::GPU;
    }
    else
    {
        return SolverMode::CPU;
    }
}

void SolverDialog::receiveMainWindowCloseSignal()
{
    close();
}

void SolverDialog::closeEvent(QCloseEvent* event)
{

}
