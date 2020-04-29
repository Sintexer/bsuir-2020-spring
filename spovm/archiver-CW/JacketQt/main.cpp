#include "pch.h"
#include "mainwindow.h"
#include "catalog.h"
#include "btree.h"
#include "node.h"
#include "treeformer.h"
#include "coder.h"


#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    Node<int, QChar>* nd1 = new Node<int, QChar>(1, 's'),
//            *nd2 = new Node<int, QChar>(2, 'a'),
//            *nd3 = new Node<int, QChar>(3,'e'),
//            *nd4 = new Node<int, QChar>(4, 'r'),
//            *nd5 = new Node<int, QChar>(nd1, nd2),
//            *nd6 = new Node<int, QChar>(nd3, nd4),
//            *nd7 = new Node<int, QChar>(nd5, nd6);
//    bTree *nw = new bTree(nd7);
//    delete nw;

    QString info;
    QFile file_in("input.txt");
    QFile file_out("output.txt");
    qDebug() << "Started\n";
    if(!file_in.open(QFile::ReadOnly)){
        qDebug() << "Can't open input file";
        a.exec();
    }
    if(!file_out.open(QFile::WriteOnly)){
        qDebug() << "Can't open output file";
        a.exec();
    }
    info = file_in.readAll();
    Catalog cat(info);
    TreeFormer trf(cat.getCatalog());
    bTree bt = trf.formBTree();
    bt.formCodes();
    Coder coder;
    coder.setDictionary(bt.getDictionary());
    QMap<QChar, QString> maper = bt.getDictionary();
    for(auto a: maper.keys()){
        qDebug() << a << ":" << maper[a];
    }
    file_out.write(info.toLocal8Bit());
    file_in.close();
    file_out.close();


    return a.exec();
}
