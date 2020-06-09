#ifndef CATALOG_H
#define CATALOG_H

#include "pch.h"

class Catalog
{
private:
    QMap<char, int> catalog;
public:
    Catalog() = default;
    Catalog(QByteArray info);

    QMap<char, int>& add(QByteArray info);
    QMap<char, int>& getCatalog();
};

#endif // CATALOG_H
