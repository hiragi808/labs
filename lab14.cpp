//
// Created by macbook on 04.04.26.
//

#include "lab14.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include <algorithm>
#include <map>

void clearInput() {
    using namespace std;
    cin.clear();
    cin.ignore(10000, '\n');
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
    while (!(cin >> size) || size <= 0 ) {
        cout << "Ошибка! Введите положительное число: ";
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
void fillVN(std::vector<std::vector<int>>& v) {
    using namespace std;
    int size;
    cout << "Введите количество векторов: ";
    while (!(cin >> size) || size <= 0 ) {
        cout << "Ошибка! Введите положительное число: ";
        clearInput();
    }
    for (int i = 0; i < size; ++i) {
        vector<int> v1;
        fillV(v1);
        v.push_back(v1);
    }
}
void t1() {
    using namespace std;
    vector<vector<int>> vn;
    vector<int> v0;
    fillV(v0);
    fillVN(vn);

    // мультимножество из V0
    std::multiset<int> ms0(v0.begin(), v0.end());

    int count = 0;

    //Цикл по набору векторов
    for (auto& Vi : vn) {
        // Создаем мультимножество из текущего вектора
        std::multiset<int> msI(Vi.begin(), Vi.end());

        // Проверка включения всех элементов V0 в Vi
        if (std::includes(msI.begin(), msI.end(), ms0.begin(), ms0.end())) {
            count++;
        }
    }
    cout << count << "\n";

}
void t2() {
    using namespace std;
    map<int, int> M;
    vector<int> V;
    for (vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        M[*it]++;
    }

    for (map<int, int>::iterator it = M.begin(); it != M.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }

}
void t3() {

}
