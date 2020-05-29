#include "archivationthread.h"

void ArchivationThread::run(){
    if(fileName.isNull() || !activeFile)
        throw std::runtime_error("ArchvationThread: fileName or activeFile is empty");
    try{
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
    catch(exception e){
        QMessageBox::critical(nullptr, "Error", e.what());
        return;
    }
}
