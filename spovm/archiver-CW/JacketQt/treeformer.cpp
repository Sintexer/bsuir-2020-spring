#include "treeformer.h"

TreeFormer::TreeFormer(QMap<QChar, int> cat){
    for(QChar a: cat.keys()){
        Node<int, QChar> *temp = new Node<int, QChar>(cat[a], a);
        nodes.push(temp);
    }
}
void TreeFormer::add(Node<int, QChar>* nw){
    nodes.push(nw);
}

Node<int, QChar>* TreeFormer::take(){
    Node<int, QChar>* temp = nodes.top();
    nodes.pop();
    return temp;
}

Node<int, QChar>* TreeFormer::formBTree(){
    Node<int, QChar>* tree;
    if(nodes.empty())
        tree = nullptr;
    Node<int, QChar>* left, *right;
    while(nodes.size()>1){
         left = take();
         right = take();
         Node<int, QChar>* temp = new Node<int, QChar>(left, right);
         nodes.push(temp);
    }
    tree = take();
    return tree;
}
