#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node {
 public:
  // Constructor
  Node();
  Node(char);
  // Destructor
  ~Node();
  // Get the next node in the list
  Node* getNext();
  Node* getLeft();
  Node* getRight();
  char getChar();
  // Set the next node in the list
  void setNext(Node* n);
  void setLeft(Node* n);
  void setRight(Node* n);
  void setChar(char newc);
  char c;
private:
  // Variables
  Node* next;
  Node* left;
  Node* right;
};
#endif
