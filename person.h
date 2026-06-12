//
// Created by macbook on 12.04.26.
//

#ifndef LAB15_PERSON_H
#define LAB15_PERSON_H


#include "name.h"

class Person {
private:
    FullName name;
    int height;
    Person* father; // Ссылка на объект отца

public:

    Person(FullName n, int h, Person* f = nullptr);

    FullName getFinalName() ;
    void setf(Person* ln) { father = ln; }
    void print();

    static Person createP(Person* ot);
};
void t2();
#endif
