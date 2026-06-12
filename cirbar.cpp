//
// Created by macbook on 12.03.26.
//

#include "cirbar.h"
#include <iostream>
#include "Node.h"

// РЕАЛИЗАЦИЯ КОНСТРУКТОРА
cirbar::cirbar() : Head(nullptr), Tail(nullptr), barrier(nullptr) {
    std::cout << "Создан пустой циклический список с барьером" << std::endl;
}

cirbar::~cirbar() {
    std::cout << "Деструктор циклического списка: ";
    int count = 0;

    if (barrier != nullptr) {
        // Удаляем все элементы, кроме барьера
        if (barrier->getNext() != barrier) {
            Node* current = barrier->getNext();
            while (current != barrier) {
                Node* temp = current;
                current = current->getNext();
                delete temp;
                count++;
            }
        }

        delete barrier;
        count++;
        std::cout << "удалено " << count << " элементов (включая барьер)" << std::endl;
    } else {
        std::cout << "нет элементов" << std::endl;
    }
}

void cirbar::setHead(Node* P1) {
    Head = P1;
}

void cirbar::setTail(Node* P1) {
    Tail = P1;
}

void cirbar::setBarrier(Node* barr) {
    barrier = barr;
}

cirbar::cirbar(cirbar& other) : Head(nullptr), Tail(nullptr), barrier(nullptr) {
    std::cout << "Конструктор копирования циклического списка" << std::endl;

    if (other.barrier != nullptr) {
        barrier = new Node(0);

        Node* current = other.barrier->getNext();
        while (current != other.barrier) {
            PushBack(current->getData());
            current = current->getNext();
        }

        if (Head != nullptr) {
            barrier->setNext(Head);
            barrier->setPrev(Tail);
            Head->setPrev(barrier);
            Tail->setNext(barrier);
        } else {
            barrier->setNext(barrier);
            barrier->setPrev(barrier);
        }
    }
}


bool cirbar::NEmpty() {
    return Head == nullptr;
}


void cirbar::PushBack(int value) {
    Node* newNode = new Node(value);

    if (NEmpty()) {
        Head = Tail = newNode;
        if (barrier) {
            barrier->setNext(newNode);
            barrier->setPrev(newNode);
            newNode->setPrev(barrier);
            newNode->setNext(barrier);
        }
    } else {
        Tail->setNext(newNode);
        newNode->setPrev(Tail);
        Tail = newNode;
        if (barrier) {
            barrier->setPrev(Tail);
            Tail->setNext(barrier);
        }
    }
    std::cout << "  Добавлен " << value << " в конец (адрес: " << newNode << ")" << std::endl;
}

Node* cirbar::Getbarrier() {
    return barrier;
}


Node* cirbar::GetHead() {
    return Head;
}


Node* cirbar::GetTail() {
    return Tail;
}


void cirbar::PrintCircularList() {
    if (barrier == nullptr) {
        std::cout << "Барьерный элемент не существует" << std::endl;
        return;
    }

    std::cout << "Циклический список с барьером" << std::endl;
    std::cout << "Барьерный элемент (0) по адресу: " << barrier << std::endl;
    std::cout << "  barrier->next = " << barrier->getNext() << std::endl;
    std::cout << "  barrier->prev = " << barrier->getPrev() << std::endl;

    if (barrier->getNext() == barrier && barrier->getPrev() == barrier) {
        std::cout << "Список пуст. Барьер указывает сам на себя." << std::endl;
        return;
    }

    std::cout << "Элементы списка:" << std::endl;
    Node* current = barrier->getNext();
    while (current != barrier) {
        std::cout << current->getData() << " (адрес: " << current << ")" << std::endl;
        current = current->getNext();
    }
}

cirbar cirbar::CreateFromDoubly(Node* head, Node* tail) {
    cirbar result;

    // Создаем барьерный элемент
    Node* barr = new Node(0);
    result.setBarrier(barr);

    if (head == nullptr || tail == nullptr) {
        // Пустой список
        barr->setNext(barr);
        barr->setPrev(barr);
        result.setHead(nullptr);
        result.setTail(nullptr);
        std::cout << "Список пуст" << std::endl;
    } else {

        result.setHead(head);
        result.setTail(tail);

        barr->setNext(head);
        barr->setPrev(tail);

        head->setPrev(barr);


        tail->setNext(barr);

        std::cout << "Создан циклический список:" << std::endl;
        std::cout << "  barrier->next = " << head << " (первый элемент: " << head->getData() << ")" << std::endl;
        std::cout << "  barrier->prev = " << tail << " (последний элемент: " << tail->getData() << ")" << std::endl;
    }

    return result;
}
int cirbar::GetSize() {
    if (barrier == nullptr || barrier->getNext() == barrier) {
        return 0;  // Список пуст
    }

    int count = 0;
    Node* current = barrier->getNext();

    while (current != barrier) {
        count++;
        current = current->getNext();
    }

    return count;
}
Node* cirbar::FindD(int value) {
    if (barrier == nullptr || barrier->getNext() == barrier) {
        std::cout << "Список пуст, элемент " << value << " не найден" << std::endl;
        return nullptr;  // Список пуст
    }

    Node* current = barrier->getNext();

    while (current != barrier) {
        if (current->getData() == value) {
            std::cout << "Элемент " << value << " найден по адресу: " << current << std::endl;
            return current;
        }
        current = current->getNext();
    }

    std::cout << "Элемент " << value << " не найден в списке" << std::endl;
    return nullptr;
}