#ifndef TREEFORMER_H
#define TREEFORMER_H

#include "pch.h"
#include "node.h"
#include "nodecomparator.h"

class TreeFormer
{
private:
    priority_queue<Node<int, QChar>*, vector<Node<int, QChar>*>, NodeComparator> nodes;
public:
    TreeFormer() {};
    TreeFormer(QMap<QChar, int> cat);

    void add(Node<int, QChar>* nw);
    Node<int, QChar>* take();
    Node<int, QChar>* formBTree();
};

#endif // TREEFORMER_H
