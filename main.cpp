

#include "functions.h"
#include <iostream>

int main() {
    using namespace std;
    setlocale(LC_ALL, "RU");
    int choice;
    do {
        cout << "1 - TreeFun2: Список в сбалансированное дерево\n";
        cout << "2 - TreeFun6: Итератор корень-право-лево\n";
        cout << "3 - TreeFun10: Пересечение зон камер\n";
        cout << "0 - ВЫХОД\n";
        choice = Check::readIntRange("Выбор: ", 0, 3);
        switch (choice) {
            case 1: TreeFun2(); break;
            case 2: TreeFun6(); break;
            case 3: TreeFun10(); break;
            case 0: cout << "Выход.\n"; break;
        }
    } while (choice != 0);
    return 0;
}