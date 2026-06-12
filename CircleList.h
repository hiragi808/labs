//
// Created by macbook on 09.03.26.
//

#ifndef LAB11_CIRCLELIST_H
#define LAB11_CIRCLELIST_H

#include <string>
#include "Node.h"

class CircularLinkedList {
private:
    Node* Head;  // Указатель на первый элемент (голову)
    Node* Tail;  // Указатель на последний элемент (хвост)

public:
    CircularLinkedList();
    CircularLinkedList(CircularLinkedList& other);
    ~CircularLinkedList();

    Node* GetHead();
    Node* GetTail();
    void PushBack(int value);     // добавление в конец
    void PushFront(int value);    // добавление в начало
    bool IsEmpty();
    void Clear();
    void Print();
    Node* FindQ(int value);
    // Удаление элемента по указателю
    Node* RemoveNode(Node* nodeToRemove);

    // Методы создания списков
    CircularLinkedList CreateCList();
    CircularLinkedList CreateFromInput();
    CircularLinkedList CreateRandom();
    CircularLinkedList CreateFromFile(std::string filename);
};


#endif //LAB11_CIRCLELIST_H