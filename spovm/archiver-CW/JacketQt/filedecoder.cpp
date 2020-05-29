#include "filedecoder.h"

void FileDecoder::dearchive(QString path, QString fileName){
    input.openFile(path+"/"+fileName);
    outpPath = path;
    readDireactoryTree();
    while (!input.isEnd()){
        if(QThread::currentThread()->isInterruptionRequested())
            return;
        dictionary.clear();
        longestCodeSize = 0;
        QString currentPath = getPath();
        QString currentName = getPath();
        if(!outpPath.isEmpty()){
            currentPath.prepend('/');
            currentPath.prepend(outpPath);
        }
        if(!currentPath.isEmpty()){
            currentName.prepend('/');
            currentName.prepend(currentPath);
        }
        QFile outf(currentName);
        if(!outf.open(QFile::WriteOnly)){
            throw std::runtime_error("FileDecodder::dearchive(): Cant create file");
        }
        if(decodeDictionary())
            decodeFile(outf);
        outf.close();
    }
}

bool FileDecoder::decodeDictionary(){
    int size{};
    QString code;

    size = getNum();
    if(!size){
        return false;                       //if empty file
    }
    do{
        char bt = input.get();
        code+=toCode(bt, size);
        size-=8;
    }while(size>0);
    endCode = code;
    char byte;
    while(true){
        if(QThread::currentThread()->isInterruptionRequested())
            return false;
        code.clear();
        input.get();
        byte = input.get();
        if(dictionary.values().contains(byte))
            break;
        input.get();
        size = getNum();
        do{
            code+=toCode(input.get(), size);
            size-=8;
        }while(size>0);
        dictionary[code]=byte;
    }
    for(QString str: dictionary.keys()){
        if(QThread::currentThread()->isInterruptionRequested())
            return false;
        if (str.length()>longestCodeSize)
            longestCodeSize = str.length();
    }
    return true;
}

int FileDecoder::getNum(){
    QString num{};
    while(input.peek()!='|'){
        num.append(input.get());
    }
    if(num.isNull())
        throw std::runtime_error("DileDecoder::getNum(): Cant get num, archive is corrupted");
    input.get();
    return num.toInt();
}

QByteArray FileDecoder::getPath(){
    QByteArray path{};
    while(input.peek()!='|'){
        path.append(input.get());
    }
    input.get();
    return path;
}

QString FileDecoder::toCode(char c, int length){
    QString code;
    int bit8 = 128;
    if (length>8)
        length = 8;
    while(length){
        if(c&bit8){
            code.append("1");
        }
        else
            code.append("0");
        --length;
        c<<=1;
    }
    return code;
}

void FileDecoder::decodeFile(QFile& outf){
    char byte{};
    int size{};
    int bit8 = 128;
    bool notEnd{true};
    QString code;
    QByteArray buffer;
    while(notEnd){
        if(QThread::currentThread()->isInterruptionRequested())
            return;
        if(!size){
            byte = input.get();
            size = 8;
        }
        while(size){
            if (byte&bit8)
                code.append("1");
            else
                code.append("0");

            if(code.length()>longestCodeSize)
                throw std::runtime_error("FileDecoder::decodeFile(): archive was corrupted");

            byte<<=1;
            --size;
            if(code==endCode){
                notEnd=false;
                break;
            }
            if(dictionary.contains(code)){
                buffer.append(dictionary[code]);
                code.clear();
                if(buffer.size()>128){
                    outf.write(buffer);
                    buffer.clear();
                }
                break;
            }

        }
    }
    if(buffer.size())
        outf.write(buffer);
}

void FileDecoder::readDireactoryTree(){
    QString dir;
    QDir a(outpPath);
    while(input.peek()!='<'){
        if(QThread::currentThread()->isInterruptionRequested())
            return;
        while(input.peek()!='|'){
            dir.append(input.get());
        }
        if(input.peek()=='|'){
            if(!dir.isEmpty()){
                a.mkdir(dir);
            }
        }
        input.get();
        dir.clear();
    }
    input.get();
}
