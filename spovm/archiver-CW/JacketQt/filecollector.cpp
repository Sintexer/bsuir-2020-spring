#include "filecollector.h"
#include <QDebug>

QList<FileEntry> FileCollector::collectFiles(){
    collect_files(startDir, startDir.dirName());
    QString allDirsLine;
    for(QString dir: allDirs){
        if(QThread::currentThread()->isInterruptionRequested())
            return allFiles;
        allDirsLine.append(dir);
        allDirsLine.append('|');
    }
    allDirsLine.append('<');
    FileEntry temp(allDirsLine, "", "");
    allFiles.push_front(temp);
    return allFiles;
}

void FileCollector::collect_files(QDir current, QString relativePath){
    if(QThread::currentThread()->isInterruptionRequested())
        return;
    QStringList files = current.entryList(QDir::Files | QDir::NoDotAndDotDot);
    QStringList dirs = current.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    if(!relativePath.isEmpty() && !allDirs.contains(relativePath))
        allDirs.push_back(relativePath);
    for(QString file: files){
        if(QThread::currentThread()->isInterruptionRequested())
            return;
        qDebug() << file << "   " << relativePath;
        FileEntry temp(current.absolutePath()+QDir::separator()+file, relativePath, file);
        allFiles.append(temp);
    }
    for(QString dir: dirs){
        if(QThread::currentThread()->isInterruptionRequested())
            return;
        QDir temp(current.absolutePath()+QDir::separator()+dir);
        collect_files(temp, relativePath+"/"+dir);
    }
}

int FileCollector::dirSize(QString dirPath, int size, const int max){
    QDir dir{dirPath};
    for(QString filePath: dir.entryList(QDir::Files | QDir::System | QDir::Hidden)){
        ++size;
    }
    for(QString childDirPath: dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::System | QDir::Hidden)){
        ++size;
        size=dirSize(dirPath+QDir::separator()+childDirPath, size, max);
        if(size>50)
            return size;
    }
    return size;
}

bool FileCollector::isCorrectFileName(QString path){
    // Anything following the raw filename prefix should be legal.
    if (path.left(4)=="\\\\?\\")
        return true;

    // Windows filenames are not case sensitive.
    path = path.toUpper();

    // Trim the drive letter off
    if (path[1]==':' && (path[0]>='A' && path[0]<='Z'))
        path = path.right(path.length()-2);

    QString illegal="\\/<>:\"|?*";

    foreach (const QChar& c, path)
    {
        // Check for control characters
         if (c.toLatin1() > 0 && c.toLatin1() < 32)
            return false;

        // Check for illegal characters
        if (illegal.contains(c))
            return false;
    }

    // Check for device names in filenames
    static QStringList devices;

    if (!devices.count())
        devices << "CON" << "PRN" << "AUX" << "NUL" << "COM0" << "COM1" << "COM2"
                << "COM3" << "COM4" << "COM5" << "COM6" << "COM7" << "COM8" << "COM9" << "LPT0"
                << "LPT1" << "LPT2" << "LPT3" << "LPT4" << "LPT5" << "LPT6" << "LPT7" << "LPT8"
                << "LPT9";

    const QFileInfo fi(path);
    const QString basename = fi.baseName();

    foreach (const QString& s, devices)
        if (basename == s)
            return false;

    // Check for trailing periods or spaces
    if (path.right(1)=="." || path.right(1)==" ")
        return false;

    // Check for pathnames that are too long (disregarding raw pathnames)
    if (path.length()>260)
        return false;

    // Exclude raw device names
    if (path.left(4)=="\\\\.\\")
        return false;

    // Since we are checking for a filename, it mustn't be a directory
    if (path.right(1)=="\\")
        return false;

    return true;
}
