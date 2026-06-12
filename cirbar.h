//
// Created by macbook on 12.03.26.
//

#ifndef LAB11_CIRBAR_H
#define LAB11_CIRBAR_H

#include "cirbar.h"
#include <string>
#include "Node.h"
class cirbar {
private:
    Node* Head;
    Node* Tail;
    Node* barrier;
public:
    cirbar();
    cirbar(cirbar& other);
    ~cirbar();
    bool NEmpty();
    void PushBack(int value);
    void setHead(Node* P1);
    void setTail(Node* P1);
    void setBarrier(Node* barr);
    Node* GetHead();
    Node* GetTail();
    Node* Getbarrier();
    int GetSize();
    Node* FindD(int value);

    // Методы создания списков
    void PrintCircularList();
    static cirbar CreateFromDoubly(Node* P1, Node* P2);  // Сделали статическим
};

#endif //LAB11_CIRBAR_H