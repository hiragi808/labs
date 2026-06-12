#include "tree.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// Отдельный вспомогательный инструментарий для ввода
int getInt() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ошибка! Введите целое число: ";
    }
    return value;
}

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void Tree::AddToTree(PNode& node, int val) {
    if (!node) {
        node = new Node(val);
        return;
    }
    if (val < node->data)
        AddToTree(node->left, val);
    else
        AddToTree(node->right, val);
}
void Tree::AddToTreed(PNode& node, int val) {
    if (!node) {
        node = new Node(val);
        return;
    }
    if (node->left==nullptr)
        AddToTree(node->left, val);
    else
        AddToTree(node->right, val);
}
PNode Tree::fillV() {
    vector<int> v;
    int size, choice;

    cout << "Выберите способ заполнения дерева:\n1 - Клавиатура, 2 - Файл, 3 - Случайные числа: ";
    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cout << "Ошибка! Введите 1, 2 или 3: ";
        clearInput();
    }

    cout << "Введите количество элементов: ";
    while (!(cin >> size) || size <= 0) {
        cout << "Ошибка! Введите положительное число: ";
        clearInput();
    }

    v.resize(size);

    if (choice == 1) {
        for (int i = 0; i < size; ++i) {
            cout << "Элемент " << i + 1 << ": ";
            v[i] = getInt();
        }
    } else if (choice == 2) {
        string filename;
        cout << "Введите имя файла: ";
        cin >> filename;
        ifstream in(filename);
        if (!in) {
            cout << "Файл не найден, заполняю нулями.\n";
        } else {
            for (int i = 0; i < size && in >> v[i]; ++i);
        }
    } else {
        srand(time(0));
        for (int i = 0; i < size; ++i) v[i] = rand() % 100;
    }

    PNode root = nullptr;
    for (int x : v) AddToTreed(root, x);
    return root;
}

void Tree::Print(PNode node) {
    if (!node) return;
    Print(node->left);
    Print(node->right);
    cout << node->data << " ";
}

// void Tree::printVisual(PNode node, int space) {
//     if (!node) return;
//     space += 5;
//     printVisual(node->right, space);
//     cout << endl;
//     for (int i = 5; i < space; i++) cout << " ";
//     cout << node->data << "\n";
//     printVisual(node->left, space);
// }

