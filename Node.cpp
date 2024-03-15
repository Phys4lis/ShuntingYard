#include <iostream>
#include "Node.h"


using namespace std;

// Constructor
Node::Node() {
  next = NULL;
  left = NULL;
  right = NULL;
}

Node::Node(char newc) {
  c = newc;
  next = NULL;
  left = NULL;
  right = NULL;
}

// Destructor
Node::~Node() {
  next = NULL;
  left = NULL;
  right = NULL;
}

// Getters
Node* Node::getNext() {
  return next;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

char Node::getChar() {
  return c;
}

// Setters
void Node::setNext(Node* n) {
  next = n;
}

void Node::setLeft(Node* n) {
  left = n;
}

void Node::setRight(Node* n) {
  right = n;
}

void Node::setChar(char newc) {
  c = newc;
}
