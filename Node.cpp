//
// Created by macbook on 09.03.26.
//

#include "Node.h"

#include <iostream>
#include <fstream>
Node::Node() : data(0), next(nullptr), prev(nullptr) {}

Node::Node(int value) : data(value), next(nullptr), prev(nullptr) {}

Node::Node(int value, Node* nextNode, Node* prevNode)
    : data(value), next(nextNode), prev(prevNode) {}

int Node::getData() {return data;}

Node* Node::getNext() {return next;}

Node* Node::getPrev(){return prev;}

void Node::setData(int value) {data = value;}

void Node::setNext(Node* nextNode) {next = nextNode;}

void Node::setPrev(Node* prevNode) {prev = prevNode;}
