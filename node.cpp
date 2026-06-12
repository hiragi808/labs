#include "node.h"

Node::Node(std::string val) : value(std::move(val)), left(nullptr), right(nullptr) {}

const std::string& Node::getValue() const { return value; }
void Node::setValue(const std::string& val) { value = val; }

Node* Node::getLeft() const { return left; }
void Node::setLeft(Node* node) { left = node; }

Node* Node::getRight() const { return right; }
void Node::setRight(Node* node) { right = node; }
