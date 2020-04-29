#ifndef TREE_H
#define TREE_H

#include "pch.h"

template <typename T>
class Tree {
public:
    template <typename N>
    class Node {
        /*Класс узла, в котором хранится значение шаблонного типа
        а также два указателя, налево и направо
        слева храннится елемент, который меньше элемента в узле
        справа наоборот*/
    public:
        N value{};																//Значение узла
        Node<N>* left{ nullptr }, * right{ nullptr };							//Указатели налево и направо
        Node<N>* parent{};														//Указатель на родителя

        Node() = default;
        Node(T val, Node<T>* lef, Node<T>* rgt, Node<T>* prnt) :value(val), left(lef), right(rgt), parent(prnt) {}
        ~Node() {
            delete left, right, parent;
        }
    };
private:

    Node<T>* root;																//В этой переменной хранится корень дерева

protected:
    void popItem(Node<T>*& tree, T val);
                                                                                /*Данный метод рекурсивно ищет узел со значением val
                                                                                При нахождении узла вызывает по отношению к нему метод deleteNode
                                                                                Тем самым данный метод производит поиск нужного для удаления узла*/

    void insertItem(Node<T>*& tree, T newItem, Node<T>* prnt);					/*Данный метод рекурсивно ищет узел со значением newItem
                                                                                Если такой узел существует, то значение не вставляется
                                                                                Если же такого узла нет, то метод остановится на узле со значением nullptr
                                                                                В который можно вставить новое значение, не нарушая структуру дерева поиска*/

    void extractMostLeft(Node<T>*& node, T& val);								/*Копирует значение самого левого от node узла, а затем удаляет этот самый левый узел
                                                                                Данный метод необходим для удаления узла с двумя наследниками*/

    void deleteNode(Node<T>*& node);											/*Удалает переданный в метод Узел
                                                                                Обрабатывает 4 ситуации:
                                                                                1) Узел не имеет наследников
                                                                                2) Узел имеет только левого наследника
                                                                                3) Узел имеет только правого наследника
                                                                                4) Узел имеет 2 наследника
                                                                                Все ситуации, кроме номера 4 обрабатываются прямо в теле метода
                                                                                Для ситуации 4 используется метод извлечения узла extractMostLeft*/

    void nodeAmount(Node<T>*& node, size_t& size);								//Считает число узлов дерева рекурсивно

    void copyTree(Node<T>* tree, Node<T>*& newTree) const;						//Копирует все ноды дерева tree в дерево newTree

    virtual void printTree(Node<T>* current, int level = 0);					//Рекурсивный симметричный вывод дерева в консоль (Дерево лежит боком)

public:



    class iterator {
        friend class Tree;
    private:
        Node<T>* current{};														//Указатель на текущую ноду
    public:
        iterator() : current(nullptr) {};

        const Tree<T>::iterator operator++();									//Переход к следующему элементу дерева, возвращает итератор после изменения
        const Tree<T>::iterator operator++(int);								//Переход к следующему элементу дерева, возвращает итератор до изменения
        const Tree<T>::iterator operator--();									//Переход к предыдущему элементу дерева, возвращает итератор после изменения
        const Tree<T>::iterator operator--(int);								//Переход к предыдущему элементу дерева, возвращает итератор до изменения

        void operator+=(int num);												//Совершает переданное число итераций вперед по дереву
        void operator-=(int num);												//Совершает переданное число итераций назад по дереву

        bool operator==(Tree<T>::iterator rht);									//Сравнивает значения узлов, на которые указывают итераторы
        bool operator!=(Tree<T>::iterator rht);									//Сравнивает значения узлов, на которые указывают итераторы

        T& operator*();															//Возвращает ссылку на значение узла, на который указывает итератор
    };

    //
    // M
    // E
    // T
    // H
    // O
    // D
    // S
    //

    Tree() : root(nullptr) {}
    Tree(const Tree& tr) : root(std::move(tr.root)) {}
    Tree(T val);
    virtual ~Tree();

    Node<T>*& getRoot();														//Возвращает ссылку на указатель на корень дерева
    virtual bool empty();														//Возвращает true, если в дереве нет узлов

    virtual size_t size();														//Считает вершины дерева, включая корень

    virtual void insert(T val);													//Метод вставки значения в дерево, использует protected method insertItem
    virtual void pop(T val);													//Ищет значение val в дереве и производит удаление ноду

