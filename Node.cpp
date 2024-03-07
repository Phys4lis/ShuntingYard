#include <iostream>
#include "Node.h"


using namespace std;

// Constructor
Node::Node() {
  next = NULL;
}

Node::Node(char newc) {
  c = newc;
  next = NULL;
}

// Destructor
Node::~Node() {
  next = NULL;
}

// Getters
Node* Node::getNext() {
  return next;
}

char Node::getChar() {
  return c;
}

// Setters
void Node::setNext(Node* n) {
  next = n;
}

void Node::setChar(char newc) {
  c = newc;
}
