#ifndef DEARCHIVATIONTHREAD_H
#define DEARCHIVATIONTHREAD_H

#include <QThread>
#include <QString>

#include "filedecoder.h"

class DearchivationThread: public QThread
{
    Q_OBJECT
private:
    QString fileName;
    QString filePath;
    QWidget *parent;
signals:
    void exception_executed(QString e);
public:
    DearchivationThread() = default;

    void setFileName(QString fileName_){
        fileName=fileName_;
    }

    void setFilePath(QString filePath_){
        filePath = filePath_;
    }

    void run();
};

#endif // DEARCHIVATIONTHREAD_H
