//
// Created by macbook on 09.03.26.
//
#include <iostream>
#include <fstream>
#include "DoublList.h"

// Конструкторы и деструктор
DoublyLinkedList::DoublyLinkedList() : Head(nullptr), Tail(nullptr) {
    std::cout << "Создан пустой двусвязный список" << std::endl;
}

DoublyLinkedList::DoublyLinkedList(DoublyLinkedList& other) : Head(nullptr), Tail(nullptr) {
    std::cout << "Конструктор копирования двусвязного списка" << std::endl;
    Node* current = other.Head;
    while (current != nullptr) {
        PushBack(current->getData());
        current = current->getNext();
    }
}

DoublyLinkedList::~DoublyLinkedList() {
    std::cout << "Деструктор списка: ";
    int count = 0;
    if (Head != nullptr) {
        Node *Top = Head;
        while (Top != nullptr) {
            Node* temp = Top;
            Top = Top->getNext();
            delete temp;
            count++;
        }
        std::cout << "удалено " << count << " элементов" << std::endl;
    }
}

// Геттеры
Node* DoublyLinkedList::GetHead() {
    return Head;
}

Node* DoublyLinkedList::GetTail() {
    return Tail;
}

int DoublyLinkedList::GetSize() {
    int size = 0;
    Node* current = Head;
    while (current != nullptr) {
        size++;
        current = current->getNext();
    }
    return size;
}

// Проверка на пустоту
bool DoublyLinkedList::IsEmpty() {
    return Head == nullptr;
}

// Добавление элементов
void DoublyLinkedList::PushBack(int value) {
    Node* newNode = new Node(value);

    if (IsEmpty()) {
        Head = Tail = newNode;
    } else {
        Tail->setNext(newNode);
        newNode->setPrev(Tail);
        Tail = newNode;
    }
    std::cout << "  Добавлен " << value << " в конец (адрес: " << newNode << ")" << std::endl;
}

void DoublyLinkedList::PushFront(int value) {
    Node* newNode = new Node(value);

    if (IsEmpty()) {
        Head = Tail = newNode;
    } else {
        newNode->setNext(Head);
        Head->setPrev(newNode);
        Head = newNode;
    }
    std::cout << "  Добавлен " << value << " в начало (адрес: " << newNode << ")" << std::endl;
}

void DoublyLinkedList::Insert(int value, int position) {
    if (position < 0) {
        std::cout << "  Ошибка: позиция не может быть отрицательной" << std::endl;
        return;
    }

    if (position == 0) {
        PushFront(value);
        return;
    }

    int size = GetSize();
    if (position > size) {
        std::cout << "  Ошибка: позиция выходит за пределы списка" << std::endl;
        return;
    }

    if (position == size) {
        PushBack(value);
        return;
    }

    Node* current;

    // Выбираем, с какой стороны быстрее дойти
    if (position < size / 2) {
        // Идем с начала
        current = Head;
        for (int i = 0; i < position - 1; i++) {
            current = current->getNext();
        }
    } else {
        // Идем с конца
        current = Tail;
        for (int i = size - 1; i > position; i--) {
            current = current->getPrev();
        }
        current = current->getPrev();
    }

    Node* newNode = new Node(value);
    newNode->setNext(current->getNext());
    newNode->setPrev(current);

    if (current->getNext() != nullptr) {
        current->getNext()->setPrev(newNode);
    }
    current->setNext(newNode);

    if (newNode->getNext() == nullptr) {
        Tail = newNode;
    }

    std::cout << "  Добавлен " << value << " на позицию " << position
              << " (адрес: " << newNode << ")" << std::endl;
}

void DoublyLinkedList::InsertSorted(int value) {
    Node* newNode = new Node(value);

    // Если список пуст
    if (Head == nullptr) {
        Head = Tail = newNode;
        std::cout << "  Вставлен " << value << " в пустой список" << std::endl;
        return;
    }

    // Вставка в начало (если value меньше первого)
    if (value < Head->getData()) {
        newNode->setNext(Head);
        Head->setPrev(newNode);
        Head = newNode;
        std::cout << "  Вставлен " << value << " в начало списка" << std::endl;
        return;
    }

    // Вставка в конец (если value больше последнего)
    if (value > Tail->getData()) {
        Tail->setNext(newNode);
        newNode->setPrev(Tail);
        Tail = newNode;
        std::cout << "  Вставлен " << value << " в конец списка" << std::endl;
        return;
    }

    // Поиск позиции для вставки
    Node* current = Head;
    while (current->getNext() != nullptr && current->getNext()->getData() < value) {
        current = current->getNext();
    }

    // Вставка после current
    newNode->setNext(current->getNext());
    newNode->setPrev(current);

    if (current->getNext() != nullptr) {
        current->getNext()->setPrev(newNode);
    }
    current->setNext(newNode);

    std::cout << "  Вставлен " << value << " в упорядоченный список" << std::endl;
}
//
// Node* DoublyLinkedList::Find(int value) {
//     Node* current = Head;
//     int position = 0;
//
//     while (current != nullptr) {
//         if (current->getData() == value) {
//             std::cout << "  Найден элемент " << value << " в списке на позиции " << position
//                       << " по адресу " << current << std::endl;
//             return current;
//         }
//         current = current->getNext();
//         position++;
//     }
//
//     std::cout << "  Элемент " << value << " не найден в списке" << std::endl;
//     return nullptr;
// }

