#include "tr.h"

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

bool InfixValidator::isOperatorChar(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

bool InfixValidator::validateExpression(const std::string& expr) const {
    if (expr.empty()) {
        return false;
    }

    bool expectOperand = true;
    for (size_t i = 0; i < expr.size(); ++i) {
        const unsigned char c = static_cast<unsigned char>(expr[i]);
        if (isspace(c)) {
            continue;
        }

        if (expectOperand) {
            if (c == 'x') {
                expectOperand = false;
                continue;
            }
            if (isdigit(c)) {
                int num = 0;
                while (i < expr.size() && isdigit(static_cast<unsigned char>(expr[i]))) {
                    num = num * 10 + (expr[i] - '0');
                    ++i;
                }
                --i;
                if (num < 1 || num > 30) {
                    return false;
                }
                expectOperand = false;
                continue;
            }
            if (c == '(') {
                continue;
            }
            if (c == '-' && (i + 1 < expr.size())) {
                const unsigned char next = static_cast<unsigned char>(expr[i + 1]);
                if (isdigit(next) || next == 'x' || next == '(') {
                    if (next == 'x') {
                        ++i;
                        expectOperand = false;
                        continue;
                    }
                    if (next == '(') {
                        continue;
                    }
                    ++i;
                    int num = 0;
                    while (i < expr.size() && isdigit(static_cast<unsigned char>(expr[i]))) {
                        num = num * 10 + (expr[i] - '0');
                        ++i;
                    }
                    --i;
                    if (num < 1 || num > 30) {
                        return false;
                    }
                    expectOperand = false;
                    continue;
                }
            }
            return false;
        }

        if (InfixValidator::isOperatorChar(static_cast<char>(c))) {
            expectOperand = true;
            continue;
        }
        if (c == ')') {
            expectOperand = false;
            continue;
        }
        return false;
    }

    return !expectOperand;
}

int ExpressionTree::priority(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int ExpressionTree::powInt(int a, int b) {
    int p = 1;
    for (int i = 0; i < b; ++i) {
        p *= a;
    }
    return p;
}

void ExpressionTree::applyTopOp(std::stack<Pnode>& vals, std::stack<char>& ops) {
    if (vals.size() < 2 || ops.empty()) {
        return;
    }

    const char op = ops.top();
    ops.pop();

    Pnode right = vals.top();
    vals.pop();
    Pnode left = vals.top();
    vals.pop();

    Pnode node = new Node(std::string(1, op));
    node->setLeft(left);
    node->setRight(right);
    vals.push(node);
}

Pnode ExpressionTree::buildFromInfix(const std::string& expr) {
    InfixValidator validator;
    if (!validator.validateExpression(expr)) {
        return nullptr;
    }

    std::stack<Pnode> vals;
    std::stack<char> ops;

    auto applyWhileHigher = [&](char incoming) {
        while (!ops.empty() && priority(ops.top()) >= priority(incoming)) {
            applyTopOp(vals, ops);
        }
    };

    for (size_t i = 0; i < expr.size(); ++i) {
        const unsigned char c = static_cast<unsigned char>(expr[i]);
        if (isspace(c)) {
            continue;
        }

        if (isdigit(c)) {
            int num = 0;
            while (i < expr.size() && isdigit(static_cast<unsigned char>(expr[i]))) {
                num = num * 10 + (expr[i] - '0');
                ++i;
            }
            --i;
            vals.push(new Node(std::to_string(num)));
            continue;
        }

        if (c == 'x') {
            vals.push(new Node("x"));
            continue;
        }

        if (c == '(') {
            ops.push('(');
            continue;
        }

        if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                applyTopOp(vals, ops);
            }
            if (!ops.empty()) {
                ops.pop();
            }
            continue;
        }

        if (InfixValidator::isOperatorChar(static_cast<char>(c))) {
            if (c == '-' && vals.empty() && (i + 1 < expr.size())) {
                const unsigned char next = static_cast<unsigned char>(expr[i + 1]);
                if (isdigit(next) || next == 'x' || next == '(') {
                    if (next == 'x') {
                        vals.push(new Node("x"));
                        i++;
                        continue;
                    }
                    if (next == '(') {
                        ops.push('(');
                        i++;
                        continue;
                    }
                    ++i;
                    int num = 0;
                    while (i < expr.size() && isdigit(static_cast<unsigned char>(expr[i]))) {
                        num = num * 10 + (expr[i] - '0');
                        ++i;
                    }
                    --i;
                    vals.push(new Node(std::to_string(num)));
                    continue;
                }
            }

            applyWhileHigher(static_cast<char>(c));
            ops.push(static_cast<char>(c));
        }
    }

    while (!ops.empty()) {
        applyTopOp(vals, ops);
    }

    return vals.size() == 1 ? vals.top() : nullptr;
}

