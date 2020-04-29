#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "pch.h"

class FileWriter
{
private:
    QFile out;
    QString path;
    QString filename;
    QString extension;
public:
    FileWriter() = default;
    ~FileWriter();
    void setPath(QString npath);
    void setFilename(QString nfilename);
    void setExstension(QString nextension);
    QString getPath();
    QString getFilename();
    QString getExtension();

    bool open();
    void write(QString buffer);
};

#endif // FILEWRITER_H
