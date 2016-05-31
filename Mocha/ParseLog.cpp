#include "ParseLog.h"

ParseLog::ParseLog(QString logFileLocal, QString logFileLocalTemp, CaffeTools &inputCaffeTools)
{
    mLogFileLocal = logFileLocal;
    mLogFileLocalTemp = logFileLocalTemp;
    mCaffeTools = &inputCaffeTools;
}

void ParseLog::run()
{
    isClose = false;
    isRun = true;

    QString judge;
    QFile file(mLogFileLocalTemp);
    file.open(QIODevice::ReadOnly|QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream streamRead(&file);

    while(true)
    {
        if(isClose == false)
        {
            if (isRun == true)
            {

                judge = streamRead.readLine();

                if(judge!="")
                {
                    emit sendLogMessage(judge);
                }
            }
        }
        else
        {
            break;
        }
        if(mCaffeTools->getIsEnd())
        {
            emit sendEndSignal(true);
            break;
        }
        usleep(1);
    }
    file.copy(mLogFileLocal);
    file.close();
}

void ParseLog::closeSlot(bool isCloseSlot)
{
    isClose = isCloseSlot;
}
