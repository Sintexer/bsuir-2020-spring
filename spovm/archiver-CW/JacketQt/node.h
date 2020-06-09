#ifndef NODE_H
#define NODE_H

#include "pch.h"

template <typename T, typename N>
class Node {
private:
    bool has_value{true};
public:
    QString code;
    T count{};
    N value{};
    Node<T, N>* left = nullptr, *right = nullptr;
    bool endNode{false};

    Node() = default;
    Node(T cnt): count(cnt), left(nullptr), right(nullptr), has_value(false), endNode(true) {}
    Node(T cnt, N val): count(cnt), value(val), left(nullptr), right(nullptr), has_value(true) {}
    Node(Node<T, N>* lef, Node<T, N>* rgt) : left(lef), right(rgt), has_value(false) {
        count = left->count+right->count;
    }
    ~Node() {
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


    void setEndNode(bool t){
        endNode = t;
    }

    bool isEndNode(){
        return endNode;
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
