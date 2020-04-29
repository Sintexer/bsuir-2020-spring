#include "coder.h"

void Coder::setSource(QString src){
    source = src;
}

void Coder::setDictionary(QMap<QChar, QString>& dict){
    dictionary = dict;
}

QString Coder::getNextCodeBuffer(){
    return buffer;
}
