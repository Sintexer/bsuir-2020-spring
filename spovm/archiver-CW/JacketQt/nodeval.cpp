#include "nodeval.h"

QChar NodeVal::getVal(){
    return nval.second;
}

int NodeVal::getCount(){
    return nval.first;
}

pair<int, QChar> NodeVal::getNval(){
    return nval;
}

bool NodeVal::onlyCount(){
    return only_count;
}
