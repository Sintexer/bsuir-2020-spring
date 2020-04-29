    #ifndef BTREE_H
#define BTREE_H

#include "node.h"

class bTree
{
private:
    Node<int, QChar>* root;
    QMap<QChar, QString> dictionary;
public:
    bTree() = delete;
    bTree(Node<int, QChar>* nd): root(nd) {}
    ~bTree(){ destroyTree(root); }

    void destroyTree(Node<int, QChar>*& node);
    void show();
    void printTree(Node<int, QChar>* node, int depth);
    void formCodes();
    void formCodesRec(Node<int, QChar>* node, QString tempCode);
    QMap<QChar, QString>& getDictionary();
};

#endif // BTREE_H
