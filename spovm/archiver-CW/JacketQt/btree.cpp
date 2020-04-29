    #include "btree.h"

void bTree::destroyTree(Node<int, QChar>*& node){
    if(node){
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
        node = nullptr;
    }
}

void bTree::show(){
    printTree(root, 0);
}

void bTree::printTree(Node<int, QChar>* node, int depth){
    if(node){

        printTree(node->left, depth + 1);
        if(node->hasValue()){
            QString t;
            t+=node->getValue();
            t+=":"+node->getCode();
            qDebug()<< t;
        }
        printTree(node->right, depth + 1);
    }
}

void bTree::formCodes(){
    formCodesRec(root, "");
}

void bTree::formCodesRec(Node<int, QChar>* node, QString tempCode){
    if(node){
        if(node->hasValue()){
            node->code = tempCode;
            dictionary[node->value] = tempCode;
        }
        formCodesRec(node->left, tempCode+'1');
        formCodesRec(node->right, tempCode+'0');
    }
}

QMap<QChar, QString>& bTree::getDictionary(){
    return dictionary;
}
