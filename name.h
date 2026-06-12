#ifndef FULLNAME_H
#define FULLNAME_H

#include <string>
#include <vector>

class FullName {
private:
    std::string lastName;   // Фамилия
    std::string firstName;  // Личное имя
    std::string middleName; // Отчество

public:
    // Конструктор с параметрами по умолчанию (пустые строки)
    FullName(std::string ln = "", std::string fn = "", std::string mn = "");


    std::string toString() const;

    // Геттеры для логики наследования
    std::string getLastName() const { return lastName; }
    std::string getFirstName() const { return firstName; }
    std::string getMiddleName() const { return middleName; }

    // Сеттеры для динамического изменения при наследовании
    void setLastName(std::string ln) { lastName = ln; }
    void setMiddleName(std::string mn) { middleName = mn; }

    static FullName create();
    void print() const;
};
void t1();
std::string getLineFromUser();

#endif
