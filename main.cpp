#include <iostream>
#include "lb12.h"
int main() {
    setlocale(LC_ALL, "");
    std::cout<<"Введите номер задания "<<std::endl;
    int choice;
    std::cin>>choice;
    std::cin.clear();
    switch (choice) {
        case 1: {
            stl2seq3();
            break;
        }
        case 2: {
            stl2seq9();
            break;
        }
        case 3: {
            stl2seq28();
            break;

        }
        case 4: {
            STL1Iter8();
            break;

        }
        default:
            std::cout << "неверный выбор!\n";
    }
}