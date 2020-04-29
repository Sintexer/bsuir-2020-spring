#ifndef NODEVAL_H
#define NODEVAL_H

#include "pch.h"

class NodeVal
{
private:
    pair<int, QChar> nval;
    bool only_count;
public:
    NodeVal() = delete;
    NodeVal(int i, QChar qc): nval(i, qc), only_count(false) {}
    NodeVal(int i): nval(i, 0), only_count(true) {}

    QChar getVal();
    int getCount();
    pair<int, QChar> getNval();
    bool onlyCount();

    bool operator<(NodeVal& other);
    bool operator>(NodeVal& other);
    bool operator==(NodeVal& other);
};

#endif // NODEVAL_H
