//
// Created by macbook on 26.05.26.
//

#include "functions.h"
#include "functions.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>
#include <unordered_set>

// ===== КЛАСС CHECK: безопасный ввод =====

int Check::readInt(const char* text) {
    using namespace std;
    int x;
    while (true) {
        cout << text;
        if (cin >> x) return x;
        cout << "Ошибка ввода. Введите целое число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int Check::readIntMin(const char* text, int minValue) {
    using namespace std;
    while (true) {
        int x = readInt(text);
        if (x >= minValue) return x;
        cout << "Число должно быть >= " << minValue << ".\n";
    }
}

int Check::readIntRange(const char* text, int left, int right) {
    using namespace std;
    while (true) {
        int x = readInt(text);
        if (x >= left && x <= right) return x;
        cout << "Число должно быть в диапазоне [" << left << "; " << right << "].\n";
    }
}

// ===== КЛАСС NODE: узел дерева/списка =====

Node::Node(int value) : data(value), left(nullptr), right(nullptr) {}
int Node::getData() const { return data; }
Node* Node::getLeft() const { return left; }
Node* Node::getRight() const { return right; }
void Node::setData(int value) { data = value; }
void Node::setLeft(Node* p) { left = p; }
void Node::setRight(Node* p) { right = p; }

// ===== КЛАСС DoublyList (из примера, без изменений) =====

DoublyList::DoublyList() : head(nullptr), tail(nullptr) {}
DoublyList::~DoublyList() { clear(); }

void DoublyList::clear() {
    while (head) {
        Node* p = head;
        head = head->getRight();
        delete p;
    }
    tail = nullptr;
}

void DoublyList::pushBack(int value) {
    Node* p = new Node(value);
    if (!head) {
        head = p;
        tail = p;
        return;
    }
    tail->setRight(p);
    p->setLeft(tail);
    tail = p;
}

void DoublyList::insertSortedNode(Node* p) {
    p->setLeft(nullptr);
    p->setRight(nullptr);
    if (!head) {
        head = p;
        tail = p;
        return;
    }
    if (p->getData() <= head->getData()) {
        p->setRight(head);
        head->setLeft(p);
        head = p;
        return;
    }
    Node* cur = head;
    while (cur->getRight() && cur->getRight()->getData() < p->getData()) {
        cur = cur->getRight();
    }
    p->setRight(cur->getRight());
    p->setLeft(cur);
    if (cur->getRight()) {
        cur->getRight()->setLeft(p);
    }
    else {
        tail = p;
    }
    cur->setRight(p);
}

void DoublyList::sortAscending() {
    Node* oldHead = head;
    head = nullptr;
    tail = nullptr;
    while (oldHead) {
        Node* p = oldHead;
        oldHead = oldHead->getRight();
        insertSortedNode(p);
    }
}

bool DoublyList::fillKeyboard() {
    clear();
    int n = Check::readIntMin("Количество элементов списка: ", 1);
    for (int i = 0; i < n; ++i) {
        int x = Check::readInt("Введите число: ");
        pushBack(x);
    }
    return true;
}

bool DoublyList::fillFile() {
    using namespace std;
    clear();
    string fileName;
    cout << "Имя файла: ";
    cin >> fileName;
    ifstream fin(fileName);
    if (!fin.is_open()) return false;
    int n;
    if (!(fin >> n) || n < 1) return false;
    for (int i = 0; i < n; ++i) {
        int x;
        if (!(fin >> x)) return false;
        pushBack(x);
    }
    return true;
}

bool DoublyList::fillRandom() {
    using namespace std;
    clear();
    int n = Check::readIntMin("Количество элементов списка: ", 1);
    int left = Check::readInt("Левая граница: ");
    int right = Check::readInt("Правая граница: ");
    if (left > right) {
        int t = left;
        left = right;
        right = t;
    }
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned)time(nullptr));
        seeded = true;
    }

cout << "Сгенерировано: ";
    for (int i = 0; i < n; ++i) {
        int x = left + rand() % (right - left + 1);
        cout << x << ' ';
        pushBack(x);
    }
    cout << '\n';
    return true;
}

int DoublyList::count() const {
    int result = 0;
    Node* p = head;
    while (p) {
        ++result;
        p = p->getRight();
    }
    return result;
}

Node* DoublyList::buildBalanced(int countNodes) {
    if (countNodes <= 0) return nullptr;
    Node* leftRoot = buildBalanced(countNodes / 2);
    Node* root = head;
    head = head->getRight();
    root->setLeft(leftRoot);
    root->setRight(buildBalanced(countNodes - countNodes / 2 - 1));
    return root;
}

Node* DoublyList::toBalancedTree() {
    int n = count();
    Node* treeRoot = buildBalanced(n);
    head = nullptr;
    tail = nullptr;
    return treeRoot;
}

