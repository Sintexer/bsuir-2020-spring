#include "dearchivationthread.h"

void DearchivationThread::run(){
    try{
        FileDecoder fd;
        fd.dearchive(filePath, fileName);
    }
    catch(std::exception e){
        QMessageBox::critical(nullptr, "Error", "Archive corrupted");
        return;
    }
}
