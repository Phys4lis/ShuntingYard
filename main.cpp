#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

void push(Node* &stackHead, Node* newNode);
void pop(Node* &stackHead);
void peek(Node* &stackHead);
void enqueue(Node* &queueTail, Node* newNode);
void dequeue(Node* &queueHead, Node* newNode);

int main() {

  Node* stackHead = NULL;
  Node* queueHead = NULL;
  Node* queueTail = NULL;
  Node* newNode;
  
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
	enqueue(queueTail, newNode);
      }
    }
    else if ((input[i] == '+') ||
	     (input[i] == '-') ||
	     (input[i] == '*') ||
	     (input[i] == '/') ||
	     (input[i] == '^')) {
      
    }
    else if (input[i] == '(') {
      newNode = new Node(input[i]);
      push(stackHead, newNode);
    }
  }
}

void push(Node* &stackHead, Node* newNode) {
  if (stackHead->getNext() != NULL) {
    stackHead = stackHead->getNext();
    push(stackHead, newNode);
  }
  else {
    stackHead->setNext(newNode);
  }
}

void enqueue(Node* &queueTail, Node* newNode) {
  queueTail->setNext(newNode);
}
