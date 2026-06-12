#include <iostream>
#include "lab14.h"
int main() {
    setlocale(LC_ALL, "");
    std::cout<<"Введите номер задания "<<std::endl;
    int choice;
    std::cin>>choice;
    std::cin.clear();
    switch (choice) {
        case 1: {
            t1();
            break;
        }
        case 2: {

            break;
        }
        case 3: {

            break;

        }
        case 4: {

            break;

        }
        default:
            std::cout << "неверный выбор!\n";
    }
}