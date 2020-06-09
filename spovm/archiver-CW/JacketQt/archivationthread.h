#ifndef ARCHIVATIONTHREAD_H
#define ARCHIVATIONTHREAD_H

#include <QThread>
#include <QFileInfo>

#include "filetranslator.h"
#include "filecollector.h"
#include "fileentry.h"

class ArchivationThread : public QThread
{ 
    Q_OBJECT
private:
    QString fileName;
    QFileInfo *activeFile{nullptr};
    QList<FileEntry> fcList;
signals:
    void exception_executed(QString e);
public:
    ArchivationThread() = default;

    void setFileName(QString fileName_){
        fileName=fileName_;
    }

    void setActiveFile(QFileInfo* activeFile_){
        activeFile = activeFile_;
    }

    void clear(){
        fcList.clear();
        fileName.clear();
        activeFile = nullptr;
    }

    QString getFileName(){
        return fileName;
    }

    QList<FileEntry> getFcList(){
        return fcList;
    }

    QString getArchiveName(){
        return fileName;
    }

    void run();
};

#endif // ARCHIVATIONTHREAD_H
