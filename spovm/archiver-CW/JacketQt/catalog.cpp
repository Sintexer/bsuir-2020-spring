#include "catalog.h"

Catalog::Catalog(QString info){
    add(info);
}

QMap<QChar, int>& Catalog::add(QString info){
    for(QChar a : info){
        if(catalog.value(a, 0))
            ++catalog[a];
        else
            catalog[a]=1;
    }
    return catalog;
}

QMap<QChar, int>& Catalog::getCatalog(){
    return catalog;
}

pair<QChar, int> Catalog::takeTop(){
    pair<QChar, int> temp;
    temp.first = catalog.begin().key();
    temp.second = catalog.take(temp.first);
    return temp;
}

bool Catalog::empty(){
    bool answer{false};
    if(catalog.empty())
        answer = true;
    return answer;
}