    virtual void show();														//Выводит значения узлов дерева на экран

    Tree<T>::iterator begin();													//Возвращает итератор на первый элемент дерева
    Tree<T>::iterator end();													//Возвращает итератор на следующий за последним элемент дерева
    Tree<T>::iterator find(T obj);												//Возвращает итератор на вхождение элемента в дерево, Если в дереве элемента нет, то итератор указывает на nullptr

    void destroyTree(Node<T>*& tree);											//Очищает все дерево рекурсивно, освобождает память на указатели нод
};

template<typename T>
void Tree<T>::popItem(Node<T>*& tree, T val) {
    if (!tree){																	//Такой ноды нет
        return;																	//Конец рекурсии
    }
    else if (val == tree->value){												//Необходимый узел найден
        deleteNode(tree);														//Удаление узла
    }
                                                                                //Поиск нужного узла
    else if (val < tree->value)
        popItem(tree->left, val);												//Поиск в левом поддереве, если искомое значение меньше значения текущего узла
    else
        popItem(tree->right, val);												//Поиск в правом поддереве
}

template<typename T>
void Tree<T>::insertItem(Node<T>*& tree, T newItem, Node<T>* prnt) {
    if (!tree){																	//Если найдено нужное место
        tree = new Node<T>(newItem, nullptr, nullptr, prnt);					//Выделение памяти под новый узел
    }
    else if (newItem == tree->value){											//Такая нода уже есть
        return;																	//Конец рекурсии
    }
                                                                                //Поиск нужного места по новый узел
    else if (newItem < tree->value) {											//Поиск в левом поддереве, если искомое значение меньше значения текущего узла
        prnt = tree;															//Сохранение предыдущего узла, чтобы можно было указать родителя нового узла
        insertItem(tree->left, newItem, prnt);
    }
    else {																		//Поиск в правом поддереве
        prnt = tree;															//Сохранение предыдущего узла, чтобы можно было указать родителя нового узла
        insertItem(tree->right, newItem, prnt);
    }
}

template<typename T>
void Tree<T>::extractMostLeft(Tree::Node<T>*& node, T& val) {					//Извлекает значение самого левого узла и удаляет его
    if (!node->left){															//Если самый левый элемент найден
        val = node->value;														//Сохранение значения самого левого узла
        Node<T>* del = node;													//Создание аременного указателя для удаления узла
        node = node->right;														//Если у удаляемого узла есть правый наследник, то он встает на место удаляемого узла
        if (node)																//Если у удаляемого узла правый наследник был
            node->parent = del->parent;											//Родителем правого узла станет родитель удаляемого узла
        delete del;																//Удаление самого левого узла
    }
    else																		//Поиск самого левого узла
        extractMostLeft(node->left, val);
}

template<typename T>
void Tree<T>::deleteNode(Node<T>*& node) {										//Удаляет ноду
    Node<T>* del;																//Временный указатель для удаления
    T replaceVal;																//Для узла с двумя наследниками
    if (node->left == nullptr && node->right == nullptr){						//Если у узла нет наследников
        delete node;															//Просто удаляем его
        node = nullptr;
    }
    else if (!node->left){														//Если у узла есть только правый наследник
        del = node;																//Указатель на узел, который надо удалить
        node = node->right;														//Помещение правого наследника на место, откуда будет удален узел
        node->parent = del->parent;												//Родителем перемещенного узла станет родитель удаленного
        del->right = nullptr;
        delete del;																//Удаление узла
    }
    else if (!node->right){														//Если у узла есть только левый наследник
        del = node;																//Указатель на узел, который надо удалить
        node = node->left;														//Помещение левого наследника на место, откуда будет удален узел
        node->parent = del->parent;												//Родителем перемещенного узла станет родитель удаленного
        del->left = nullptr;
        delete del;																//Удаление узла
    }
    else																		//Если у ноды два наследника
    {
        extractMostLeft(node->right, replaceVal);
        node->value = replaceVal;
    }
}

template<typename T>
void Tree<T>::nodeAmount(Tree::Node<T>*& node, size_t& size) {					//Метод подсчитывает количество нод в дереве
    if (node){
        ++size;
        nodeAmount(node->left, size);
        nodeAmount(node->right, size);
    }
}

