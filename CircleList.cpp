//
// Created by macbook on 09.03.26.
//

#include "CircleList.h"
#include <iostream>
#include <fstream>
#include <ctime>

// Конструкторы и деструктор
CircularLinkedList::CircularLinkedList() : Head(nullptr), Tail(nullptr) {
    std::cout << "Создан пустой кольцевой список" << std::endl;
}

CircularLinkedList::CircularLinkedList(CircularLinkedList& other) : Head(nullptr), Tail(nullptr) {
    std::cout << "Конструктор копирования кольцевого списка" << std::endl;

    if (other.Head == nullptr) return;

    Node* current = other.Head;
    do {
        PushBack(current->getData());
        current = current->getNext();
    } while (current != other.Head);
}

CircularLinkedList::~CircularLinkedList() {
    std::cout << "Деструктор кольцевого списка: ";
    Clear();
}

// Геттеры
Node* CircularLinkedList::GetHead() {
    return Head;
}

Node* CircularLinkedList::GetTail() {
    return Tail;
}


// Проверка на пустоту
bool CircularLinkedList::IsEmpty() {
    return Head == nullptr;
}

// Добавление элементов
void CircularLinkedList::PushBack(int value) {
    Node* newNode = new Node(value);

    if (IsEmpty()) {
        Head = Tail = newNode;
        Tail->setNext(Head);  // Замыкаем в кольцо
    } else {
        Tail->setNext(newNode);
        Tail = newNode;
        Tail->setNext(Head);  // Замыкаем в кольцо
    }
    std::cout << "  Добавлен " << value << " в конец (адрес: " << newNode << ")" << std::endl;
}

void CircularLinkedList::PushFront(int value) {
    Node* newNode = new Node(value);

    if (IsEmpty()) {
        Head = Tail = newNode;
        Tail->setNext(Head);  // Замыкаем в кольцо
    } else {
        newNode->setNext(Head);
        Head = newNode;
        Tail->setNext(Head);  // Обновляем замыкание
    }
    std::cout << "  Добавлен " << value << " в начало (адрес: " << newNode << ")" << std::endl;
}

// Удаление узла
Node* CircularLinkedList::RemoveNode(Node* nodeToRemove) {
    if (IsEmpty() || nodeToRemove == nullptr) return nullptr;

    Node* result = nullptr;

    // Если это единственный элемент
    if (Head == Tail && Head == nodeToRemove) {
        delete Head;
        Head = Tail = nullptr;
        return nullptr;
    }

    // Ищем предыдущий элемент
    Node* prev = Head;
    while (prev->getNext() != nodeToRemove) {
        prev = prev->getNext();
    }

    // Если удаляем голову
    if (nodeToRemove == Head) {
        Head = Head->getNext();
        Tail->setNext(Head);
        result = Head;
    }
    // Если удаляем хвост
    else if (nodeToRemove == Tail) {
        Tail = prev;
        Tail->setNext(Head);
        result = Head;
    }
    // Если удаляем средний элемент
    else {
        prev->setNext(nodeToRemove->getNext());
        result = prev->getNext();
    }

    int value = nodeToRemove->getData();
    delete nodeToRemove;
    std::cout << "  Удален элемент " << value << std::endl;

    return result;
}

// Очистка списка
void CircularLinkedList::Clear() {
    if (IsEmpty()) {
        std::cout << "список уже пуст" << std::endl;
        return;
    }

    int count = 0;
    Node* current = Head;

    // Размыкаем кольцо для обычного удаления
    Tail->setNext(nullptr);

    while (current != nullptr) {
        Node* next = current->getNext();
        delete current;
        current = next;
        count++;
    }

    Head = Tail = nullptr;
    std::cout << "удалено " << count << " элементов" << std::endl;
}

// Вывод списка
void CircularLinkedList::Print() {
    if (IsEmpty()) {
        std::cout << "Кольцевой список пуст" << std::endl;
        return;
    }

    std::cout << "Кольцевой список: ";
    Node* current = Head;
    do {
        std::cout << current->getData() << " ";
        current = current->getNext();
    } while (current != Head);
    std::cout << " (замыкается на " << Head->getData() << ")" << std::endl;
}

// Методы создания списков
CircularLinkedList CircularLinkedList::CreateFromInput() {
    CircularLinkedList list;
    int N;
    std::cout << "Введите количество элементов: ";
    std::cin >> N;
    std::cout << "Введите " << N << " чисел: ";
    for (int i = 0; i < N; i++) {
        int value;
        if (!(std::cin >> value)) {
            std::cout << "Ошибка! Введите целое число: ";
            while (!(std::cin >> value)) {
                std::cin.clear(); // Сбрасываем флаг ошибки
                std::cin.ignore(10000, '\n');
            }
        }
        list.PushBack(value);
    }
    return list;
}

CircularLinkedList CircularLinkedList::CreateRandom() {
    CircularLinkedList list;
    int size, minValue = 0, maxValue = 100;
    std::cout << "Введите размер: ";
    std::cin >> size;
    srand(time(nullptr));

    std::cout << "Генерация " << size << " случайных чисел от "
              << minValue << " до " << maxValue << std::endl;

    for (int i = 0; i < size; i++) {
        int value = minValue + rand() % (maxValue - minValue + 1);
        list.PushBack(value);
    }

    return list;
}

CircularLinkedList CircularLinkedList::CreateFromFile(std::string filename) {
    CircularLinkedList list;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return list;
    }

    int value;
    while (file >> value) {
        list.PushBack(value);
    }

    file.close();
    std::cout << "Список заполнен из файла. ";
    return list;
}

CircularLinkedList CircularLinkedList::CreateCList() {
    std::cout << "Выберите способ заполнения списка:\n"
              << "1 - С клавиатуры\n"
              << "2 - Из файла\n"
              << "3 - Случайными числами\n"
              << "Ваш выбор: ";

    int choice;
    std::cin >> choice;

    switch(choice) {
        case 1:
            return CreateFromInput();
        case 2: {
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;
            return CreateFromFile(filename);
        }
        case 3:
            return CreateRandom();
        default:
            std::cout << "Неверный выбор. Создан пустой список.\n";
            return CircularLinkedList();
    }
}
Node* CircularLinkedList::FindQ(int value) {
    Node* current = Head;
    int position = 0;

    while (current != nullptr) {
        if (current->getData() == value) {
            std::cout << "  Найден элемент " << value << " в списке на позиции " << position
                      << " по адресу " << current << std::endl;
            return current;
        }
        current = current->getNext();
        position++;
    }

    std::cout << "  Элемент " << value << " не найден в списке" << std::endl;
    return nullptr;
}