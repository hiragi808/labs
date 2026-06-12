#ifndef LAB17_2_NODE_H
#define LAB17_2_NODE_H

#include <string>

class Node {
    std::string value;
    Node* left;
    Node* right;

public:
    explicit Node(std::string val);

    const std::string& getValue() const;
    void setValue(const std::string& val);

    Node* getLeft() const;
    void setLeft(Node* node);

    Node* getRight() const;
    void setRight(Node* node);
};

typedef Node* Pnode;

#endif // LAB17_2_NODE_H