template<typename T>
void Tree<T>::copyTree(Tree::Node<T>* tree, Tree::Node<T>*& newTree) const {	//Метод копирует ноды в новое дерево
    if (tree)
    {
        newTree = new Node<T>(tree->value, nullptr, nullptr);
        copyTree(tree->left, newTree->left);
        copyTree(tree->right, newTree->right);
    }
    else
        newTree = nullptr;
}

template<typename T>
void Tree<T>::printTree(Tree::Node<T>* current, int level) { //Метод выводит дерево
    if (current)
    {
        printTree(current->left, level + 1);
        cout << current->value << std::endl;
        printTree(current->right, level + 1);
    }
}

template<typename T>
const typename Tree<T>::iterator Tree<T>::iterator::operator++() {
    Node<T>* temp;
    if (current->right)
    //Если есть наследники справа
    {
        current = current->right;//Переход вправо
        while (current->left)//Проход до конца влево
            current = current->left;
    }
    else//Если наследников справа нет
    {
        temp = current->parent;
        while (temp && current == temp->right) //Переход наверх
        {
            current = temp;
            temp = temp->parent;
        }
        current = temp;
    }
    return *this;
}

template<typename T>
const typename Tree<T>::iterator Tree<T>::iterator::operator++(int) {
    Tree<T>::iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
const typename Tree<T>::iterator Tree<T>::iterator::operator--() {
    Node<T>* temp;
    if (current->left)//Если есть наследники слева
    {
        current = current->left;//Шаг влево
        while (current->right)//Проход до конца вправо
            current = current->right;
    }
    else//Если наследников слева нет
    {
        temp = current->parent;//Проход вверх
        while (temp && current == temp->left)
        {
            current = temp;
            temp = temp->parent;
        }
        current = temp;
    }
    return *this;
}

template<typename T>
const typename Tree<T>::iterator Tree<T>::iterator::operator--(int) {
    Tree<T>::iterator temp = *this;
    --(*this);
    return temp;
}

template<typename T>
void Tree<T>::iterator::operator+=(int num) {
    if (num < 0)
        * this -= (-1 * num);
    else
        while (num > 0)
        {
            ++(*this);
            --num;
        }
}

template<typename T>
void Tree<T>::iterator::operator-=(int num) {
    if (num < 0)
        * this += (-1 * num);
    else
        while (num > 0)
        {
            --(*this);
            --num;
        }
}

template<typename T>
bool Tree<T>::iterator::operator==(Tree<T>::iterator rht) {
    return current == rht.current;
}

template<typename T>
bool Tree<T>::iterator::operator!=(Tree<T>::iterator rht) {
    return !(*this == rht);
}

template<typename T>
T& Tree<T>::iterator::operator*(){ //Возвращает сслку на узел, на который указывает итератор
    return current->value;
}

template<typename T>
Tree<T>::Tree(T val) {
    root = new Node<T>(val, nullptr, nullptr);
}

template<typename T>
Tree<T>::~Tree() {
    destroyTree(root);
}

template<typename T>
typename Tree<T>::template Node<T>*& Tree<T>::getRoot() {
    return root;
}

template<typename T>
bool Tree<T>::empty() {
    return !root;
}

template<typename T>
size_t Tree<T>::size() {
    size_t size{};
    nodeAmount(root, size);
    return size;
}

template<typename T>
void Tree<T>::insert(T val) {
    insertItem(root, val, nullptr);
}

template<typename T>
void Tree<T>::pop(T val) {
    popItem(root, val);
}

template<typename T>
void Tree<T>::show() {
    printTree(getRoot(), 0);
    std::cout << std::endl;
}

template<typename T>
typename Tree<T>::iterator Tree<T>::begin() {//Итератор на начало дерева
    Tree<T>::iterator it;
    Node<T>* temp = root;
    if (!temp)
        return it;
    while (temp->left)
        temp = temp->left;
    it.current = temp;
    return it;
}

template<typename T>
typename Tree<T>::iterator Tree<T>::end() {//Итератор на конец дерева
    return Tree<T>::iterator();
}

template<typename T>
inline typename Tree<T>::iterator Tree<T>::find(T obj){
    Tree<T>::iterator it = begin();
    while (*it) {
        if (*it == obj)
            return it;
        ++it;
    }
    return it;
}

template<typename T>
void Tree<T>::destroyTree(Tree::Node<T>*& tree) {
    if (tree)
    {
        destroyTree(tree->left);
        destroyTree(tree->right);
        delete tree;
        tree = nullptr;
    }
}


#endif // TREE_H
