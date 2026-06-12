//
// Created by macbook on 09.03.26.
//

#ifndef LAB11_DOUBLLIST_H
#define LAB11_DOUBLLIST_H

#include "Node.h"
#include <string>
class DoublyLinkedList {
private:
    Node* Head;
    Node* Tail;

public:
    DoublyLinkedList();
    DoublyLinkedList(DoublyLinkedList& other);
    ~DoublyLinkedList();

    Node* GetHead();
    Node* GetTail();
    void PushBack(int value);     // добавление в конец
    void PushFront(int value);    // добавление в начало
    void Insert(int value, int position); // вставка по позиции
    int RemoveFirst();             // удаление первого
    bool IsEmpty();
    void Clear();
    void Print();
    int GetSize();
    void InsertSorted(int value);
    bool IsSorted();
    bool AllUnique();
    Node* FindD(int value);
    // Методы создания списков
    DoublyLinkedList CreateList();
    DoublyLinkedList CreateFromInput();
    DoublyLinkedList CreateRandom();
    DoublyLinkedList CreateFromFile(std::string filename);
};


#endif //LAB11_DOUBLLIST_H