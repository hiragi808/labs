//
// Created by macbook on 26.05.26.
//

#ifndef LAB18_2_FUNCTIONS_H
#define LAB18_2_FUNCTIONS_H

#include <string>
#include <vector>
#include <unordered_set>

class Check {
public:
    static int readInt(const char* text);
    static int readIntMin(const char* text, int minValue);
    static int readIntRange(const char* text, int left, int right);
};

class Node {
private:
    int data;
    Node* left;
    Node* right;

public:
    Node(int value);

    int getData() const;
    Node* getLeft() const;
    Node* getRight() const;

    void setData(int value);
    void setLeft(Node* p);
    void setRight(Node* p);
};

class DoublyList {
private:
    Node* head;
    Node* tail;

    void insertSortedNode(Node* p);
    Node* buildBalanced(int count);

public:
    DoublyList();
    ~DoublyList();

    void clear();
    void pushBack(int value);
    void sortAscending();

    bool fillKeyboard();
    bool fillFile();
    bool fillRandom();

    int count() const;
    Node* toBalancedTree();
    void print() const;

    static void printTreed(Node* root, int indent);
};

class BinaryTree {
private:
    Node* root;

    void clear(Node* p);
    int height(Node* p) const;
    void buildByLevels(const std::vector<int>& values);

    // Для TreeFun10
    int placeCamerasGreedy(Node* p, std::unordered_set<Node*>& camSet) const;
    int countOverlaps(Node* p, Node* parent, const std::unordered_set<Node*>& camSet) const;

public:
    class Iterator {
    private:
        std::vector<Node*> stack;
    public:
        Iterator(Node* root);
        bool hasNext() const;
        int next();
    };

    BinaryTree();
    ~BinaryTree();

    void clear();
    void setRoot(Node* p);

    bool fillKeyboard();
    bool fillFile();
    bool fillRandom();

    void print() const;
    Iterator iteratorRootRightLeft() const;
    int countNodesWithMultipleCoverage() const;
};

void TreeFun2();
void TreeFun6();
void TreeFun10();




#endif //LAB18_2_FUNCTIONS_H