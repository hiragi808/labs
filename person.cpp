//
// Created by macbook on 12.04.26.
//

#include "person.h"
#include "Name.h"
#include <iostream>

Person::Person(FullName n, int h, Person* f) {
    name = n;    // Присваиваем имя
    height = h;  // Присваиваем рост
    father = f;  // Присваиваем указатель на отца
}

FullName Person::getFinalName()  {
    // Создаем копию текущего имени, которую будем дополнять
    FullName result = name;

    // Если папа есть — пробуем взять у него данные
    if (father != nullptr) {

        // получим полное имя отца
        FullName fathersName = father->getFinalName();

        // Проверяем фамилию: если у ребенка пусто, а у папы есть
        if (result.getLastName() == "") {
            if (fathersName.getLastName() != "") {
                result.setLastName(fathersName.getLastName());
            }
        }

        // Проверяем отчество: если у ребенка пусто, а у папы есть имя
        if (result.getMiddleName() == "") {
            if (fathersName.getFirstName() != "") {
                // Просто склеиваем имя папы и окончание
                std::string newMiddleName = fathersName.getFirstName() + "ович";
                result.setMiddleName(newMiddleName);
            }
        }
    }

    return result;
}
Person Person::createP(Person* ot){
    using namespace std;
    cin.clear();
    cin.ignore(1000, '\n');
    FullName newPerson;
    newPerson = FullName::create();
    cout<<"Введите рост"<<endl;
    int h;
    while (!(cin >> h)) {

        cout << "Ошибка! ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    if (!(h>=100 and h<=300)) {
        cout << "Ошибка! ";
        h=150;
    }
    return Person(newPerson,h,ot);
}

void Person::print() {
    std::cout <<"Человек с именем " <<getFinalName().toString() << "и ростом " << height << std::endl;
}
void t2() {
    Person cleo(FullName("", "Клеопатра"), 152);
    Person pushkin(FullName("Пушкин", "Александр", "Сергеевич"), 167);
    Person mayak(FullName("Маяковский", "Владимир"), 189);

    std::cout << "Список людей" << std::endl;
    cleo.print();
    pushkin.print();
    mayak.print();
    int s;
   std::vector<Person> z;
    std::cout<<"Кол-во людей?"<<std::endl;
    std::cin>>s;
    for (int i = 0; i < s; i++) {
       z.push_back(Person::createP(nullptr));
    }
    std::cout<<"Весь список"<<std::endl;
    for (int i = 0; i < s; i++) {
        z[i].print();
    }

    std::cout<<"Расставте семейное древо. -1 = сирота "<<std::endl;
    for (int i = 0; i < s; ++i) {
        using namespace std;
        z[i].print();
        int ind;
        while (!(cin>>ind) or ind==i) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Ошибка!";
        }
        z[i].setf(&z[ind]);
    }
    std::cout<<"Весь список"<<std::endl;
    for (int i = 0; i < s; i++) {
        z[i].print();
    }
}