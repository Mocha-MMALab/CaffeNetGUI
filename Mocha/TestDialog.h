#ifndef TESTDIALOG_H
#define TESTDIALOG_H

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
class TestDialog : public QDialog
{
    Q_OBJECT

    public:
        TestDialog();

        void closeEvent(QCloseEvent *event);
    private:
        char tempChar[2048];
        CaffeTools* ct = new CaffeTools();
        QString logFileLocalTemp;

		//write profile		
        QSettings* profile;

		//get receive log
        QRegExp* regex;
        int position;
        int accuracyRunCount;
        int lossRunCount;

        QGridLayout* mainLayout;
        QHBoxLayout* gpusLayout;
        QHBoxLayout* modelLayout;

        QLineEdit* lineEditCaffeLocal;
        QPushButton* pushButtonCaffeLocal;

        QLineEdit* lineEditModelLocal;
        QPushButton* pushButtonModelLocalOpen;

        QLineEdit* lineEditWeightsLocal;
        QPushButton* pushButtonWeightsLocal;

        vector<QCheckBox*> checkBoxGpus;

        QLineEdit* lineEditSaveLogLocal;
        QPushButton* pushButtonSaveLogLocal;

        QPushButton* pushButtonRun;
        QPushButton* pushButtonSaveProfile;

        QPlainTextEdit* plainTextEditShowLog;

        ParseLog* mShowLogMessageThread;

		//use Qwt draw picture
        QwtPlotCurve *curveAccuracy;
        QwtPlotCurve *curveLoss;
        QPolygonF pointsAccuracy;
        QPolygonF pointsLoss;
        QwtPlot *plot;
        QwtPlotGrid *grid;
        QwtSymbol *symbolAccuracy;
        QwtSymbol *symbolLoss;
        QwtPlotPicker *picker;

        void createQwt();
        void showCurve(QwtPlotItem *item, bool IsOn);
    signals:
        void closeSignal(bool isCloseSignal);
    private slots:
        void getCaffeLocal();
        void getModelLocalOpen();
        void getSaveLogLocal();
        void getWeightsLocal();
        void run();
        void saveProfile();
        void receiveLogMessage(QString message);
        void receiveEndSignal(bool signal);
        void receiveMainWindowCloseSignal();
        void legendChecked(const QVariant &itemInfo, bool isOn);
};

#endif // TESTDIALOG_H
