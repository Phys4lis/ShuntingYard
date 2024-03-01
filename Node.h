#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node {
 public:
  // Constructor
  Node();
  // Destructor
  ~Node();
  // Get the next node in the list
  Node* getNext();
  // Set the next node in the list
  void setNext(Node* n);
  
 private:
  // Variables
  Node* next;
};
#endif
