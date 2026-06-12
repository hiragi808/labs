#ifndef LAB17_2_TR_H
#define LAB17_2_TR_H

#include "node.h"

#include <ostream>
#include <stack>


class InfixValidator {
public:
    bool validateExpression(const std::string& expr) const;
    static bool isOperatorChar(char c);
};

class ExpressionTree {
public:
    Pnode buildFromInfix(const std::string& expr);
    int evaluate(Pnode root, int xVal) const;
    Pnode transform(Pnode root);
    void printTree(Pnode root, int indent = 0) const;
    void printSideways(Pnode root, std::ofstream& out, int depth = 0) const;
    void clear(Pnode root);
    static std::string generateRandomExpr();

private:
    static int priority(char op);
    static int powInt(int a, int b);
    static void applyTopOp(std::stack<Pnode>& vals, std::stack<char>& ops);
};

void t2();

#endif // LAB17_2_TR_H
