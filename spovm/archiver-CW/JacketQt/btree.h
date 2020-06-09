#ifndef BTREE_H
#define BTREE_H

#include "node.h"

class bTree
{
private:
    Node<int, char>* root;
    QString endCode;
    QMap<char, QString> dictionary;
public:
    bTree() = delete;
    bTree(Node<int, char>* nd): root(nd) {}
    ~bTree(){ destroyTree(root); }

    void destroyTree(Node<int, char>*& node);
    void formCodes();
    void formCodesRec(Node<int, char>* node, QString tempCode);
    QString getEndCode();
    QMap<char, QString>& getDictionary();
};

#endif // BTREE_H
