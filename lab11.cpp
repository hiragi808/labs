//
// Created by macbook on 09.03.26.
//

#include "lab11.h"
#include "Node.h"
#include "CircleList.h"
#include "DoublList.h"
#include <iostream>
#include <fstream>
#include "cirbar.h"
void t1() {
    std::cout << "Кольцевой список с выводом в файл с шагом 2" << std::endl;

    CircularLinkedList list = list.CreateCList();
    std::cout << "Созданный список:" << std::endl;
    list.Print();
    std::cout << "Указатель на первый элемент (P1): " << list.GetHead() << std::endl;
    std::string filename = "lab11_1.txt";
    if (list.IsEmpty()) {
        std::cout << "Список пуст, нечего обрабатывать" << std::endl;
        return;
    }

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << " для записи" << std::endl;
        return;
    }
    std::cout << "Обработка списка с шагом 2" << std::endl;
    std::cout << "Исходный список: ";
    list.Print();

    Node* current = list.GetHead();

    while (!list.IsEmpty()) {
        // Записываем текущий элемент в файл
        outFile << current->getData() << " ";
        std::cout << "Записан в файл: " << current->getData() << std::endl;

        Node* nextNode = list.RemoveNode(current);
        if (!list.IsEmpty()) {
            current = nextNode;
            current = current->getNext();
        }
    }
    outFile.close();
    std::cout << "Результат сохранен в файл: " << filename << std::endl;
    std::cout << "Проверка: список после обработки:" << std::endl;
    list.Print();
}
void FindMinMax(Node* start, Node*& minNode, Node*& maxNode) {
    if (start == nullptr) {
        minNode = maxNode = nullptr;
        return;
    }

    minNode = maxNode = start;
    Node* current = start->getNext();

    while (current != nullptr) {
        if (current->getData() < minNode->getData()) {
            minNode = current;
        }
        if (current->getData() > maxNode->getData()) {
            maxNode = current;
        }
        current = current->getNext();
    }

    std::cout << "Минимальный элемент: " << minNode->getData() << std::endl;
    std::cout << "Максимальный элемент: " << maxNode->getData() << std::endl;
}

void PrintBetweenMinMax(Node* head) {
    if (head == nullptr) {
        std::cout << "Список пуст" << std::endl;
        return;
    }

    // Находим минимальный и максимальный элементы
    Node* minNode = nullptr;
    Node* maxNode = nullptr;
    FindMinMax(head, minNode, maxNode);

    if (minNode == maxNode) {
        std::cout << "Минимальный и максимальный элементы совпадают. Между ними нет элементов." << std::endl;
        return;
    }

    // Определяем, какой из них встречается раньше в списке
    Node* first = nullptr;
    Node* second = nullptr;

    // Проходим по списку, чтобы найти порядок
    Node* current = head;
    while (current != nullptr) {
        if (current == minNode) {
            first = minNode;
            second = maxNode;
            break;
        }
        if (current == maxNode) {
            first = maxNode;
            second = minNode;
            break;
        }
        current = current->getNext();
    }

    std::cout << "Элементы между " << first->getData() << " и " << second->getData() << ": ";

    current = first->getNext();
    bool found = false;

    while (current != nullptr && current != second) {
        std::cout << current->getData() << " ";
        current = current->getNext();
        found = true;
    }

    if (!found) {
        std::cout << "нет элементов"<<std::endl;
    }
    std::cout <<std::endl;
}
void t2() {

    // Создаем список
    DoublyLinkedList list = list.CreateList();
    // Получаем указатель на первый элемент P1
    Node* P1 = list.GetHead();

    std::cout << "Исходный список:" << std::endl;
    list.Print();
    std::cout << "Указатель на первый элемент P1 = " << P1 << std::endl;
    std::cout << "Результат:" << std::endl;
    PrintBetweenMinMax(P1);

}
void t3() {
    DoublyLinkedList list=list.CreateList();

    Node* P1 = list.GetHead();
    Node* Tail = list.GetTail();

    std::cout << "Созданный список:" << std::endl;
    list.Print();
    std::cout << "Указатель на первый элемент P1 = " << P1 << std::endl;
    std::cout << "Указатель на последний элемент = " << Tail << std::endl;

    // Проверка на пустой список
    if (P1 == nullptr) {
        std::cout << "Список пуст" << std::endl;
        return;
    }

    std::string filename = "lab11_3.txt";
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << " для записи" << std::endl;
        return;
    }

    std::cout << "Вывод списка в обратном порядке с удалением " << std::endl;
    std::cout << std::endl;
    Node* current = Tail;
    bool first = true;

    while (current != nullptr) {
        // Запоминаем предыдущий элемент (тот, что слева)
        Node* prev = current->getPrev();

        // Записываем в файл (без пробела в конце)
        if (!first) {
            outFile << " ";
        }
        outFile << current->getData();
        first = false;

        std::cout << "Записан в файл и удаляется: " << current->getData() << std::endl;

        delete current;
        current = prev;
    }
    outFile.close();
    std::cout << "Все элементы удалены. Результат сохранен в файл: " << filename << std::endl;
    
}
void t5() {

    // Создаем список
    DoublyLinkedList list = list.CreateList();
    // Получаем указатель на первый элемент P1
    Node* P1 = list.GetHead();
    std::cout <<std::endl;
    std::cout << "Исходный список:" << std::endl;
    list.Print();
    std::cout << "Указатель на первый элемент P1 = " << P1 << std::endl;
    std::cout << "Результат:" << std::endl;
    PrintBetweenMinMax2(P1);
}
void PrintBetweenMinMax2(Node* head) {
    if (head == nullptr) {
        std::cout << "Список пуст" << std::endl;
        return;
    }

    // Находим минимальный и максимальный элементы
    Node* minNode = nullptr;
    Node* maxNode = nullptr;
    FindMinMax(head, minNode, maxNode);

    if (minNode == maxNode) {
        std::cout << "Минимальный и максимальный элементы совпадают. Между ними нет элементов." << std::endl;
        return;
    }

    // Определяем, какой из них встречается раньше в списке
    Node* first = nullptr;
    Node* second = nullptr;

    // Проходим по списку, чтобы найти порядок
    Node* current = head;
    while (current != nullptr) {
        if (current == minNode) {
            first = minNode;
            second = maxNode;
            break;
        }
        if (current == maxNode) {
            first = maxNode;
            second = minNode;
            break;
        }
        current = current->getNext();
    }

    std::cout << "Элементы между " << first->getData() << " и " << second->getData() << ": ";

    current = second->getPrev();
    bool found = false;

    while (current != nullptr && current != first) {
        std::cout << current->getData() << " ";
        current = current->getPrev();
        found = true;
    }

    if (!found) {
        std::cout << "нет элементов"<<std::endl;
    }
    std::cout <<std::endl;
}

void t4() {
    DoublyLinkedList list = list.CreateList();
    list.Print();

    // Используем статический метод
    cirbar t = cirbar::CreateFromDoubly(list.GetHead(), list.GetTail());

    t.PrintCircularList();
}