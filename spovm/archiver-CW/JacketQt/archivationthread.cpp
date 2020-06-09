#include "archivationthread.h"

void ArchivationThread::run(){
    if(fileName.isNull() || !activeFile)
        emit exception_executed("ArchvationThread: fileName or activeFile is empty");
    try{
        FileTranslator ft;
        ft.openFile(fileName);
        QList<FileEntry> fcList;
        if(activeFile->isDir()){
            FileCollector fc(activeFile->absoluteFilePath());
            fcList = fc.collectFiles();
        }
        else{
            FileEntry temp(activeFile->absoluteFilePath(), "", activeFile->fileName());
            fcList.push_front(temp);
            FileEntry temp2("<", "", "");
            fcList.push_front(temp2);
        }
        if(QThread::currentThread()->isInterruptionRequested()){
            clear();
            return;
        }
        ft.setAllFiles(fcList);
        ft.translateFiles();
    }
    catch(runtime_error e){
        emit exception_executed(e.what());
    }
}
