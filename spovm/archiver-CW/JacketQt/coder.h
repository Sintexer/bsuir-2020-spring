#ifndef CODER_H
#define CODER_H

#include "pch.h"
#include "filewriter.h"

class Coder
{
private:
    QString source;
    QString buffer;
    QChar prev;
    bool leftPrev;
    short prevSize;
    QMap<QChar, QString> dictionary;
    FileWriter fw;

public:
    Coder():leftPrev(false), prevSize(0) {}
    void setSource(QString src);
    void setDictionary(QMap<QChar, QString>& dict);
    QString getNextCodeBuffer();
};

#endif // CODER_H