// Удаление элементов
int DoublyLinkedList::RemoveFirst() {
    if (IsEmpty()) {
        std::cout << "  Список пуст, невозможно удалить первый элемент" << std::endl;
        return -1;
    }

    Node* temp = Head;
    int value = temp->getData();

    Head = Head->getNext();
    if (Head != nullptr) {
        Head->setPrev(nullptr);
    } else {
        Tail = nullptr;
    }

    std::cout << "  Удален первый элемент " << value << " (адрес: " << temp << ")" << std::endl;
    delete temp;
    return value;
}




// Очистка списка
void DoublyLinkedList::Clear() {
    int count = 0;
    while (!IsEmpty()) {
        RemoveFirst();
        count++;
    }
    std::cout << "удалено " << count << " элементов" << std::endl;
}

// Вывод списка
void DoublyLinkedList::Print() {
    if (IsEmpty()) {
        std::cout << "Список пуст" << std::endl;
        return;
    }

    std::cout << "Двусвязный список: ";
    Node* current = Head;
    while (current != nullptr) {
        std::cout << current->getData() << " ";
        current = current->getNext();
    }
    std::cout << std::endl;
}
// Проверка упорядоченности
bool DoublyLinkedList::IsSorted() {
    if (Head == nullptr || Head->getNext() == nullptr) {
        std::cout << "Список пуст или содержит один элемент - считается упорядоченным" << std::endl;
        return true;
    }

    Node* current = Head;
    while (current->getNext() != nullptr) {
        if (current->getData() > current->getNext()->getData()) {
            std::cout << "Список НЕ упорядочен: " << current->getData()
                      << " > " << current->getNext()->getData() << std::endl;
            return false;
        }
        current = current->getNext();
    }

    std::cout << "Список упорядочен по возрастанию" << std::endl;
    return true;
}

// Методы создания списков
DoublyLinkedList DoublyLinkedList::CreateFromInput() {
    DoublyLinkedList list;
    int N;

    std::cout << "Введите количество элементов: ";
    std::cin >> N;
    std::cout << "Введите " << N << " различных чисел: ";

    for (int i = 0; i < N; i++) {
        int value;
        bool validInput = false;

        while (!validInput) {
            if (!(std::cin >> value)) {
                std::cout << "Ошибка! Введите целое число: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            // Проверяем уникальность
            if (list.FindD(value) != nullptr) {
                std::cout << "Ошибка! Число " << value << " уже есть в списке. Введите другое: ";
            } else {
                validInput = true;
            }
        }

        list.PushBack(value);
    }

    std::cout << "Список успешно создан! Все элементы уникальны." << std::endl;
    return list;
}
DoublyLinkedList DoublyLinkedList::CreateRandom() {
    DoublyLinkedList list;
    int size, minValue = 0, maxValue = 100;
    std::cout << "Введите размер: ";
    std::cin >> size;
    srand(time(nullptr));

    std::cout << "Генерация " << size << " случайных чисел от "
              << minValue << " до " << maxValue << std::endl;

    for (int i = 0; i < size; i++) {
        bool validInput = false;
        int value;
        while (!validInput) {
            value = minValue + rand() % (maxValue - minValue + 1);
            // Проверяем уникальность
            if (list.FindD(value) != nullptr) {
            } else {
                validInput = true;
            }
        }
        list.PushBack(value);
    }

    return list;
}

DoublyLinkedList DoublyLinkedList::CreateFromFile(std::string filename) {
    DoublyLinkedList list;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return list;
    }

    int value;
    while (file >> value) {
        list.PushBack(value);
        std::cout << "Ошибка элементы повторяются";
    }
    if (!list.AllUnique()) {
        return DoublyLinkedList();
    }
    file.close();
    std::cout << "Список заполнен из файла. ";
    return list;
}

DoublyLinkedList DoublyLinkedList::CreateList() {
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
            return DoublyLinkedList();
    }
}
Node* DoublyLinkedList::FindD(int value) {
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
bool DoublyLinkedList::AllUnique() {
    if (Head == nullptr || Head->getNext() == nullptr) {
        std::cout << "Список пуст или содержит один элемент - все элементы уникальны" << std::endl;
        return true;
    }

    // Создаем вектор и копируем в него все значения
    std::vector<int> values;
    Node* current = Head;

    while (current != nullptr) {
        values.push_back(current->getData());
        current = current->getNext();
    }

    // Сортируем вектор
    std::sort(values.begin(), values.end());

    // Проверяем соседние элементы на равенство
    bool hasDuplicates = false;
    for (size_t i = 0; i < values.size() - 1; i++) {
        if (values[i] == values[i + 1]) {
            std::cout << "Найдены дубликаты повторите ввод"  << std::endl;
            hasDuplicates = true;
            break;
        }
    }

    if (!hasDuplicates) {
        std::cout << "Все элементы списка уникальны" << std::endl;
        return true;
    } else {
        return false;
    }
}
