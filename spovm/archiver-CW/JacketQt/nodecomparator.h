#ifndef NODECOMPARATOR_H
#define NODECOMPARATOR_H

#include "node.h"

struct NodeComparator
{
public:
    bool operator()(Node<int, char>* first, Node<int, char>* second){
        return first->getCount()>second->getCount();
    }
};

#endif // NODECOMPARATOR_H
