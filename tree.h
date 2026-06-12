//
// Created by macbook on 09.05.26.
//

#ifndef LAB17_2_TREE_H
#define LAB17_2_TREE_H

#include "node.h"

#include <string>

class RpnValidator {
public:
    bool validateExpression(const std::string& expr) const;
    static bool isOperatorToken(const std::string& token);
    static bool isOperandToken(const std::string& token);
};

class RpnTree {
public:
    static Pnode buildFromExpr(const std::string& expr);
    static void encodeTree(Pnode root);
    static int evaluate(Pnode root);
    static Pnode transform(Pnode root);
    static void printTree(Node* root, int indent = 0);
    static void clear(Pnode root);
    static std::string generateRandomExpr();

private:
    static bool isEncodedOperator(const std::string& v);
};

void t1();

#endif // LAB17_2_TREE_H
