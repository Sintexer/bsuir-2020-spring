#include "fileentry.h"

void FileEntry::setPath(QString path_){
    path = path_;
}

QString FileEntry::getPath(){
    return path;
}

void FileEntry::setRelativePath(QString relativePath_){
    relativePath = relativePath_;
}

QString FileEntry::getRelativePath(){
    return relativePath;
}

void FileEntry::setFileName(QString file_name){
    fileName = file_name;
}

QString FileEntry::getFileName(){
    return fileName;
}
