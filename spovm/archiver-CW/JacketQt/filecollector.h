#ifndef FILECOLLECTOR_H
#define FILECOLLECTOR_H

#include <QDir>
#include <QFile>
#include <QString>
#include <QList>
#include <QThread>
#include "fileentry.h"

class FileCollector
{
private:
    QDir startDir;
    QList<FileEntry> allFiles;
    QStringList allDirs;
public:
    FileCollector(QDir dir){
        startDir = dir;
    }

    QList<FileEntry> collectFiles();
    void collect_files(QDir current, QString relativePath);
    static int dirSize(QString dirPath,  int size, const int max);
    static bool isCorrectFileName(QString path);
};

#endif // FILECOLLECTOR_H
