#include "catalog.h"

Catalog::Catalog(QByteArray info){
    add(info);
}

QMap<char, int>& Catalog::add(QByteArray info){
    for(char a : info){
        if(catalog.value(a, 0))
            ++catalog[a];
        else
            catalog[a]=1;
    }
    return catalog;
}

QMap<char, int>& Catalog::getCatalog(){
    return catalog;
}