void DoublyList::print() const {
    using namespace std;
    cout << "list: ";
    Node* p = head;
    while (p) {
        cout << p->getData() << ' ';
        p = p->getRight();
    }
    cout << '\n';
}


BinaryTree::BinaryTree() : root(nullptr) {}
BinaryTree::~BinaryTree() { clear(); }

void BinaryTree::clear(Node* p) {
    if (!p) return;
    clear(p->getLeft());
    clear(p->getRight());
    delete p;
}

void BinaryTree::clear() {
    clear(root);
    root = nullptr;
}

void BinaryTree::setRoot(Node* p) {
    clear();
    root = p;
}

void BinaryTree::buildByLevels(const std::vector<int>& values) {
    clear();
    if (values.empty() || values[0] == -1) return;
    std::vector<Node*> nodes(values.size(), nullptr);
    nodes[0] = new Node(values[0]);
    for (size_t i = 1; i < values.size(); ++i) {
        size_t parentIndex = (i - 1) / 2;
        if (values[i] != -1 && nodes[parentIndex]) {
            nodes[i] = new Node(values[i]);
        }
    }
    for (size_t i = 0; i < values.size(); ++i) {
        if (!nodes[i]) continue;
        size_t leftIndex = 2 * i + 1;
        size_t rightIndex = 2 * i + 2;
        if (leftIndex < values.size()) nodes[i]->setLeft(nodes[leftIndex]);
        if (rightIndex < values.size()) nodes[i]->setRight(nodes[rightIndex]);
    }
    root = nodes[0];
}

bool BinaryTree::fillKeyboard() {
    using namespace std;
    cout << "Ввод дерева по уровням слева направо.\n";
    cout << "-1 означает пустую позицию.\n";
    int n = Check::readIntMin("Количество позиций: ", 1);
    vector<int> values;
    values.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x = Check::readInt("Введите значение: ");
        values.push_back(x);
    }
    buildByLevels(values);
    if (!root) {
        cout << "Дерево не должно быть пустым.\n";
        return false;
    }
    return true;
}

bool BinaryTree::fillFile() {
    using namespace std;
    string fileName;
    cout << "Имя файла: ";
    cin >> fileName;
    ifstream fin(fileName);
    if (!fin.is_open()) return false;
    int n;
    if (!(fin >> n) || n < 1) return false;
    vector<int> values;
    values.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x;
        if (!(fin >> x)) return false;
        values.push_back(x);
    }
    buildByLevels(values);
    return root != nullptr;
}

bool BinaryTree::fillRandom() {
    using namespace std;
    int n = Check::readIntMin("Количество позиций: ", 1);
    int left = Check::readInt("Левая граница: ");
    int right = Check::readInt("Правая граница: ");
    if (left > right) {
        int t = left;
        left = right;
        right = t;
    }
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned)time(nullptr));
        seeded = true;
    }
    vector<int> values;
    values.reserve(n);
    cout << "Сгенерировано: ";
    for (int i = 0; i < n; ++i) {
        int x = left + rand() % (right - left + 1);
        values.push_back(x);
        cout << x << ' ';
    }
    cout << '\n';
    buildByLevels(values);
    return true;
}

int


BinaryTree::height(Node* p) const {
    if (!p) return 0;
    int leftHeight = height(p->getLeft());
    int rightHeight = height(p->getRight());
    if (leftHeight > rightHeight) return leftHeight + 1;
    return rightHeight + 1;
}

static void printSpaces(int count) {
    using namespace std;
    for (int i = 0; i < count; ++i) cout << ' ';
}

void BinaryTree::print() const {
    using namespace std;
    if (!root) {
        cout << "Дерево пустое\n";
        return;
    }
    int h = height(root);
    queue<Node*> q;
    q.push(root);
    for (int level = 0; level < h; ++level) {
        int nodesCount = 1 << level;
        int firstSpaces = (1 << (h - level)) - 1;
        int betweenSpaces = (1 << (h - level + 1)) - 1;
        printSpaces(firstSpaces * 2);
        for (int i = 0; i < nodesCount; ++i) {
            Node* cur = q.front();
            q.pop();
            if (cur) {
                cout << setw(3) << cur->getData();
                q.push(cur->getLeft());
                q.push(cur->getRight());
            }
            else {
                cout << "   ";
                q.push(nullptr);
                q.push(nullptr);
            }
            printSpaces(betweenSpaces * 2);
        }
        cout << "\n\n";
    }
}

// ===== ИТЕРАТОР (TreeFun6) =====

BinaryTree::Iterator::Iterator(Node* root) {
    if (root) stack.push_back(root);
}

bool BinaryTree::Iterator::hasNext() const {
    return !stack.empty();
}

int BinaryTree::Iterator::next() {
    Node* p = stack.back();
    stack.pop_back();
    if (p->getLeft()) stack.push_back(p->getLeft());
    if (p->getRight()) stack.push_back(p->getRight());
    return p->getData();
}

