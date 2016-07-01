#ifndef SOLVERDIALOG_H
#define SOLVERDIALOG_H

#include <QtWidgets>
#include <QDialog>
#include "CaffeTools.h"
#include "Solver.h"
using namespace MMALab;

class SolverDialog : public QDialog
{
    Q_OBJECT

public:
    SolverDialog();
    ~SolverDialog();
    void closeEvent(QCloseEvent *event);

private:
    QLineEdit* lineEditFileName;

    QIntValidator* intValidator;
    QDoubleValidator* doubleValidator;

    QGridLayout* mainLayout;

    QGroupBox* groupBoxNet;
    QGroupBox* groupBoxTrainTestNet;

    QLineEdit* lineEditNet;
    QPushButton* pushButtonNetLocal;

    QLineEdit* lineEditTrainNet;
    QPushButton* pushButtonTrainNetLocal;

    QLineEdit* lineEditTestNet;
    QPushButton* pushButtonTestNetLocal;

    QLineEdit* lineEditTestIter;

    QLineEdit* lineEditTestInterval;

    QLineEdit* lineEditBaseLr;

    QLineEdit* lineEditMomentum;

    QLineEdit* lineEditWeightDecay;

    QComboBox* comboBoxLrPolicy;

    QWidget* widgetLrPolicyParam;

    QLineEdit* lineEditStepSize;

    QLineEdit* lineEditGamma;

    QLineEdit* lineEditPower;

    QLineEdit* lineEditStepValue;

    QLineEdit* lineEditDisplay;

    QLineEdit* lineEditMaxIter;

    QLineEdit* lineEditSnapshot;

    QLineEdit* lineEditSnapshotPrefix;
    QPushButton* pushButtonSnapshotPrefix;

    QComboBox* comboBoxType;
    QComboBox* comboBoxSolverMode;

    QPushButton* pushButtonImport;
    QPushButton* pushButtonSave;
    QPushButton* pushButtonExport;

    QString mFileName;
    MMALab::Solver*  mSolver;
    SolverParameter* mSolverParam;

    LrPolicy selectLrPolicy(string);
    SolverType selectType(string);
    SolverMode selectSolverMode(string);

    void writeInSolver();


private slots:
    void selectNet();
    void selectTrainTestNet();
    void getNetLocal();
    void changeLrPolicy(int);
    void getSaveLocal();
    void importSolver();
    void saveSolver();
    void exportSolver();
    void receiveMainWindowCloseSignal();
};

#endif // SOLVERDIALOG_H
