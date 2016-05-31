#ifndef TRAINDIALOG_H
#define TRAINDIALOG_H

#include "cuda_runtime.h"
#include "CaffeTools.h"
#include "ParseLog.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_legend_label.h>

#include <QtWidgets>
#include <QDialog>
#include <QSettings>

using namespace MMALab;
class TrainDialog : public QDialog
{
    Q_OBJECT

    public:
        TrainDialog();

        void closeEvent(QCloseEvent *event);
    private:
        char tempChar[2048];
        CaffeTools* ct = new CaffeTools();
        QString logFileLocalTemp;
		//write profile
        QSettings* profile;

		//get receive log
        QRegExp* regexTrain;
        QRegExp* regexTest;
        QRegExp* regexFlag;
        int currentNumber;
        int position;
        int lossRunCount;
        int lrRunCount;

        QGridLayout* mainLayout;
        QHBoxLayout* gpusLayout;
        QHBoxLayout* solverLayout;

        QLineEdit* lineEditCaffeLocal;
        QPushButton* pushButtonCaffeLocal;

        QLineEdit* lineEditSolverLocal;
        QPushButton* pushButtonSolverLocalOpen;

        QLineEdit* lineEditSnapshotLocal;
        QPushButton* pushButtonSnapshotLocal;

        vector<QCheckBox*> checkBoxGpus;

        QLineEdit* lineEditSaveLogLocal;
        QPushButton* pushButtonSaveLogLocal;

        QPushButton* pushButtonRun;
        QPushButton* pushButtonSaveProfile;

        QPlainTextEdit* plainTextEditShowLog;

        ParseLog* mShowLogMessageThread;

		//use Qwt draw picture
        QwtPlotCurve *curveTrainLoss;
        QwtPlotCurve *curveTrainLr;
        QwtPlotCurve *curveTestAccuracy;
        QwtPlotCurve *curveTestLoss;
        QPolygonF pointsTestAccuracy;
        QPolygonF pointsTestLoss;
        QPolygonF pointsTrainLoss;
        QPolygonF pointsTrainLr;
        QwtPlot *plot;
        QwtPlotGrid *grid;
        QwtSymbol *symbolTestAccuracy;
        QwtSymbol *symbolTestLoss;
        QwtSymbol *symbolTrainLoss;
        QwtSymbol *symbolTrainLr;
        QwtPlotPicker *picker;

        void createQwt();
        void showCurve(QwtPlotItem *item, bool IsOn);
    signals:
        void closeSignal(bool isCloseSignal);
    private slots:
        void getCaffeLocal();
        void getSolverLocalOpen();
        void getSnapshotLocal();
        void getSaveLogLocal();
        void run();
        void saveProfile();
        void receiveLogMessage(QString message);
        void receiveEndSignal(bool signal);
        void receiveMainWindowCloseSignal();
        void legendChecked(const QVariant &itemInfo, bool isOn);
};

#endif // TRAINDIALOG_H
