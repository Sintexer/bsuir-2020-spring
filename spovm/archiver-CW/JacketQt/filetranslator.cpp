#include "filetranslator.h"
#include "catalog.h"
#include "treeformer.h"
#include "btree.h"

void FileTranslator::openFile(QString path_){
    if(fout.isOpen())
        fout.close();
    fout.setFileName(path_);
    fout.open(QFile::WriteOnly);
}

void FileTranslator::translateFiles(){
    const int BUFFER_SIZE = 512;
    QByteArray buf{};

    if(allFiles.isEmpty())
        throw std::runtime_error("FileTranslator::translateFiles():allFiles is empty");

    buf.clear();
    buf.append(allFiles.front().getPath());
    fout.write(buf);
    allFiles.pop_front();
    while(allFiles.size()){
        if(QThread::currentThread()->isInterruptionRequested()){
            clear();
            return;
        }
        coder.clear();
        QString path = allFiles.front().getRelativePath();
        buf.clear();
        buf.append(path);
        buf.append("|");
        buf.append(allFiles.front().getFileName());
        buf.append("|");
        fout.write(buf);

        path = allFiles.front().getPath();
        QFile inf(path);
        if(!inf.open(QFile::ReadOnly)){
            throw runtime_error("Can't open input file");
        }
        Catalog cat;

        buf.clear();
        allFiles.pop_front();

        if(inf.size())
            do{
                if(QThread::currentThread()->isInterruptionRequested()){
                    clear();
                    return;
                }
                buf = inf.read(BUFFER_SIZE);
                if(buf.isNull() || !buf.size())
                    break;
                cat.add(buf);
            }while(!buf.isNull());
        else{
            buf.clear();
            buf.append("0|");
            fout.write(buf);
            buf.clear();
            qDebug() << "File is empty";
            continue;
        }

        TreeFormer trf(cat.getCatalog());
        bTree tree = trf.formBTree();
        tree.formCodes();
        coder.setDictionary(tree.getDictionary());
        coder.setEndCode(tree.getEndCode());

        translateDictionary();

        inf.seek(0);
        do{
            if(QThread::currentThread()->isInterruptionRequested()){
                clear();
                return;
            }
            buf = inf.read(BUFFER_SIZE);
            if(buf.isNull() || !buf.size())
                break;
            fout.write(coder.getNextCodeBuffer(buf));
            fout.flush();
        }while(!buf.isNull());
        fout.write(coder.getEof());
        fout.flush();
    }
    fout.close();
}

void FileTranslator::translateDictionary(){
    QString temp;
    fout.write(std::to_string(coder.getEndCode().size()).c_str());
    fout.write("|");
    temp = coder.getEndCode();
    fout.write(Coder::formBytes(temp));

    for(char key: coder.getDictionary().keys()){
        if(QThread::currentThread()->isInterruptionRequested()){
            clear();
            return;
        }
        QByteArray arr;
        arr.clear();
        arr.append("|");
        arr.append(key);
        arr.append("|");
        arr.append(to_string(coder.getDictionary()[key].length()).c_str());
        arr.append("|");
        arr.append(Coder::formBytes(coder.getDictionary()[key]));
        fout.write(arr);
    }
    fout.write("|");
    fout.putChar(coder.getDictionary().keys()[0]);
}


void FileTranslator::setAllFiles(QList<FileEntry> allFiles_){
    allFiles = allFiles_;
}

QList<FileEntry> FileTranslator::getAllFiles(){
    return allFiles;
}

void FileTranslator::clear(){
    if(fout.isOpen())
        fout.close();
    if(fin.isOpen())
        fin.close();
    allFiles.clear();
    coder.clear();
}
