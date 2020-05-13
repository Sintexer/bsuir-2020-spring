    #include "filewriter.h"

FileWriter::~FileWriter(){
    if(out.isOpen())
        out.close();
}

void FileWriter::setPath(QString npath){
    path = npath;
}

void FileWriter::setFilename(QString nfilename){
    filename = nfilename;
}

void FileWriter::setExstension(QString nextension){
    extension = nextension;
}

QString FileWriter::getPath(){
    return path;
}

QString FileWriter::getFilename(){
    return filename;
}

QString FileWriter::getExtension(){
    return extension;
}

bool FileWriter::open(){
    if(out.isOpen())
        out.close();
    path +=filename+"."+extension;
    out.setFileName(path);
    out.open(QFile::WriteOnly);
    return out.isOpen();
}

void FileWriter::write(QString buffer){
    if(!out.isOpen())
        throw std::runtime_error("FW: Can't write to closed file");
    out.write(buffer.toLocal8Bit());
}
