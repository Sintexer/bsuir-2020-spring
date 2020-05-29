#ifndef FILEDECODER_H
#define FILEDECODER_H

#include "pch.h"
#include "readbuffer.h"

#include <QThread>
#include <QDir>

class FileDecoder
{
private:
    ReadBuffer input;
    QMap<QString, char> dictionary{};
    QString dirName{};
    QString endCode{};
    QString outpPath{};
    QString mainDir{};
    int longestCodeSize{};
public:
    FileDecoder():input(5120) {}
    void dearchive(QString path, QString fileName);
    bool decodeDictionary();
    void decodeFile(QFile& outf);
    void readDireactoryTree();
    int getNum();
    QByteArray getPath();
    QString toCode(char c, int length);
};

#endif // FILEDECODER_H
