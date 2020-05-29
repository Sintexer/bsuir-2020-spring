#ifndef TREEFORMER_H
#define TREEFORMER_H

#include "pch.h"
#include "node.h"
#include "nodecomparator.h"

class TreeFormer
{
private:
    priority_queue<Node<int, char>*, vector<Node<int, char>*>, NodeComparator> nodes;
public:
    TreeFormer() {};
    TreeFormer(QMap<char, int> cat);

    void add(Node<int, char>* nw);
    Node<int, char>* take();
    Node<int, char>* formBTree();
};

#endif // TREEFORMER_H
