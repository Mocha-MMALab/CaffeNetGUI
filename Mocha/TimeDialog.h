#ifndef TIMEDIALOG_H
#define TIMEDIALOG_H

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
class TimeDialog : public QDialog
{
    Q_OBJECT

    public:
        TimeDialog();

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
        int runCount;

        QGridLayout* mainLayout;
        QHBoxLayout* gpusLayout;
        QHBoxLayout* modelLayout;

        QLineEdit* lineEditCaffeLocal;
        QPushButton* pushButtonCaffeLocal;

        QLineEdit* lineEditModelLocal;
        QPushButton* pushButtonModelLocalOpen;

        vector<QCheckBox*> checkBoxGpus;

        QLineEdit* lineEditSaveLogLocal;
        QPushButton* pushButtonSaveLogLocal;

        QPushButton* pushButtonRun;
        QPushButton* pushButtonSaveProfile;

        QPlainTextEdit* plainTextEditShowLog;

        ParseLog* mShowLogMessageThread;

		//use Qwt draw picture
        QwtPlotCurve *curve;
        QPolygonF points;
        QwtPlot *plot;
        QwtPlotGrid *grid;
        QwtSymbol *symbol;
        QwtPlotPicker *picker;

        void createQwt();
        void showCurve(QwtPlotItem *item, bool IsOn);
    signals:
        void closeSignal(bool isCloseSignal);
    private slots:
        void getCaffeLocal();
        void getModelLocalOpen();
        void getSaveLogLocal();
        void run();
        void saveProfile();
        void receiveLogMessage(QString message);
        void receiveEndSignal(bool signal);
        void receiveMainWindowCloseSignal();
        void legendChecked(const QVariant &itemInfo, bool isOn);
};

#endif // TIMEDIALOG_H
