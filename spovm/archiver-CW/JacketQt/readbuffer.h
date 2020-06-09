#ifndef READBUFFER_H
#define READBUFFER_H

#include <QFile>

class ReadBuffer
{
private:
    QFile fin;
    char* buffer;
    const size_t inputSize;
    size_t index{};
    size_t readen{};
public:
    ReadBuffer(size_t inputSize_): inputSize(inputSize_){
        buffer = new char[inputSize];
        index = inputSize;
    }

    ~ReadBuffer(){
        delete[] buffer;
        fin.close();
    }

    void openFile(QString fileName){
        if(fin.isOpen())
            fin.close();
        fin.setFileName(fileName);
        fin.open(QFile::ReadOnly);
    }

    char get(){
        nextBuffer();
        return buffer[index++];
    }

    char peek(){
        nextBuffer();
        return buffer[index];
    }

    void nextBuffer(){
        if(!(index<inputSize)){
            memset(buffer, 0, inputSize);
            if(fin.atEnd()){
                throw std::runtime_error("ReadBuffer::nextBuffer(): File was corrupted");
            }
            readen = fin.read(buffer, inputSize);
            index=0;
        }
    }

    bool isEnd(){
        if(index<readen)
            return false;
        else
            return fin.atEnd();
    }

    void close(){
        fin.close();
    }
};

#endif // READBUFFER_H
