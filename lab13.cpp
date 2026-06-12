//
// Created by macbook on 24.03.26.
//

#include "lab13.h"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <deque>
#include <fstream>
void clearInput() {
    using namespace std;
    cin.clear();
    cin.ignore(10000, '\n');
}

void printVector(const std::vector<int>& v) {
    std::cout << "Вектор: ";
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

void printList(const std::list<int>& l) {
    std::cout << "Список: ";
    for (int x : l) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

void fillV(std::vector<int>& v) {
    using namespace std;
    int size;
    cout << "Выберите способ заполнения вектора:\n";
    cout << "1 - с клавиатуры\n";
    cout << "2 - из файла\n";
    cout << "3 - случайными числами\n";

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cout << "Ошибка! Введите число 1, 2 или 3: ";
        clearInput();
    }
    clearInput();

    cout << "Введите количество элементов: ";
    while (!(cin >> size) || size <= 0 ||size%2 != 0) {
        cout << "Ошибка! Введите положительное четное число число: ";
        clearInput();
    }
    clearInput();
    v.resize(size);
    switch (choice) {
        case 1: {  // С клавиатуры
            cout << "Введите " << size << " целых чисел:\n";
            for (int i = 0; i < size; ++i) {
                cout << "Элемент " << i + 1 << ": ";
                while (!(cin >> v[i])) {
                    cout << "Ошибка! Введите целое число: ";
                    clearInput();
                }
            }
            clearInput();
            break;
        }

        case 2: {  // Из файла
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;

            ifstream in(filename);
            while (!in.is_open()) {
                cout << "Ошибка! Файл '" << filename << "' не найден.\n";
                cout << "Введите имя файла: ";
                cin >> filename;
                in.open(filename);
            }

            int count = 0;
            for (int i = 0; i < size && in >> v[i]; ++i) {
                count++;
            }
            in.close();

            if (count < size) {
                cout << "Предупреждение! В файле только " << count << " чисел из " << size << "\n";
                cout << "Оставшиеся элементы будут заполнены нулями.\n";
                for (int i = count; i < size; ++i) {
                    v[i] = 0;
                }
            }
            break;
        }

        case 3: {  // Случайные числа
            srand(time(0));
            cout << "Случайные числа от 0 до 99:\n";
            for (int i = 0; i < size; ++i) {
                v[i] = rand() % 100;
                cout << v[i] << " ";
            }
            cout << endl;
            break;
        }

        default:
            cout << "Ошибка! Неизвестный способ выбора.\n";
            break;
    }
}
void fillV2(std::vector<int>& v) {
    using namespace std;
    int size;
    cout << "Выберите способ заполнения вектора:\n";
    cout << "1 - с клавиатуры\n";
    cout << "2 - из файла\n";
    cout << "3 - случайными числами\n";

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cout << "Ошибка! Введите число 1, 2 или 3: ";
        clearInput();
    }
    clearInput();

    cout << "Введите количество элементов: ";
    while (!(cin >> size) || size <= 0 ||size%2 != 0) {
        cout << "Ошибка! Введите положительное четное число число: ";
        clearInput();
    }
    clearInput();
    v.resize(size);
    switch (choice) {
        case 1: {  // С клавиатуры
            cout << "Введите " << size << " целых чисел:\n";
            for (int i = 0; i < size; ++i) {
                cout << "Элемент " << i + 1 << ": ";
                while (!(cin >> v[i])) {
                    cout << "Ошибка! Введите целое число: ";
                    clearInput();
                }
            }
            clearInput();
            break;
        }

        case 2: {  // Из файла
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;

            ifstream in(filename);
            while (!in.is_open()) {
                cout << "Ошибка! Файл '" << filename << "' не найден.\n";
                cout << "Введите имя файла: ";
                cin >> filename;
                in.open(filename);
            }

            int count = 0;
            for (int i = 0; i < size && in >> v[i]; ++i) {
                count++;
            }
            in.close();

            if (count < size) {
                cout << "Предупреждение! В файле только " << count << " чисел из " << size << "\n";
                cout << "Оставшиеся элементы будут заполнены нулями.\n";
                for (int i = count; i < size; ++i) {
                    v[i] = 0;
                }
            }
            break;
        }

        case 3: {  // Случайные числа
            srand(time(0));
            cout << "Случайные числа от -99 до 99:\n";
            for (int i = 0; i < size; ++i) {
                v[i] = (rand() % 200) - 100;
                cout << v[i] << " ";
            }
            cout << endl;
            break;
        }

        default:
            cout << "Ошибка! Неизвестный способ выбора.\n";
            break;
    }
}
void fillL(std::list<int>& l) {
    using namespace std;
    int size;
    l.clear(); // Очищаем список перед заполнением

    cout << "Выберите способ заполнения листа:\n";
    cout << "1 - с клавиатуры\n";
    cout << "2 - из файла\n";
    cout << "3 - случайными числами\n";

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cout << "Ошибка! Введите число 1, 2 или 3: ";
        clearInput(); // Предполагается, что функция очистки определена выше
    }

    cout << "Введите количество элементов: ";
    while (!(cin >> size) || size <= 0) {
        cout << "Ошибка! Введите положительное число: ";
        clearInput();
    }

    switch (choice) {
        case 1: { // С клавиатуры
            cout << "Введите " << size << " целых чисел:\n";
            for (int i = 0; i < size; ++i) {
                int val;
                cout << "Элемент " << i + 1 << ": ";
                while (!(cin >> val)) {
                    cout << "Ошибка! Введите целое число: ";
                    clearInput();
                }
                l.push_back(val);
            }
            break;
        }

        case 2: { // Из файла
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;

            ifstream in(filename);
            while (!in.is_open()) {
                cout << "Ошибка! Файл не найден. Введите имя файла: ";
                cin >> filename;
                in.open(filename);
            }

            int count = 0, val;
            while (count < size && in >> val) {
                l.push_back(val);
                count++;
            }
            in.close();

            if (count < size) {
                cout << "Предупреждение! В файле только " << count << " чисел. Остальные — нули.\n";
                for (int i = count; i < size; ++i) l.push_back(0);
            }
            break;
        }

        case 3: { // Случайные числа
            srand(time(0));
            cout << "Случайные числа: ";
            for (int i = 0; i < size; ++i) {
                int val = rand() % 100;
                l.push_back(val);
                cout << val << " ";
            }
            cout << endl;
            break;
        }
    }
}
void fillLs(std::list<std::string>& l) {
    using namespace std;
    int size;
    l.clear();

    cout << "Выберите способ заполнения списка СЛОВ:\n";
    cout << "1 - с клавиатуры\n";
    cout << "2 - из файла\n";

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 2) {
        cout << "Ошибка! Введите 1 или 2: ";
        clearInput();
    }

    cout << "Введите количество слов: ";
    while (!(cin >> size) || size <= 0) {
        cout << "Ошибка! Введите положительное число: ";
        clearInput();
    }

    switch (choice) {
        case 1: { // С клавиатуры
            cout << "Введите " << size << " слов:\n";
            for (int i = 0; i < size; ++i) {
                string word;
                cout << "Слово " << i + 1 << ": ";
                cin >> word;
                l.push_back(word);
            }
            break;
        }

        case 2: { // Из файла
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;

            ifstream in(filename);
            while (!in.is_open()) {
                cout << "Ошибка! Файл не найден. Имя файла: ";
                cin >> filename;
                in.open(filename);
            }

            int count = 0;
            string word;
            while (count < size && in >> word) {
                l.push_back(word);
                count++;
            }
            in.close();

            if (count < size) {
                cout << "Предупреждение! Найдено только " << count << " слов.\n";
                // Для строк "пустой" элемент — это пустая строка ""
                for (int i = count; i < size; ++i) l.push_back("Empty");
            }
            break;
        }
    }
}
void fillL2(std::list<int>& l) {
    using namespace std;
    int size;
    l.clear(); // Очищаем список перед заполнением

    cout << "Выберите способ заполнения листа:\n";
    cout << "1 - с клавиатуры\n";
    cout << "2 - из файла\n";
    cout << "3 - случайными числами\n";

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cout << "Ошибка! Введите число 1, 2 или 3: ";
        clearInput(); // Предполагается, что функция очистки определена выше
    }

    cout << "Введите количество элементов: ";
    while (!(cin >> size) || size <= 0 || size % 2 != 0) {
        cout << "Ошибка! Введите положительное четное число: ";
        clearInput();
    }

    switch (choice) {
        case 1: { // С клавиатуры
            cout << "Введите " << size << " целых чисел:\n";
            for (int i = 0; i < size; ++i) {
                int val;
                cout << "Элемент " << i + 1 << ": ";
                while (!(cin >> val)) {
                    cout << "Ошибка! Введите целое число: ";
                    clearInput();
                }
                l.push_back(val);
            }
            break;
        }

        case 2: { // Из файла
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;

            ifstream in(filename);
            while (!in.is_open()) {
                cout << "Ошибка! Файл не найден. Введите имя файла: ";
                cin >> filename;
                in.open(filename);
            }

            int count = 0, val;
            while (count < size && in >> val) {
                l.push_back(val);
                count++;
            }
            in.close();

            if (count < size) {
                cout << "Предупреждение! В файле только " << count << " чисел. Остальные — нули.\n";
                for (int i = count; i < size; ++i) l.push_back(0);
            }
            break;
        }

        case 3: { // Случайные числа
            srand(time(0));
            cout << "Случайные числа: ";
            for (int i = 0; i < size; ++i) {
                int val = rand() % 200-100;
                l.push_back(val);
                cout << val << " ";
            }
            cout << endl;
            break;
        }
    }
}
void t1() {

    std::vector<int> V;
    fillV(V);

    std::list<int> L;
    fillL(L);

    auto v_half_end = V.begin() + V.size() / 2;

    auto it = std::find_first_of(L.rbegin(), L.rend(), V.begin(), v_half_end);

    // Если элемент найден
    if (it != L.rend()) {
        L.insert(it.base(), *it);
    }
    else {
         std::cout<<"Элемент не найден"<<std::endl;
    }
    printVector(V);
    printList(L);
}


bool P::isPositive(int x) {
    return x > 0;
}

bool P::isNegative(int x) {
    return x < 0;
}
void t2() {
    std::vector<int> v;
    fillV2(v);

    auto mid = v.begin() + v.size() / 2;

    std::replace_if(v.begin(), mid,P::isNegative,-1);


    std::replace_if(mid, v.end(),P::isPositive,1);
    printVector(v);
}
void t3() {
    std::list<int> l;
    fillL2(l);

    std::stable_partition(l.begin(), l.end(), P::isPositive);
    printList(l);
}
#include <deque>
#include <numeric>
#include <iterator>
std::string C::combine(const std::string& b, const std::string& a) {
    std::string res = "";
    res += a[0];    // Первая буква левого слова
    res += b.back(); // Последняя буква правого слова
    return res;
}
void t4() {
    std::list<std::string> L;
    fillLs(L);
    std::deque<std::string> D;
    std::adjacent_difference(L.begin(), L.end(), std::back_inserter(D), C::combine);
    if (!D.empty()) {
        D.erase(D.begin());
    }
    std::cout << "Дек D: ";
    for (auto& s : D) std::cout << s << " ";
}