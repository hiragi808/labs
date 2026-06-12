//
// Created by macbook on 09.03.26.
//

#ifndef LAB11_NODE_H
#define LAB11_NODE_H


class Node {
private:
    int data;
    Node* next;
    Node* prev;

public:
    // Конструкторы
    Node();
    explicit Node(int value);
    Node(int value, Node* nextNode, Node* prevNode = nullptr);

    // Геттеры
    int getData();
    Node* getNext();
    Node* getPrev();

    // Сеттеры
    void setData(int value);
    void setNext(Node* nextNode);
    void setPrev(Node* prevNode);
};

#endif //LAB11_NODE_H