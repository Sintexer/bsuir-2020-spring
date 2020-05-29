#ifndef DEARCHIVATIONTHREAD_H
#define DEARCHIVATIONTHREAD_H

#include <QThread>
#include <QString>
#include <QMessageBox>

#include "filedecoder.h"

class DearchivationThread: public QThread
{
private:
    QString fileName;
    QString filePath;
public:
    DearchivationThread(){}
    DearchivationThread(QString fileName_, QString filePath_): fileName(fileName_), filePath(filePath_) {}

    void setFileName(QString fileName_){
        fileName=fileName_;
    }

    void setFilePath(QString filePath_){
        filePath = filePath_;
    }

    void run();
};

#endif // DEARCHIVATIONTHREAD_H
