#include <iostream>
#include "Node.h"


using namespace std;

// Constructor
Node::Node() {
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

// Setters
void Node::setNext(Node* n) {
  next = n;
}
