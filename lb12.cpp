//
// Created by macbook on 17.03.26.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <iterator>
#include <string>
#include "lb12.h"
void clearInput() {
    using namespace std;
    cin.clear();
    cin.ignore(10000, '\n');
}
void stl2seq3() {
    using namespace std;
    cout << "\n=== STL2Seq3 ===\n";
    cout<<"Дан набор целых чисел с четным количеством элементов. Заполнить вектор V\n";
    vector<int> V;
    int* arr;
    int size;
    do {
        fillArray(arr, size);
        if (size % 2 != 0) {
            cout << "Ошибка! Количество элементов должно быть ЧЁТНЫМ.\n";
            cout << "Повторите ввод.\n\n";
            delete[] arr;  // освобождаем память перед повторным вводом
        }
    } while (size % 2 != 0);
    vector<int> V1(arr, arr + size);
    int half = size / 2;
    vector<int>::iterator it;

    cout << "Вторая половина: ";
    for (it = V1.begin() + half; it != V1.end(); ++it)
        cout << *it << " ";

    cout << "\nПервая половина: ";
    for (it = V1.begin(); it != V1.begin() + half; ++it)
        cout << *it << " ";
    cout << endl;

}

void fillArray(int*& arr, int& size) {
    using namespace std;
    cout << "Выберите способ заполнения:\n";
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
    while (!(cin >> size) || size <= 0) {
        cout << "Ошибка! Введите положительное число: ";
        clearInput();
    }
    clearInput();

    arr = new int[size];

    switch (choice) {
        case 1: {  // С клавиатуры
            cout << "Введите " << size << " целых чисел:\n";
            for (int i = 0; i < size; ++i) {
                cout << "Элемент " << i + 1 << ": ";
                while (!(cin >> arr[i])) {
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
            for (int i = 0; i < size && in >> arr[i]; ++i) {
                count++;
            }
            in.close();

            if (count < size) {
                cout << "Предупреждение! В файле только " << count << " чисел из " << size << "\n";
                cout << "Оставшиеся элементы будут заполнены нулями.\n";
                for (int i = count; i < size; ++i) {
                    arr[i] = 0;
                }
            }
            break;
        }

        case 3: {  // Случайные числа
            srand(time(0));
            cout << "Случайные числа от 0 до 99:\n";
            for (int i = 0; i < size; ++i) {
                arr[i] = rand() % 100;
                cout << arr[i] << " ";
            }
            cout << endl;
            break;
        }

        default:
            cout << "Ошибка! Неизвестный способ выбора.\n";
            break;
    }
}
void stl2seq9() {
    using namespace std;
    cout << "\n=== STL2Seq9 ===\n";
    cout << "Дек D с нечетным количеством элементов N (≥ 5).\n";
    int* arr;
    int size;

    do {
        fillArray(arr, size);
        if (size < 5) {
            cout << "Ошибка! Количество элементов должно быть >= 5.\n";
            cout << "Повторите ввод.\n\n";
        }
        else if (size % 2 == 0) {
            cout << "Ошибка! Количество элементов должно быть НЕЧЁТНЫМ.\n";
            cout << "Повторите ввод.\n\n";
        }
    } while (size < 5 || size % 2 == 0);

    deque<int> D;
    for (int i = 0; i < size; ++i) {
        D.push_back(arr[i]);
    }

    cout << "Исходный дек: ";
    for (deque<int>::iterator it = D.begin(); it != D.end(); ++it) {
        cout << *it << " ";
    }
    cout<<endl;
    cout << "Полученый дек: ";
    int middleIndex = size / 2;  // индекс центрального элемента
    cout << endl;
    cout << D[middleIndex] << endl;
    int startIndex = middleIndex - 2; // индекс первого из пяти средних


    D.insert(D.begin(), D.begin() + startIndex, D.begin() + startIndex + 5);
    for (deque<int>::iterator it = D.begin(); it != D.end(); ++it) {
        cout << *it << " ";
    }

}
void stl2seq28() {
    using namespace std;
    cout << "\n=== STL2Seq28 ===\n";
    cout << "Дек D с количеством элементов, кратным 4.\n";
    int* arr;
    int size;

    do {
        fillArray(arr, size);
        if (size < 4) {
            cout << "Ошибка! Количество элементов должно быть >= 4.\n";
            cout << "Повторите ввод.\n\n";
        }
        else if (size % 4 != 0) {
            cout << "Ошибка! Количество элементов должно быть КРАТНЫМ 4.\n";
            cout << "Повторите ввод.\n\n";
        }
    } while (size < 4 || size % 4 != 0);

    deque<int> D;
    for (int i = 0; i < size; ++i) {
        D.push_back(arr[i]);
    }

    cout << "Исходный дек: ";
    for (deque<int>::iterator it = D.begin(); it != D.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    deque<int>::iterator it = D.begin();
    for (int i=0;  i<size/4; i++) {
        it=D.erase(++it);
    }

    cout << "Полученный дек: ";
    for (deque<int>::iterator it = D.begin(); it != D.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}
void createFile(std::string filename) {
    using namespace std;
    cout << "\nВыберите способ заполнения файла " << filename << ":\n";
    cout << "1 - Ввод с клавиатуры\n";
    cout << "2 - Случайные слова\n";
    cout << "3 - Из другого файла \n";

    int choice;
    cout << "Ваш выбор: ";
    cin >> choice;

    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка создания файла!" << endl;
        return;
    }

    switch(choice) {
        case 1: {
            // Ввод с клавиатуры
            cout << "Введите слова (пустая строка - конец ввода):\n";
            cin.ignore(); // очищаем буфер
            string word;
            while (true) {
                getline(cin, word);
                if (word.empty()) break;
                file << word << "\n";
            }
            break;
        }
        case 2: {
            // Случайные слова
            srand(time(nullptr));
            string v = "aeioubcdfghjklmnpqrstvwxyz";

            cout << "Сколько слов сгенерировать? ";
            int count;
            cin >> count;

            for (int i = 0; i < count; i++) {
                // Генерируем слово случайной длины от 3 до 10
                int len = 3 + rand() % 8;
                string word;
                for (int j = 0; j < len; j++) {
                        word += v[rand() % v.length()];
                }
                file << word << "\n";
            }
            cout << "Сгенерировано " << count << " слов.\n";
            break;
        }
        case 3: {
            // Из другого файла
            string name;
            cout<<"Введите имя другого файла\n";
            cin >> name;
            ifstream defaultFile(name);
            if (!defaultFile.is_open()) {
                cerr << "Файл не найден!\n";
                file.close();
                return;
            }

            string word;
            while (defaultFile >> word) {
                file << word << "\n";
            }
            defaultFile.close();
            cout << "Слова скопированы\n";
            break;
        }
        default:
            cout << "Неверный выбор!\n";
            file.close();
            return;
    }

    file.close();
    cout << "Файл " << filename << " успешно создан!\n";
}
void STL1Iter8() {
    using namespace std;
    cout << "\n=== STL1Iter8 ===\n";

    int K;
    string name1, name2;

    // Ввод данных
    cout << "Введите целое число K (> 0): ";
    cin >> K;

    cout << "Введите имя исходного файла (name1): ";
    cin >> name1;

    cout << "Введите имя результирующего файла (name2): ";
    cin >> name2;

    createFile(name1);

    ifstream inputFile(name1);
    if (!inputFile.is_open()) {
        cerr << "Ошибка! Не удалось открыть файл " << name1 << endl;
        return;
    }

    ofstream outputFile(name2);
    if (!outputFile.is_open()) {
        cerr << "Ошибка! Не удалось создать файл " << name2 << endl;
        return;
    }

    cout << "\nСодержимое исходного файла " << name1 << ":\n";

    string word;
    while (inputFile >> word) {
        cout << word << " ";
    }
    cout << "\n";

    inputFile.clear();
    inputFile.seekg(0);

    remove_copy_if(
        istream_iterator<string>(inputFile),
        istream_iterator<string>(),
        ostream_iterator<string>(outputFile, "\n"),
        [K](const string& s) {
            return s.length() > K;
        }
    );

    cout << "Готово! Слова длиной не более " << K << " записаны в файл " << name2 << endl;

    cout << "\nСодержимое результирующего файла " << name2 << ":\n";
    outputFile.close();

    ifstream resultFile(name2);
    if (resultFile.is_open()) {
        while (resultFile >> word) {
            cout << word << "\n";
        }
        resultFile.close();
    }

    inputFile.close();
    outputFile.close();
}