int ExpressionTree::evaluate(Pnode root, int xVal) const {
    if (!root) return 0;

    const std::string& val = root->getValue();
    if (val == "x") return xVal;
    if (isdigit(static_cast<unsigned char>(val[0]))) {
        int n = 0;
        for (char d : val) {
            n = n * 10 + (d - '0');
        }
        return n;
    }

    const int a = evaluate(root->getLeft(), xVal);
    const int b = evaluate(root->getRight(), xVal);

    if (val == "+") return a + b;
    if (val == "-") return a - b;
    if (val == "*") return a * b;
    if (val == "/") return (b != 0) ? a / b : 0;
    if (val == "%") return (b != 0) ? a % b : 0;
    if (val == "^") return powInt(a, b);
    return 0;
}

Pnode ExpressionTree::transform(Pnode root) {
    if (!root) return nullptr;

    root->setLeft(transform(root->getLeft()));
    root->setRight(transform(root->getRight()));

    if (root->getValue() == "*" && root->getLeft() != nullptr &&
        root->getLeft()->getValue() == "x") {
        Pnode tmp = root->getLeft();
        root->setLeft(root->getRight());
        root->setRight(tmp);
    }
    return root;
}

void ExpressionTree::printTree(Pnode root, int indent) const {
    if (root != nullptr) {
        if (root->getRight()) printTree(root->getRight(), indent + 4);
        if (indent) std::cout << std::string(indent, ' ');
        std::cout << root->getValue() << "\n";
        if (root->getLeft()) printTree(root->getLeft(), indent + 4);
    }
}

void ExpressionTree::printSideways(Pnode root, std::ofstream& out, int depth) const {
    if (!root) return;

    printSideways(root->getRight(), out, depth + 1);

    for (int i = 0; i < depth * 4; ++i) {
        out << ' ';
    }
    out << std::setw(4) << std::right << root->getValue() << '\n';

    printSideways(root->getLeft(), out, depth + 1);
}

void ExpressionTree::clear(Pnode root) {
    if (!root) return;
    clear(root->getLeft());
    clear(root->getRight());
    delete root;
}

std::string ExpressionTree::generateRandomExpr() {
    const char ops[] = {'+', '-', '*', '/', '%', '^'};
    const std::string n1 = std::to_string(rand() % 30 + 1);
    const std::string n2 = std::to_string(rand() % 30 + 1);
    const std::string n3 = std::to_string(rand() % 30 + 1);
    const std::string op1(1, ops[rand() % 6]);
    const std::string op2(1, ops[rand() % 6]);

    switch (rand() % 6) {
        case 0:
            return n1 + op1 + n2;
        case 1:
            return n1 + op1 + n2 + op2 + n3;
        case 2:
            return std::string("x") + op1 + n2;
        case 3:
            return n1 + op1 + "x";
        case 4:
            return n1 + op1 + "x" + op2 + n3;
        default:
            return std::string("x") + op1 + n2 + op2 + n1;
    }
}

void t2() {
    ExpressionTree tree;
    std::string expr;

    std::cout << "Способ ввода выражения:\n";
    std::cout << "  1 - с консоли\n";
    std::cout << "  2 - случайное\n";
    std::cout << "  3 - из файла f1.txt\n";

    int inputChoice = 0;
    std::cin >> inputChoice;
    std::cin.clear();
    std::cin.ignore(10000, '\n');

    switch (inputChoice) {
        case 1:
            std::cout << "Введите выражение (+ - * / % ^, x, числа 1..30): ";
            std::getline(std::cin, expr);
            break;
        case 2:
            srand(static_cast<unsigned>(time(nullptr)));
            expr = ExpressionTree::generateRandomExpr();
            std::cout << "Случайное выражение: " << expr << '\n';
            break;
        case 3: {
            std::ifstream fin("f1.txt");
            if (!fin) {
                std::cout << "Не открылся файл f1.txt\n";
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

    InfixValidator validator;
    if (!validator.validateExpression(expr)) {
        std::cout << "Ошибка: числа 1..30, операции + - * / % ^, переменная x\n";
        return;
    }

    Pnode root = tree.buildFromInfix(expr);
    if (!root) {
        std::cout << "Ошибка построения дерева\n";
        return;
    }

    int xVal = 0;
    std::cout << "Введите x: ";
    while (!(std::cin >> xVal)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Повторите ввод x: ";
    }

    int answer = tree.evaluate(root, xVal);

    std::cout << "Исходное дерево:\n";
    tree.printTree(root, 0);

    Pnode transformed = tree.transform(root);
    root = nullptr;

    std::cout << "\nПосле трансформации (x*A -> A*x):\n";
    tree.printTree(transformed, 0);

    std::ofstream fout("FN2.txt");
    if (!fout) {
        std::cout << "Не открылся файл FN2\n";
        tree.clear(transformed);
        return;
    }

    fout << answer << ", x = " << xVal << "\n\n";
    tree.printSideways(transformed, fout, 0);
    fout.close();

    std::cout << "\nРезультат " << answer << " записан в FN2\n";

    tree.clear(transformed);
}
