#include "name.h"
#include <sstream>
#include <iostream>
#include <vector>

FullName::FullName(std::string ln, std::string fn, std::string mn)
    : lastName(ln), firstName(fn), middleName(mn) {}

std::string FullName::toString() const {
    std::string result = "";
    std::vector<std::string> parts;

    if (!lastName.empty()) parts.push_back(lastName);
    if (!firstName.empty()) parts.push_back(firstName);
    if (!middleName.empty()) parts.push_back(middleName);

    for (size_t i = 0; i < parts.size(); ++i) {
        result += parts[i];
        if (i < parts.size() - 1) result += " ";
    }
    return result;
}

void FullName::print() const {
    std::string out = toString();
    if (out.empty()) {
        std::cout << "[Пустое имя]" << std::endl;
    } else {
        std::cout << out << std::endl;
    }
}
#include <cctype>
#include <algorithm>

bool isOnlyAlpha(const std::string& s) {
    if (s.empty()) return true;

    for (int i = 0; i < s.length(); ++i) {
        unsigned char c = s[i];

        // Проверка на пробел
        if (c == ' ') continue;


        if (c >= 0xD0 && c <= 0xD1) {
            if (i + 1 < s.length()) {
                i++;
                continue;
            }
        }


        return false;
    }
    return true;
}


std::string getLineFromUser() {
    std::string value;
    while (true) {
        std::getline(std::cin, value);
        if (isOnlyAlpha(value)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            break;
        }
        std::cout << "Ошибка! Пожалуйста, используйте только буквы: ";
    }
    return value;
}
FullName FullName::create() {

    std::cout << "\nСоздание вашего имени" << std::endl;

    std::cout << "Введите фамилию (или оставьте пустой): ";
    std::string ln = getLineFromUser();

    std::cout << "Введите имя (или оставьте пустой): ";
    std::string fn = getLineFromUser();

    std::cout << "Введите отчество (или оставьте пустой): ";
    std::string mn = getLineFromUser();

    FullName userPerson(ln, fn, mn);
    return userPerson;
}
void t1() {
    FullName cleopatra("", "Клеопатра", "");
    FullName pushkin("Пушкин", "Александр", "Сергеевич");
    FullName mayakovsky("Маяковский", "Владимир", "");

    std::cout << "Демонстрация готовых имен" << std::endl;
    cleopatra.print();
    pushkin.print();
    mayakovsky.print();
    FullName userPerson;
    userPerson = userPerson.create();
    userPerson.print();
}