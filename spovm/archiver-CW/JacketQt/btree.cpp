#include "btree.h"

void bTree::destroyTree(Node<int, char>*& node){
    if(node){
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
        node = nullptr;
    }
}

void bTree::formCodes(){
    formCodesRec(root, "");
}

void bTree::formCodesRec(Node<int, char>* node, QString tempCode){
    if(node){
        if(node->isEndNode())
            endCode = tempCode;
        if(node->hasValue()){
            node->code = tempCode;
            dictionary[node->value] = tempCode;
        }
        formCodesRec(node->left, tempCode+'1');
        formCodesRec(node->right, tempCode+'0');
    }
}

QMap<char, QString>& bTree::getDictionary(){
    return dictionary;
}

QString bTree::getEndCode(){
    return endCode;
}
