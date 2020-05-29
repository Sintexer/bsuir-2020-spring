#include "pch.h"
#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile styles(":style.css");
    if(!styles.open(QFile::ReadOnly))
        throw std::runtime_error("Can't open css file");
    a.setStyleSheet(styles.readAll());
    MainWindow w;
    w.show();

    return a.exec();
}
