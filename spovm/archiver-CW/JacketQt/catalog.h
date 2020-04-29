#ifndef CATALOG_H
#define CATALOG_H

#include "pch.h"

class Catalog
{
private:
    QMap<QChar, int> catalog;
public:
    Catalog(){}
    Catalog(QString info);

    QMap<QChar, int>& add(QString info);
    QMap<QChar, int>& getCatalog();
    pair<QChar, int> takeTop();
    bool empty();
};

#endif // CATALOG_H
