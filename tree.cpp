//
// Created by macbook on 09.05.26.
//

#include "tree.h"

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

bool RpnValidator::isOperatorToken(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

bool RpnValidator::isOperandToken(const std::string& token) {
    if (token.empty() || token.size() > 1) {
        return false;
    }
    if (!isdigit(static_cast<unsigned char>(token[0]))) {
        return false;
    }
    const int num = token[0] - '0';
    return num >= 0 && num <= 9;
}

bool RpnValidator::validateExpression(const std::string& expr) const {
    if (expr.empty()) {
        return false;
    }

    std::stringstream ss(expr);
    std::string token;
    int stackSize = 0;

    while (ss >> token) {
        if (isOperandToken(token)) {
            stackSize++;
        } else if (isOperatorToken(token)) {
            if (stackSize < 2) {
                return false;
            }
            stackSize--;
        } else {
            return false;
        }
    }

    return stackSize == 1;
}

Pnode RpnTree::buildFromExpr(const std::string& expr) {
    RpnValidator validator;
    if (!validator.validateExpression(expr)) {
        return nullptr;
    }

    std::stack<Node*> vals;
    std::stringstream ss(expr);
    std::string token;

    while (ss >> token) {
        if (RpnValidator::isOperatorToken(token)) {
            Node* z = new Node(token);
            z->setRight(vals.top());
            vals.pop();
            z->setLeft(vals.top());
            vals.pop();
            vals.push(z);
        } else {
            vals.push(new Node(token));
        }
    }

    return vals.empty() ? nullptr : vals.top();
}

void RpnTree::encodeTree(Pnode root) {
    if (!root) return;

    encodeTree(root->getLeft());
    encodeTree(root->getRight());

    const std::string& v = root->getValue();
    if (v == "+") root->setValue("-1");
    else if (v == "-") root->setValue("-2");
    else if (v == "*") root->setValue("-3");
    else if (v == "/") root->setValue("-4");
}

bool RpnTree::isEncodedOperator(const std::string& v) {
    return v == "-1" || v == "-2" || v == "-3" || v == "-4";
}

int RpnTree::evaluate(Pnode root) {
    if (!root) return 0;

    const std::string& v = root->getValue();
    if (!isEncodedOperator(v)) {
        return std::stoi(v);
    }

    const int l = evaluate(root->getLeft());
    const int r = evaluate(root->getRight());

    if (v == "-1") return l + r;
    if (v == "-2") return l - r;
    if (v == "-3") return l * r;
    if (v == "-4") return (r != 0) ? l / r : 0;
    return 0;
}

static void deleteSubtree(Pnode root) {
    if (!root) return;
    deleteSubtree(root->getLeft());
    deleteSubtree(root->getRight());
    delete root;
}

Pnode RpnTree::transform(Pnode root) {
    if (!root) return nullptr;

    if (root->getValue() == "-1") {
        const int res = evaluate(root);
        deleteSubtree(root);
        return new Node(std::to_string(res));
    }

    root->setLeft(transform(root->getLeft()));
    root->setRight(transform(root->getRight()));
    return root;
}

void RpnTree::printTree(Node* root, int indent) {
    if (root != nullptr) {
        if (root->getRight()) printTree(root->getRight(), indent + 4);
        if (indent) std::cout << std::string(indent, ' ');
        std::cout << root->getValue() << "\n";
        if (root->getLeft()) printTree(root->getLeft(), indent + 4);
    }
}

void RpnTree::clear(Pnode root) {
    deleteSubtree(root);
}

std::string RpnTree::generateRandomExpr() {
    const char ops[] = {'+', '-', '*', '/'};
    const int n1 = rand() % 10;
    const int n2 = rand() % 10;
    const int n3 = rand() % 10;
    const char op1 = ops[rand() % 4];
    const char op2 = ops[rand() % 4];
    return std::to_string(n1) + " " + std::to_string(n2) + " " + op1 + " " +
           std::to_string(n3) + " " + op2;
}

void t1() {
    std::string expr;

    std::cout << "Способ ввода выражения:\n";
    std::cout << "  1 - с консоли\n";
    std::cout << "  2 - случайное\n";
    std::cout << "  3 - из файла filename.txt\n";

    int inputChoice = 0;
    std::cin >> inputChoice;
    std::cin.clear();
    std::cin.ignore(10000, '\n');

    switch (inputChoice) {
        case 1:
            std::cout << "Введите выражение (ОПЗ): ";
            std::getline(std::cin, expr);
            break;
        case 2:
            srand(static_cast<unsigned>(time(nullptr)));
            expr = RpnTree::generateRandomExpr();
            std::cout << "Случайное выражение: " << expr << '\n';
            break;
        case 3: {
            std::ifstream fin("filename.txt");
            if (!fin) {
                std::cout << "Не открылся файл filename.txt\n";
                return;
            }
            std::getline(fin, expr);
            fin.close();
            std::cout << "Из файла: " << expr << '\n';
            break;
        }
        default:
            std::cout << "Неверный выбор!\n";
            return;
    }

    if (expr.empty()) {
        std::cout << "Пустое выражение\n";
        return;
    }

    RpnValidator validator;
    if (!validator.validateExpression(expr)) {
        std::cout << "Ошибка: корректное ОПЗ, числа от 0 до 9, операции + - * /\n";
        return;
    }

    Pnode root = RpnTree::buildFromExpr(expr);
    if (!root) {
        std::cout << "Ошибка построения дерева\n";
        return;
    }

    std::cout << "Исходное дерево (операции как символы):\n";
    RpnTree::printTree(root, 0);

    RpnTree::encodeTree(root);

    std::cout << "\nЗакодированное дерево:\n";
    RpnTree::printTree(root, 0);

    root = RpnTree::transform(root);

    std::cout << "\nПосле трансформации (без сложения):\n";
    RpnTree::printTree(root, 0);

    std::cout << "\nУказатель на корень: " << root << std::endl;

    RpnTree::clear(root);
}
