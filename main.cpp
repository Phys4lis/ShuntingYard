#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

void push(Node* &stackHead, Node* current, Node* newNode);
void pop(Node* &stackHead, Node* &queueHead, Node* &queueTail, Node* current, Node* previous, bool discard);
Node* peek(Node* &stackHead, Node* current);
void enqueue(Node* &queueHead, Node* &queueTail, Node* current, Node* newNode);
void dequeue(Node* &queueHead, Node* newNode);
int precedence(Node* newNode);

int main() {

  Node* stackHead = NULL;
  Node* queueHead = NULL;
  Node* queueTail = NULL;
  Node* newNode;
  Node* current;
  bool discard;
  
  char input[50];
  cin.get(input, 50);
  cin.get(); 
  for (int i = 0; i < strlen(input); i++) {
    newNode = new Node(input[i]);
    if (isdigit(input[i])) {
      cout << "number in queue" << endl;
      enqueue(queueHead, queueTail, queueHead, newNode);
    }
    else if ((input[i] == '+') ||
	     (input[i] == '-') ||
	     (input[i] == '*') ||
	     (input[i] == '/') ||
	     (input[i] == '^')) {
      while ((((stackHead != NULL) && (peek(stackHead, stackHead)->getChar() != '('))) && (((precedence(peek(stackHead, stackHead)) > precedence(newNode)) || ((precedence(peek(stackHead, stackHead)) == precedence(newNode)) && ((newNode->getChar() != '^')))))) {
	  discard = false;
	  cout << "looping" << endl;
	  pop(stackHead, queueHead, queueTail, stackHead, stackHead, discard);
	  cout << "post pop" << endl;
      }
      push(stackHead, stackHead, newNode);
      cout << "post push" << endl;
    }
    else if (input[i] == '(') {
      push(stackHead, stackHead, newNode);
    }
    else if (input[i] == ')') {
      cout << "right paren" << endl;
      Node* topNode = peek(stackHead, stackHead);
      cout << "peek: " << topNode->getChar() << endl;
      /*while (peek(stackHead, stackHead)->getChar() != ')') {
	if (stackHead != NULL) {
	  discard = false;
	  pop(stackHead, queueHead, queueTail, stackHead, stackHead, discard);
	}
	}*/
      cout << "rah" << endl;
      discard = true;
      pop(stackHead, queueHead, queueTail, stackHead, stackHead, discard);
    }
  }

  /*while (stackHead != NULL) {
    pop(stackHead, queueHead, queueTail, stackHead, stackHead);
    }*/
}

void push(Node* &stackHead, Node* current, Node* newNode) {
  if (stackHead == NULL) {
    cout << "hooray!" << endl;
    stackHead = newNode;
  }
  else if (current->getNext() != NULL) {
    push(stackHead, current->getNext(), newNode);
  }
  else {
    current->setNext(newNode);
  }
}

void pop(Node* &stackHead, Node* &queueHead, Node* &queueTail, Node* current, Node* previous, bool discard) {
  if (stackHead == NULL) {
    cout << "The stack is currently empty!" << endl;
  }
  else if (current->getNext() != NULL) {
    pop(stackHead, queueHead, queueTail, current->getNext(), current, discard);
  }
  else if (current->getChar() == '(') {
    delete current;
    previous->setNext(NULL);
  }
  else {
    cout << "successfully popped!" << endl;
    if (discard == false) {
      enqueue(queueHead, queueTail, queueHead, peek(stackHead, stackHead));
    }
    if (current == stackHead) {
      stackHead = NULL;
    }
    previous->setNext(NULL);
  }
}

Node* peek(Node* &stackHead, Node* current) {
  if (stackHead == NULL) {
    cout << "The stack is currently empty!" << endl;
  }
  else if (current->getNext() != NULL) {
    peek(stackHead, current->getNext());
  }
  else {
    Node* tempNode = new Node('e');
    current = tempNode;
    cout << "char: " << current->getChar() << endl;
    return current;
  }
  return 0;
}

void enqueue(Node* &queueHead, Node* &queueTail, Node* current, Node* newNode) {
  if (queueHead == NULL) {
    queueHead = newNode;
    queueTail = newNode;
  }
  else if (current->getNext() != NULL) {
    enqueue(queueHead, queueTail, current->getNext(), newNode);
  }
  else {
    current->setNext(newNode);
    queueTail = newNode;
  }
}

int precedence(Node* newNode) {
  if (newNode->getChar() == '^') {
    return 4;
  }
  else if ((newNode->getChar() == '*') || (newNode->getChar() == '/')) {
    return 3;
  }
  else if ((newNode->getChar() == '+') || (newNode->getChar() == '-')) {
    return 2;
  }
  return 0;
}
