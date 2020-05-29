#include "treeformer.h"

TreeFormer::TreeFormer(QMap<char, int> cat){
    for(char a: cat.keys()){
        Node<int, char> *temp = new Node<int, char>(cat[a], a);
        nodes.push(temp);
    }
}
void TreeFormer::add(Node<int, char>* nw){
    nodes.push(nw);
}

Node<int, char>* TreeFormer::take(){
    Node<int, char>* temp = nodes.top();
    nodes.pop();
    return temp;
}

Node<int, char>* TreeFormer::formBTree(){
    Node<int, char>* tree;
    if(nodes.empty())
        tree = nullptr;
    Node<int, char>* left, *right;
    Node<int, char> *temp = new Node<int, char>(0);
    nodes.push(temp);
    while(nodes.size()>1){
         left = take();
         right = take();
         Node<int, char>* temp = new Node<int, char>(left, right);
         nodes.push(temp);
    }
    tree = take();
    return tree;
}
