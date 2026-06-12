//
// Created by macbook on 24.03.26.
//

#ifndef LAB13_LAB13_H
#define LAB13_LAB13_H
#include <iostream>
#include <list>
#include <string>
void t1();
void t2();
void t3();
void t4();
void clearInput();
void fillV(std::vector<int>& v);
void fillV2(std::vector<int>& v);
void fillL(std::list<int>& l);
void printVector(const std::vector<int>& v);
void printList(const std::list<int>& l);
void fillL2();
void fillLs(std::list<std::string>& l);
std::string combine(const std::string& b, const std::string& a);
class P {
    public:
    bool static isPositive(int x);
    bool static isNegative(int x);
};
class C {
public:
    std::string static combine(const std::string& b, const std::string& a);
};
#endif //LAB13_LAB13_H