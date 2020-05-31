#ifndef CODER_H
#define CODER_H

#include "pch.h"

class Coder
{
private:
    QString endCode;
    char prev;
    bool leftPrev;
    short prevSize;
    int len{};
    QMap<char, QString> dictionary;

public:
    Coder():leftPrev(false), prevSize(0) {}
    bool hasPrev();
    char getPrev();
    void setDictionary(QMap<char, QString>& dict);
    QMap<char, QString> getDictionary();
    void setEndCode(QString code);
    QString getEndCode();
    QByteArray getEof();
    QByteArray encode(char sb);
    QByteArray getNextCodeBuffer(QByteArray source);
    void clear();

    static char formByte(QString code);
    static QByteArray formBytes(QString code);
};

#endif // CODER_H
