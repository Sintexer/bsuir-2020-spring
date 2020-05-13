    #ifndef CODER_H
#define CODER_H

#include "pch.h"
#include "filewriter.h"

class Coder
{
private:
    QString buffer;
    char prev;
    bool leftPrev;
    short prevSize;
    QMap<QChar, QString> dictionary;

public:
    Coder():leftPrev(false), prevSize(0) {}
    bool hasPrev();
    char getPrev();
    void setDictionary(QMap<QChar, QString>& dict);
    string encode(QChar sb);
    string getNextCodeBuffer(QString source);
};

#endif // CODER_H
