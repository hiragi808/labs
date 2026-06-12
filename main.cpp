#include "name.h"
#include <iostream>
#include "person.h"
#include "point.h"
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::cout<<"Введите номер задания "<<std::endl;
    int choice;
    std::cin>>choice;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    switch (choice) {
        case 1: {
            t1();
            break;
        }
        case 2: {
            t2();
            break;
        }
        case 3: {
            t3();
            break;

        }
        case 4: {
            t4();
            break;

        }
        default:
            std::cout << "неверный выбор!\n";
    }
}