#ifndef FILEENTRY_H
#define FILEENTRY_H

#include <QString>

class FileEntry
{
private:
    QString path;
    QString relativePath;
    QString fileName;
public:
    FileEntry(QString path_, QString relativePath_, QString file_name){
        path = path_;
        relativePath = relativePath_;
        fileName = file_name;
    }

    void setPath(QString path_);
    QString getPath();
    void setRelativePath(QString relativePath_);
    QString getRelativePath();
    void setFileName(QString file_name);
    QString getFileName();
};

#endif // FILEENTRY_H
