#include "coder.h"

bool Coder::hasPrev(){
    return leftPrev;
}

char Coder::getPrev(){
    return prev;
}

void Coder::setDictionary(QMap<QChar, QString>& dict){
    dictionary = dict;
}

string Coder::encode(QChar sb){
    string bf;
    QString code;
    char byte{0};
    code = dictionary[sb];
    //qDebug() << code;
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
    if(counter<8)
        bf+=byte;
    return bf;
}

string Coder::getNextCodeBuffer(QString source){
    string temp;
    string buf;
    int len{};
    for(QChar sb: source){
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
    }
    return buf;
}
