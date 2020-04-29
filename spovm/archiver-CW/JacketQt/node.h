#ifndef NODE_H
#define NODE_H

#include "pch.h"

template <typename T, typename N>
class Node {
    /*Класс узла, в котором хранится значение шаблонного типа и число,
    а также два указателя, налево и направо
    слева храннится елемент, который меньше элемента в узле
    справа наоборот*/
private:
    bool has_value{true};
public:
    QString code;
    T count{};
    N value{};                                                                  //Значение узла

    Node<T, N>* left{}, *right{};							//Ссылки налево и направо

    Node() = default;
    Node(T cnt, N val): count(cnt), value(val), left(nullptr), right(nullptr), has_value(true) {}
    Node(Node<T, N>* lef, Node<T, N>* rgt) : left(lef), right(rgt), has_value(false) {
        count = left->count+right->count;
    }
    ~Node() {
        qDebug() << "Deleting";
        if(left)
            delete left;
        if(right)
            delete right;
    }

    T getCount(){
        return count;
    }

    N getValue(){
        return value;
    }

    QString getCode(){
        return code;
    }

    bool hasValue(){
        return has_value;
    }

    bool operator>(Node<T, N> other){
        return count>other.getCount();
    }

    bool operator<(Node<T, N> other){
        return count<other.getCount();
    }

    bool operator==(Node<T, N> other){
        return count==other.getCount();
    }

    bool operator!=(Node<T, N> other){
        return !count==other.getCount();
    }
};

#endif // NODE_H
