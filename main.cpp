#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

void push(Node* &stackHead, Node* current, Node* newNode);
void pop(Node* &stackHead, Node* current, Node* previous);
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
  
  char input[50];
  cin.get(input, 50);
  cin.get(); 
  for (int i = 0; i < strlen(input); i++) {
    if (isdigit(input[i])) {
      newNode = new Node(input[i]);
      if (queueHead == NULL && queueTail == NULL) {
	queueHead = newNode;
	queueTail = newNode;
      }
      else {
	enqueue(queueHead, queueTail, queueHead, newNode);
      }
    }
    else if ((input[i] == '+') ||
	     (input[i] == '-') ||
	     (input[i] == '*') ||
	     (input[i] == '/') ||
	     (input[i] == '^')) {
      while ((stackHead != NULL) && (peek(stackHead, stackHead)->getChar() != '(')) {
	while ((precedence(peek(stackHead, stackHead)) > precedence(newNode)) || ((precedence(peek(stackHead, stackHead)) == precedence(newNode)) && ((newNode->getChar() != '^')))) {
	  pop(stackHead, stackHead, stackHead);
	  enqueue(queueHead, queueTail, queueHead, peek(stackHead, stackHead));
	}
      }
      push(stackHead, stackHead, newNode);
    }
    else if (input[i] == '(') {
      newNode = new Node(input[i]);
      push(stackHead, stackHead, newNode);
    }
  }
}

void push(Node* &stackHead, Node* current, Node* newNode) {
  if (stackHead == NULL) {
    stackHead = newNode;
  }
  else if (current->getNext() != NULL) {
    push(stackHead, current->getNext(), newNode);
  }
  else {
    current->setNext(newNode);
  }
}

void pop(Node* &stackHead, Node* current, Node* previous) {
  if (stackHead == NULL) {
    cout << "The stack is currently empty!" << endl;
  }
  else if (current->getNext() != NULL) {
    pop(stackHead, current->getNext(), previous);
  }
  else {
    delete current;
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
    return current;
  }
  return 0;
}
void enqueue(Node* &queueHead, Node* &queueTail, Node* current, Node* newNode) {
  if (queueHead == NULL) {
    queueHead = newNode;
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
  else if ((newNode->getChar() == 'x') || (newNode->getChar() == '/')) {
    return 3;
  }
  else if ((newNode->getChar() == '+') || (newNode->getChar() == '-')) {
    return 2;
  }
  return 0;
}
