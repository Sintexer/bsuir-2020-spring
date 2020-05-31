#include "dearchivationthread.h"

void DearchivationThread::run(){
    try{
        FileDecoder fd;
        fd.dearchive(filePath, fileName);
    }
    catch(std::runtime_error e){
        emit exception_executed(e.what());
    }
}