void Tree::clear(PNode node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>

// Вспомогательная функция для определения высоты дерева
int getHeight(PNode node) {
    if (!node) return 0;
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

void Tree::printVertical(PNode root) {
    if (!root) {
        std::cout << "Дерево пусто." << std::endl;
        return;
    }

    int h = getHeight(root);
    // Рассчитываем ширину поля (минимум 4 символа на узел [XX])
    int width = pow(2, h) * 2;
    int rows = h * 2; // Строка для чисел + строка для веток

    // Создаем матрицу символов, заполненную пробелами
    std::vector<std::string> display(rows, std::string(width, ' '));

    // Рекурсивная функция для заполнения матрицы
    auto fill = [&](auto self, PNode node, int row, int left, int right) -> void {
        if (!node) return;

        int mid = (left + right) / 2;

        // Записываем значение узла
        std::string val = "[" + std::to_string(node->data) + "]";
        int pos = mid - val.size() / 2;
        for (int i = 0; i < val.size() && (pos + i) < width; ++i) {
            display[row][pos + i] = val[i];
        }

        // Рисуем ветки и рекурсивно переходим к детям
        if (node->left) {
            display[row + 1][mid - 1] = '/';
            self(self, node->left, row + 2, left, mid);
        }
        if (node->right) {
            display[row + 1][mid + 1] = '\\';
            self(self, node->right, row + 2, mid, right);
        }
    };

    fill(fill, root, 0, 0, width);

    // Вывод матрицы на экран
    std::cout << "\nГрафическое представление (сверху вниз) \n";
    for (const auto& line : display) {
        // Убираем лишние пробелы в конце строки для чистоты вывода
        std::string trimmed = line;
        size_t last = trimmed.find_last_not_of(' ');
        if (last != std::string::npos) {
            std::cout << trimmed.substr(0, last + 1) << std::endl;
        }
    }
}
PNode Tree::FindNode(PNode root, int K, int& N) {
    PNode current = root;
    N = 0;
    while (current != nullptr) {
        N++;

        if (current->data == K) {
            return current;
        }

        if (K < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return nullptr;
}
PNode Tree::fillVP() {
    using namespace std;
    vector<int> v;
    int size, choice;

    cout << "\nСпособ заполнения Дерева Поиска \n";
    cout << "1 - С клавиатуры (без дубликатов)\n";
    cout << "2 - Из файла\n";
    cout << "3 - Случайные числа (уникальные)\n";
    cout << "Выберите вариант: ";

    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cout << "Ошибка! Введите 1, 2 или 3: ";
        clearInput();
    }

    cout << "Сколько уникальных элементов добавить? ";
    while (!(cin >> size) || size <= 0) {
        cout << "Ошибка! Введите число больше 0: ";
        clearInput();
    }

    PNode root = nullptr;

    switch (choice) {
        case 1: { // Клавиатура
            cout << "Введите " << size << " разных целых чисел:\n";
            while (v.size() < size) {
                cout << "Элемент " << v.size() + 1 << ": ";
                int val = getInt();

                // Проверяем, есть ли уже такое число в векторе (чтобы не было дублей)
                if (find(v.begin(), v.end(), val) == v.end()) {
                    v.push_back(val);
                } else {
                    cout << "Это число уже есть в дереве! Введите другое.\n";
                }
            }
            break;
        }

        case 2: { // Файл
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
            ifstream in(filename);
            if (!in) {
                cout << "Ошибка открытия файла! Создаю пустое дерево.\n";
            } else {
                int val;
                while (in >> val && v.size() < size) {
                    if (find(v.begin(), v.end(), val) == v.end()) {
                        v.push_back(val);
                    }
                }
                in.close();
            }
            break;
        }

        case 3: { // Случайные числа
            srand(time(0));
            cout << "Генерация уникальных чисел: ";
            while (v.size() < size) {
                int val = rand() % 100; // Числа от 0 до 99
                if (find(v.begin(), v.end(), val) == v.end()) {
                    v.push_back(val);
                    cout << val << " ";
                }
            }
            cout << endl;
            break;
        }
    }

    // Строим дерево поиска
    for (int x : v) {
        AddToTree(root, x);
    }

    return root;
}


// 1. Вспомогательная функция высоты
int Tree::getHeight(PNode node) {
    if (!node) return 0;
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

// 2. Функция проверки АВЛ-баланса
bool Tree::isAVLBalanced(PNode node) {
    // Пустое дерево считается сбалансированным
    if (!node) return true;

    // Вычисляем высоту левого и правого поддеревьев
    int leftH = getHeight(node->left);
    int rightH = getHeight(node->right);

    return std::abs(leftH - rightH) <= 1 &&
           isAVLBalanced(node->left) &&
           isAVLBalanced(node->right);
}

void t1() {
    Tree treeManager;
    PNode myTree = nullptr;

    myTree = treeManager.fillV();

    treeManager.printVertical(myTree);
    treeManager.Print(myTree);


    treeManager.clear(myTree);
}
void t2() {
    Tree treeManager;
    PNode myTree = nullptr;
    myTree = treeManager.fillVP();
    treeManager.printVertical(myTree);
    treeManager.Print(myTree);
    std::cout << "Число для поиска:"<<std::endl;
    int k;
    int count = 0;
    k=getInt();
    PNode root = treeManager.FindNode(myTree, k, count);
    std::cout<<"кол-во проанализированных вершин  = "<<count<<std::endl;
    std::cout<<" Указатель = "<<root<<std::endl;


    treeManager.clear(myTree);
}
void t3() {
    Tree treeManager;
    PNode myTree = nullptr;

    myTree = treeManager.fillV();

    treeManager.printVertical(myTree);
    treeManager.Print(myTree);
    cout << endl;
    cout<< std::boolalpha <<treeManager.isAVLBalanced(myTree)<<endl;

    treeManager.clear(myTree);
}