BinaryTree::Iterator BinaryTree::iteratorRootRightLeft() const {
    return Iterator(root);
}

// ===== TREEFUN10: КАМЕРЫ И ПЕРЕКРЫТИЯ =====

int BinaryTree::placeCamerasGreedy(Node* p, std::unordered_set<Node*>& camSet) const {
    if (!p) return 2; // 2 = покрыт ребенком
    int left = placeCamerasGreedy(p->getLeft(), camSet);
    int right = placeCamerasGreedy(p->getRight(), camSet);
    if (left == 0 || right == 0) {
        camSet.insert(const_cast<Node*>(p)); // 1 = ставим камеру
        std::cout<<p->getData()<<"\n";
        return 1;
    }
    if (left == 1 || right == 1) return 2; // Покрыт ребенком с камерой
    return 0; // 0 = не покрыт
}

int BinaryTree::countOverlaps(Node* p, Node* parent, const std::unordered_set<Node*>& camSet) const {
    if (!p) return 0;
    int coverage = 0;
    if (camSet.count(p)) coverage++;
    if (parent && camSet.count(parent)) coverage++;
    if (p->getLeft() && camSet.count(p->getLeft())) coverage++;
    if (p->getRight() && camSet.count(p->getRight())) coverage++;
    int overlaps = (coverage > 1) ? 1 : 0;
    return overlaps + countOverlaps(p->getLeft(), p, camSet) + countOverlaps(p->getRight(), p, camSet);
}

int BinaryTree::countNodesWithMultipleCoverage() const {
    std::unordered_set<Node*> camSet;
    int rootState = placeCamerasGreedy(const_cast<Node*>(root), camSet);

    if (rootState == 0) camSet.insert(const_cast<Node*>(root));

    return countOverlaps(root, nullptr, camSet);
}

// ===== ЗАПУСК ЗАДАНИЙ =====

// ЗАДАНИЕ 1: TREEFUN2 - СПИСОК В ДЕРЕВО
void TreeFun2() {
    using namespace std;
    DoublyList list;
    cout << "\nTREEFUN2: СПИСОК В СБАЛАНСИРОВАННОЕ ДЕРЕВО \n";
    int mode = Check::readIntRange("Заполнение списка: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);
    bool ok = false;
    if (mode == 1) ok = list.fillKeyboard();
    else if (mode == 2) ok = list.fillFile();
    else ok = list.fillRandom();
    if (!ok) { cout << "Ошибка заполнения.\n"; return; }

    cout << "\nИсходный список:\n";
    list.print();

    list.sortAscending();
    cout << "Список по возрастанию:\n";
    list.print();

    cout << "\nПолучившееся дерево поиска:\n";

    DoublyList::printTreed( list.toBalancedTree(),0);

}

void DoublyList::printTreed(Node* root, int indent) {
    if (root != nullptr) {
        if (root->getRight()) printTreed(root->getRight(), indent + 4);
        if (indent) std::cout << std::string(indent, ' ');
        std::cout << root->getData() << "\n";
        if (root->getLeft()) printTreed(root->getLeft(), indent + 4);
    }
}
// ЗАДАНИЕ 2: TREEFUN6 - ИТЕРАТОР КОРЕПЬ-ПРАВО-ЛЕВО
void TreeFun6() {


using namespace std;
    BinaryTree tree;
    cout << "\nTREEFUN6: ИТЕРАТОР КОРЕПЬ-ПРАВО-ЛЕВО \n";
    int mode = Check::readIntRange("Заполнение дерева: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);
    bool ok = false;
    if (mode == 1) ok = tree.fillKeyboard();
    else if (mode == 2) ok = tree.fillFile();
    else ok = tree.fillRandom();
    if (!ok) { cout << "Ошибка заполнения.\n"; return; }

    cout << "\nДерево:\n";
    tree.print();

    cout << "Обход корень-право-лево: ";
    BinaryTree::Iterator it = tree.iteratorRootRightLeft();
    while (it.hasNext()) {
        cout << it.next() << ' ';
    }
    cout << '\n';

}


void TreeFun10() {
    using namespace std;
    BinaryTree tree;
    cout << "\n TREEFUN10: УЗЛЫ С ПЕРЕКРЫТИЕМ КАМЕР \n";
    int mode = Check::readIntRange("Заполнение дерева: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);
    bool ok = false;
    if (mode == 1) ok = tree.fillKeyboard();
    else if (mode == 2) ok = tree.fillFile();
    else ok = tree.fillRandom();
    if (!ok) { cout << "Ошибка заполнения.\n"; return; }

    cout << "\nИсходное дерево:\n";
    tree.print();

    int overlaps = tree.countNodesWithMultipleCoverage();
    cout << "Узлов, покрытых более чем одной камерой: " << overlaps << '\n';

}



#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#endif





