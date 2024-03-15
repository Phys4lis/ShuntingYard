#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

void push(Node* &stackHead, Node* current, Node* newNode);
void pop(Node* &stackHead, Node* &queueHead, Node* &queueTail, Node* current, Node* previous, bool discard, int &size);
char peek(Node* stackHead);
Node* peekNode(Node* stackHead, Node* current);
void printStack(Node* stackHead);
void printQueue(Node* queueHead);
void enqueue(Node* &queueHead, Node* &queueTail, Node* current, Node* newNode, int &size);
Node* dequeue(Node* &queueHead);
int precedence(char nodeChar);
bool conditions(Node* stackHead, Node* newNode);
void infix(Node* bStackHead);
void prefix(Node* bStackHead);
void postfix(Node* bStackHead);

int main() {

  Node* stackHead = NULL;
  Node* queueHead = NULL;
  Node* queueTail = NULL;
  Node* newNode;
  Node* current;
  bool discard;

  int size = 0;

  cout << "Input an infix expression." << endl;
  char input[50];
  cin.get(input, 50);
  cin.get();
  // Loop through the input
  for (int i = 0; i < strlen(input); i++) {
    newNode = new Node(input[i]);
    // If token is a number, output it to the queue
    if (isdigit(input[i])) {
      enqueue(queueHead, queueTail, queueHead, newNode, size);
    }
    // If token is an operator
    else if ((input[i] == '+') ||
	     (input[i] == '-') ||
	     (input[i] == '*') ||
	     (input[i] == '/') ||
	     (input[i] == '^')) {
      // While conditions are met, pop the top of the stack into the queue
      while ((conditions(stackHead, newNode) == true) && (stackHead != NULL)) {
	  discard = false;
	  pop(stackHead, queueHead, queueTail, stackHead, stackHead, discard, size);
      }
      // Push the token (operator) onto the stack
      push(stackHead, stackHead, newNode);
    }
    // If token is a left parenthesis, push it to the stack
    else if (input[i] == '(') {
      push(stackHead, stackHead, newNode);
    }
    // If token is a right parenthesis
    else if (input[i] == ')') {
      // Pop the top operator from the stack into the queue until the top operator is a left parenthesis
      while ((peek(stackHead) != '(') && (stackHead != NULL)) {
	discard = false;
	pop(stackHead, queueHead, queueTail, stackHead, stackHead, discard, size);
      }
      // Pop the left parenthesis and discard it
      discard = true;
      pop(stackHead, queueHead, queueTail, stackHead, stackHead, discard, size);
    }
  }

  // Pop the remaining operators left in the stack into the queue
  while (stackHead != NULL) {
    discard = false;
    pop(stackHead, queueHead, queueTail, stackHead, stackHead, discard, size);
  }

  Node* bStackHead = NULL;
  Node* rightNode = NULL;
  Node* leftNode = NULL;

  // Loop through the queue
  for (int i = 0; i < size+1; i++) {
    newNode = new Node(dequeue(queueHead)->getChar());
    // If token is a number, push to stack
    if (isdigit(newNode->getChar()) == true) {
      push(bStackHead, bStackHead, newNode);
    }
    // If token is an operator...
    else if ((newNode->getChar() == '+') ||
	     (newNode->getChar() == '-') ||
	     (newNode->getChar() == '*') ||
	     (newNode->getChar() == '/') ||
	     (newNode->getChar() == '^')) {
      // Pop the top two tokens off the stack, set them to the left and right nodes of the operator...
      rightNode = peekNode(bStackHead, bStackHead);
      newNode->setRight(rightNode);
      discard = true;
      pop(bStackHead, queueHead, queueTail, bStackHead, bStackHead, discard, size);
      leftNode = peekNode(bStackHead, bStackHead);
      newNode->setLeft(leftNode);
      pop(bStackHead, queueHead, queueTail, bStackHead, bStackHead, discard, size);
      // Then push the operator to the stack
      push(bStackHead, bStackHead, newNode);
    }
  }

  bool looping = true;
  // Prompt user for input on choice of output
  while (looping == true) {
    cout << endl << "Enter: INFIX, PREFIX, or POSTFIX" << endl;
    char input[50];
    cin.get(input, 50);
    cin.get();
    // Infix
    if (strcmp(input, "INFIX") == 0) {
      infix(bStackHead);
      cout << endl;
    }
    // Prefix
    else if (strcmp(input, "PREFIX") == 0) {
      prefix(bStackHead);
      cout << endl;
    }
    // Postfix
    else if (strcmp(input, "POSTFIX") == 0) {
      postfix(bStackHead);
      cout << endl;
    }
    else {
      cout << "Please enter a valid command." << endl;
    }
  }
}

