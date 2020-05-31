#ifndef FILETRANSLATOR_H
#define FILETRANSLATOR_H

#include "coder.h"
#include "fileentry.h"

#include <QThread>

using namespace std;

class FileTranslator
{  
private:
    QFile fout;
    QFile fin;
    QList<FileEntry> allFiles;
    Coder coder{};
public:
    FileTranslator() = default;
    FileTranslator(QString path): fout(path){
        fout.open(QFile::WriteOnly);
    }

    ~FileTranslator(){
        fout.close();
        fin.close();
    }

    void openFile(QString path_);
    void setAllFiles(QList<FileEntry> allFiles_);
    QList<FileEntry> getAllFiles();
    void translateFiles();
    void translateDictionary();
    void clear();
};

#endif // FILETRANSLATOR_H
