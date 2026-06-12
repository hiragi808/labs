//
// Created by macbook on 14.04.26.
//

#ifndef LAB16_TREE_H
#define LAB16_TREE_H
#include <vector>
// Структура узла
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

typedef Node* PNode;

class Tree {
public:
    void AddToTree(PNode& node, int val);
    void AddToTreed(PNode& node, int val);
    PNode fillV();
    PNode fillVP();
    void Print(PNode node);
    void printVertical(PNode root);
    void clear(PNode node);

    PNode FindNode(PNode root, int K, int& N);
    int getHeight(PNode node);
    bool isAVLBalanced(PNode root);
};
void t1();
void t2();
void t3();
#endif //LAB16_TREE_H