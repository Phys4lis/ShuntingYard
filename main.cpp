#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

void push(Node* &stackHead, Node* current, Node* newNode);
void pop(Node* &stackHead, Node* &queueHead, Node* &queueTail, Node* current, Node* previous, bool discard);
char peek(Node* stackHead);
void printStack(Node* stackHead);
void enqueue(Node* &queueHead, Node* &queueTail, Node* current, Node* newNode);
void dequeue(Node* &queueHead, Node* newNode);
int precedence(char nodeChar);
bool conditions(Node* stackHead, Node* newNode);

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
    cout << endl;
    printStack(stackHead);
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
      while ((conditions(stackHead, newNode) == true) && (stackHead != NULL)) {
	  discard = false;
	  cout << "while loop" << endl;
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
      cout << "peek: " << peek(stackHead) << endl;
      while ((peek(stackHead) != ')') && (stackHead != NULL)) {
	if (stackHead != NULL) {
	  discard = false;
	  pop(stackHead, queueHead, queueTail, stackHead, stackHead, discard);
        }
      }
      cout << "rah" << endl;
      discard = true;
      pop(stackHead, queueHead, queueTail, stackHead, stackHead, discard);
    }
  }

  while (stackHead != NULL) {
    discard = false;
    pop(stackHead, queueHead, queueTail, stackHead, stackHead, discard);
  }
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
      enqueue(queueHead, queueTail, queueHead, current);
    }
    if (current == stackHead) {
      stackHead = NULL;
    }
    previous->setNext(NULL);
  }
}

char peek(Node* stackHead) {
  if (stackHead == NULL) {
    cout << "The stack is currently empty!" << endl;
  }
  else if (stackHead->getNext() != NULL) {
    peek(stackHead->getNext());
  }
  else {
    cout << "peek char: " << stackHead->getChar() << endl;
    return (stackHead->getChar());
  }
  return 0;
}

void printStack(Node* stackHead) {
  if (stackHead == NULL) {
    cout << "empty stack" << endl;
  }
  else if (stackHead->getNext() != NULL) {
    cout << "printing: " << stackHead->getChar() << endl;
    printStack(stackHead->getNext());
  }
  else {
    cout << "printing: " << stackHead->getChar() << endl << endl;
  }
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

int precedence(char nodeChar) {
  if (nodeChar == '^') {
    return 4;
  }
  else if ((nodeChar == '*') || (nodeChar == '/')) {
    return 3;
  }
  else if ((nodeChar == '+') || (nodeChar == '-')) {
    return 2;
  }
  else {
    return 0;
  }
}

bool conditions(Node* stackHead, Node* newNode) {
  bool notLeftParen = false;
  if (peek(stackHead) != '(') {
    notLeftParen = true;
  }
  bool greaterPrecedence = false;
  if ((precedence(peek(stackHead))) > (precedence(newNode->getChar()))) {
      greaterPrecedence = true;
  }
  bool equalPrecedence = false;  
  if (((precedence(peek(stackHead))) == (precedence(newNode->getChar()))) && (newNode->getChar() != '^')) {
    equalPrecedence = true;
  }
  if ((notLeftParen == true) && ((greaterPrecedence == true) || (equalPrecedence == true))) {
    cout << "what the flip" << endl;
    return true;
  }
  else {
    cout << "left paren? " << notLeftParen << endl;
    cout << "greaterPrec? " << greaterPrecedence << endl;
    cout << "equalPrec? " << equalPrecedence << endl;
    char huh = peek(stackHead);
    cout << "char: " << huh << endl;
    cout << "stackHead Prec: " << precedence(huh) << endl;
    cout << "newNode Prec: " << precedence(newNode->getChar()) << endl;
    return false;
  }
}
