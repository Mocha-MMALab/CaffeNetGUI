#ifndef PARSELOG_H
#define PARSELOG_H

#include <QThread>
#include <QFile>
#include <QTextStream>

#include <CaffeTools.h>

using namespace MMALab;
class ParseLog : public QThread
{
        Q_OBJECT
    public:
		//get log thread
        ParseLog(QString logFileLocal, QString logFileLocalTemp, CaffeTools &inputCaffeTools);
        void run();
    private:
        QString mLogFileLocal;
        QString mLogFileLocalTemp;
        CaffeTools *mCaffeTools;
        bool isRun;
        bool isClose;
    signals:
        void sendLogMessage(QString message);
        void sendEndSignal(bool signal);
    private slots :
        void closeSlot(bool isCloseSlot);
};

#endif // PARSELOG_H
