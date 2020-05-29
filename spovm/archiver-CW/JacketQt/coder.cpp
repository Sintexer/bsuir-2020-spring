#include "coder.h"

bool Coder::hasPrev(){
    return leftPrev;
}

char Coder::getPrev(){
    return prev;
}

void Coder::setDictionary(QMap<char, QString>& dict){
    dictionary = dict;
}

QMap<char, QString> Coder::getDictionary(){
    return dictionary;
}

void Coder::setEndCode(QString code){
    endCode = code;
}
QString Coder::getEndCode(){
    return endCode;
}

QByteArray Coder::getEof(){
    char byte{0};
    int counter{8};
    QByteArray bf;
    if(hasPrev()){
        byte = prev;
        counter = 8-prevSize;
    }
    for(QChar bit: endCode){
        if(!counter){
            bf += byte;
            byte = 0;
            counter = 8;
        }
        else
            byte<<=1;
        if(bit=='1'){
            byte|=1;
        }
        --counter;
    }
    byte<<=counter;
    bf+=byte;
    prev = 0;
    leftPrev = false;
    prevSize = 0;
    return bf;
}

QByteArray Coder::encode(char sb){
    QByteArray bf;
    QString code;
    char byte{0};
    code = dictionary[sb];
    int counter = 8;
    if(leftPrev){
        leftPrev = false;
        byte = prev;
        counter = 8 - prevSize;
    }
    for(QChar bit: code){
        if(!counter){
            bf += byte;
            byte = 0;
            counter = 8;
        }
        else
            byte<<=1;
        if(bit=='1'){
            byte|=1;
        }
        --counter;

    }
    bf+=byte;
    return bf;
}

//Length of code must be less than 8, but greater than 0
char Coder::formByte(QString code){
    if(code.length() > 8|| code.length() < 1)
        throw std::runtime_error("Coder::formByte: argument length must less than be 8, but greater than 0");
    char byte{0};

    for(QChar bit: code){
        byte<<=1;
        if(bit=='1')
            byte|=1;
    }
    byte<<=8-code.length();
    return byte;
}

//Returns string of bytes aligned by left: 111 represented as 1110000, not 00000111
QByteArray Coder::formBytes(QString code){
    if(!code.size())
        throw std::runtime_error("Coder::formBytes: code size must be greater than 0");
    QByteArray bf;
    while(code.size()>8){
        bf+=formByte(code.left(8));
        code = code.right(code.length()-8);
    }
    bf+=formByte(code.left(8));
    return bf;
}

QByteArray Coder::getNextCodeBuffer(QByteArray source){
    QByteArray temp;
    QByteArray buf;
    for(char sb: source){
        temp = encode(sb);
        len += dictionary[sb].length();
        int i{};
        while(len>=8){
            buf+=temp[i++];
            len-=8;
        }
        if(len){
            prevSize = len;
            prev = temp[i];
            leftPrev = true;
        }
        else
            leftPrev = false;
    }
    //qDebug() << buf;
    return buf;
}

void Coder::clear(){
    dictionary.clear();
    endCode.clear();
    len = 0;
    leftPrev = false;
    prevSize = 0;
    prev = 0;
}