// Push the token to the stack using recursion
void push(Node* &stackHead, Node* current, Node* newNode) {
  if (stackHead == NULL) {
    stackHead = newNode;
  }
  else if (current->getNext() != NULL) {
    // Recurse
    push(stackHead, current->getNext(), newNode);
  }
  else {
    current->setNext(newNode);
  }
}

// Pop the top of the stack off using recursion
void pop(Node* &stackHead, Node* &queueHead, Node* &queueTail, Node* current, Node* previous, bool discard, int &size) {
  if (stackHead == NULL) {
    //cout << "The stack is currently empty!" << endl;
  }
  else if (current->getNext() != NULL) {
    // Recurse
    pop(stackHead, queueHead, queueTail, current->getNext(), current, discard, size);
  }
  else if (current->getChar() == '(') {
    delete current;
    previous->setNext(NULL);
  }
  else {
    // If we don't discard, enqueue the token
    if (discard == false) {
      enqueue(queueHead, queueTail, queueHead, current, size);
    }
    if (current == stackHead) {
      stackHead = NULL;
    }
    previous->setNext(NULL);
  }
}

// Peek at the top of the stack using recursion
char peek(Node* stackHead) {
  if (stackHead == NULL) {
    //cout << "The stack is currently empty!" << endl;
  }
  else if (stackHead->getNext() != NULL) {
    // Recurse
    return(peek(stackHead->getNext()));
  }
  else if (stackHead->getNext() == NULL) {
    return (stackHead->getChar());
  }
  else {
    return '\n';
  }
  return '\n';
}

// Peek at the top of the stuck using recursion, but return a node instead of a character
Node* peekNode(Node* stackHead, Node* current) {
  if (stackHead == NULL) {
    return NULL;
  }
  else if (current->getNext() != NULL) {
    return(peekNode(stackHead, current->getNext()));
  }
  else if (current->getNext() == NULL) {
    return current;
  }
  else {
    return NULL;
  }
  return NULL;
}

// Print the stack using recursion (used solely for testing)
void printStack(Node* stackHead) {
  if (stackHead == NULL) {
    //cout << "empty stack" << endl;
  }
  else if (stackHead->getNext() != NULL) {
    cout << "printing: " << stackHead->getChar() << endl;
    // Recurse
    printStack(stackHead->getNext());
  }
  else {
    cout << "printing: " << stackHead->getChar() << endl << endl;
  }
}

// Print the queue using recursion (used solely for testing)
void printQueue(Node* queueHead) {
  if (queueHead == NULL) {
    //cout << "empty queue" << endl;
  }
  else if (queueHead->getNext() != NULL) {
    cout << "printing: " << queueHead->getChar() << endl;
    // Recurse
    printQueue(queueHead->getNext());
  }
  else {
    cout << "printing: " << queueHead->getChar() << endl << endl;
  }
}

// Add token to the end of the queue using recursion
void enqueue(Node* &queueHead, Node* &queueTail, Node* current, Node* newNode, int &size) {
  if (queueHead == NULL) {
    queueHead = newNode;
    queueTail = newNode;
  }
  else if (current->getNext() != NULL) {
    // Recurse
    enqueue(queueHead, queueTail, current->getNext(), newNode, size);
  }
  else {
    current->setNext(newNode);
    queueTail = newNode;
    // Add to the size variable each time enqueue is called. This variable will be used in a for loop 
    size++;
  }
}

// Remove token at the beginning of the queue
Node* dequeue(Node* &queueHead) {
  Node* temp = queueHead;
  queueHead = temp->getNext();
  return temp;
}

// Function to calculate the precedence of an operator
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

// A set of conditions that must be achieved for a specific action to occur in the shunting yard algorithm
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
    return true;
  }
  else {
    return false;
  }
}

// Print the expression in infix through recursion
void infix(Node* bStackHead) {
  if (bStackHead->getLeft() != NULL) {
    infix(bStackHead->getLeft());
  }
  cout << bStackHead->getChar();
  if (bStackHead->getRight() != NULL) {
    infix(bStackHead->getRight());
  }
  return;
}

// Print the expression in prefix through recursion
void prefix(Node* bStackHead) {
  cout << bStackHead->getChar();
  if (bStackHead->getLeft() != NULL) {
    prefix(bStackHead->getLeft());
  }
  if (bStackHead->getRight() != NULL) {
    prefix(bStackHead->getRight());
  }
  return;
}

// Print the expression in postfix through recursion
void postfix(Node* bStackHead) {
  if (bStackHead->getLeft() != NULL) {
    postfix(bStackHead->getLeft());
  }
  if (bStackHead->getRight() != NULL) {
    postfix(bStackHead->getRight());
  }
  cout << bStackHead->getChar();
  return;
}
