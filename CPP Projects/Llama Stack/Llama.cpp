#ifndef _LLAMA_CPP_
#define _LLAMA_CPP_

/************************************************************
 File:    Llama.cpp
 Project: CMSC 341 Project 1, Fall 2016
 Author:  Chris Jimenez
 Date:    9/22/16
 Section: 03
 Email:   fp42134@umbc.edu

   This file contains the Llama class definitions. The Llama
 class uses a combination of arrays and linked list nodes,
 defined as the LlamaNode class, to form a templated data stack.

 ************************************************************/

#include <stdexcept>
#include "Llama.h"
#include "LlamaNode.h"

using namespace std;


// Constructor
//
template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama() {

	// Allocate first node and set pointers
  stackHead = new LlamaNode<T, LN_SIZE>;
  cursor = stackHead;
  extraNode = NULL;

  m_numInStack = 0;
  m_numInNode = 0;
  m_hasExtra = false;

}

// Copy Constructor
//
template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama(const Llama<T,LN_SIZE>& other) {

	// Allocate first node and set pointers
  stackHead = new LlamaNode<T, LN_SIZE>;
  cursor = stackHead;
  extraNode = NULL;

  m_numInStack = 0;
  m_numInNode = 0;
  m_hasExtra = other.m_hasExtra;

  // Use peek() to push() every value from the other stack
  for (int i = other.m_numInStack - 1 ; i > -1 ; i--) {

    push(other.peek(i));

  }

  // Check for extra node in other stack, allocate one if true
  if (m_hasExtra) {
    extraNode = new LlamaNode<T, LN_SIZE>;
    extraNode->m_next = cursor;
  }

}

// Destructor
//
template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::~Llama() {

  LlamaNode<T, LN_SIZE> *current = cursor;
  LlamaNode<T, LN_SIZE> *temp;

  // Standard Liked List destruction
  while (current != NULL) {
    temp = current->m_next;
    delete current;
    current = temp;
  }

  // Check for extra
  if (m_hasExtra) { delete extraNode; }

  stackHead = NULL;
  cursor = NULL;
  extraNode = NULL;

  return;
}

// size()
//
// Returns the number of items in the stack
template <class T, int LN_SIZE>
int Llama<T, LN_SIZE>::size() { return m_numInStack; }

// dump()
//
// Prints important information regarding the stack to cerr
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dump() {

  cerr << "\n***** Llama Stack Dump *****\nLN_SIZE = " << LN_SIZE
       << "\n# of items in the stack = " << m_numInStack << endl;

  stackHead->report();


  if (m_hasExtra) {
    cerr << "\nThe stack has an extra node: " << extraNode << endl;
  } else {
    cerr << "\nThis stack does not have an extra node" << endl;
  }


  cerr << "\nStack contents, top to bottom" << endl;

  // print the top node
  cerr << "----- " << cursor << " -----" << endl;
  for (int i = m_numInNode - 1; i > -1; i--) {
    cerr << cursor->arr[i] << endl;
  }

  // Create helper pointer and print the other nodes if there's more than one
  LlamaNode<T, LN_SIZE> *current = cursor;

  if (current->m_next != NULL) {

    while(current->m_next != NULL) {
      current = current->m_next;
      cerr << "----- " << current << " -----" << endl;

      for (int i = LN_SIZE - 1; i > -1; i--) {
        cerr << current->arr[i] << endl;

      }
    }
  }

  cerr << "----- bottom of stack -----"
       << "\n\n*****************************" << endl;

  return;
}

// push()
//
// Adds a templated value to the top of the stack
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::push(const T& data) {

  // Check if the top node is full
  if (m_numInNode == LN_SIZE) {

  	LlamaNode<T, LN_SIZE> *temp = cursor;  // helper pointer

  	// If theres already an extra, push into the extra
    if (m_hasExtra) {

      temp = extraNode;
      cursor = temp;
      extraNode = NULL;
      m_hasExtra = false;
      m_numInNode = 0;

    } else {

      // Make a new node
      LlamaNode<T, LN_SIZE> *newNode = new LlamaNode<T, LN_SIZE>() ;

      // New nodes are added to the front of the list
      // as opposed to adding to the end like a normal list.
      // This allows for easier implementation of dump()
      newNode->m_next = temp;
      cursor = newNode;

      m_numInNode = 0;
    }
  }

  cursor->arr[m_numInNode] = data;

  m_numInNode++;
  m_numInStack++;

  return;
}

// pop()
//
// Removes and returns the top value in the stack
template <class T, int LN_SIZE>
T Llama<T, LN_SIZE>::pop() {

  if (m_numInStack == 0) {
    throw (LlamaUnderflow("Can't pop, stack is empty"));
  }

  // Store the value to be popped
  int index = m_numInNode - 1;
  T data = cursor->arr[index];

  // Check for extra node and delete if the # of elements
  // in the top node is <= half of LN_SIZE
  if ( (m_hasExtra) and ((m_numInNode - 1) <= (LN_SIZE / 2)) ) {

    delete extraNode;
    m_hasExtra = false;

  }

  // pop
  m_numInStack--;
  m_numInNode--;

  // After popping, check if node is empty and create
  // extra node if ture
  if (m_numInNode == 0) {
    extraNode = cursor;
    m_hasExtra = true;
    cursor = cursor->m_next;
    m_numInNode = LN_SIZE;
  }

  return data;
}

// dup()
//
// (top) A B C D -> A A B C D
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dup() {

  if (m_numInStack == 0) {
    throw(LlamaUnderflow("Can't duplicate, stack is empty"));
  }

  // Push the top element
  T data = cursor->arr[m_numInNode - 1];
  push(data);

  return;
}

// swap()
//
// (top) A B C D -> B A C D
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::swap() {

  if (m_numInStack < 2) {
    throw(LlamaUnderflow("Can't swap, need at least 2 elements"));
  }

  T temp;
  LlamaNode<T, LN_SIZE> *tempPtr = cursor->m_next; // helper pointer to next node down

  // Case: top two values are in different nodes
  if (m_numInNode == 1) {

  	// swap
    temp = cursor->arr[m_numInNode - 1];
    cursor->arr[m_numInNode - 1] = tempPtr->arr[LN_SIZE - 1];
    tempPtr->arr[LN_SIZE - 1] = temp;

    return;
  }

  // swap
  temp = cursor->arr[m_numInNode - 1];
  cursor->arr[m_numInNode - 1] = cursor->arr[m_numInNode - 2];
  cursor->arr[m_numInNode - 2] = temp;

  return;
}

// rot()
//
// (top) A B C D -> C A B D
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::rot() {

  if (m_numInStack < 3) {
    throw(LlamaUnderflow("Can't rotate, need at least 3 elements"));
  }

  T temp;
  LlamaNode<T, LN_SIZE> *tempPtr = cursor->m_next; // helper pointer to next node down

  // Case: 1 element in top node, 2 in next node
  if (m_numInNode == 1) {

  	// rotate
    temp = tempPtr->arr[LN_SIZE - 2];
    tempPtr->arr[LN_SIZE - 2] = tempPtr->arr[LN_SIZE - 1];
    tempPtr->arr[LN_SIZE - 1] = cursor->arr[m_numInNode - 1];
    cursor->arr[m_numInNode - 1] = temp;

    return;
  }

  // Case: 2 elements in top node, 1 in next node
  if (m_numInNode == 2) {

  	// rotate
    temp = tempPtr->arr[LN_SIZE - 1];
    tempPtr->arr[LN_SIZE - 1] = cursor->arr[m_numInNode - 2];
    cursor->arr[m_numInNode - 2] = cursor->arr[m_numInNode - 1];
    cursor->arr[m_numInNode - 1] = temp;

    return;
  }

  // Case: all 3 elements in top node
  // rotate
  temp = cursor->arr[m_numInNode - 3];
  cursor->arr[m_numInNode - 3] = cursor->arr[m_numInNode - 2];
  cursor->arr[m_numInNode - 2] = cursor->arr[m_numInNode - 1];
  cursor->arr[m_numInNode - 1] = temp;

  return;
}

// peek()
//
// Returns the value at the offset index(starting from the top)
template <class T, int LN_SIZE>
T Llama<T, LN_SIZE>::peek(int offset) const {

  if (offset > (m_numInStack - 1)) {
    throw (LlamaUnderflow("Offset too large"));
  }

  T data;

  // We already know where the top node is(cursor), so if the
  // offset wants a value in the the last node, this if block
  // will essentially short peek(), making it O(1) for this case.
  if (offset <= (m_numInNode - 1)) {

    data = cursor->arr[m_numInNode - offset - 1];
    return data;

  }

  // Same as above, except for values in stackHead
  if ((m_numInStack - offset) <= (LN_SIZE))  {

    data = stackHead->arr[m_numInStack - offset - 1];
    return data;

  }

  int nodeNumber = ((offset + 2) / LN_SIZE); // node index of the offset
  LlamaNode<T, LN_SIZE> *peeker;             // helper pointer
  int iterator = 0;                          // iterator for while loop

  peeker = cursor;

  // Traverse to the correct node
  while (iterator != nodeNumber) {

    peeker = peeker->m_next;
    iterator++;

  }

  int indexNumber = (m_numInStack - offset - 1) % LN_SIZE; // index in correct node

  data = peeker->arr[indexNumber];

  return data;
}

// Overloaded Assignment Operator
//
template <class T, int LN_SIZE>
const Llama<T,LN_SIZE>& Llama<T, LN_SIZE>::operator=(const Llama<T,LN_SIZE>& rhs) {


	// Copied from destructor...
  LlamaNode<T, LN_SIZE> *current = cursor;
  LlamaNode<T, LN_SIZE> *temp;

  // Standard Linked List destruction
  while (current != NULL) {
    temp = current->m_next;
    delete current;
    current = temp;
  }

  // Check for extra
  if (m_hasExtra) { delete extraNode; }

  stackHead = NULL;
  cursor = NULL;
  extraNode = NULL;


  // Copied from Copy Constructor...
  // Allocate first node and set pointers
  stackHead = new LlamaNode<T, LN_SIZE>;
  cursor = stackHead;
  extraNode = NULL;

  m_numInStack = 0;
  m_numInNode = 0;
  m_hasExtra = rhs.m_hasExtra;

  // Use peek() to push() every value from the rhs stack
  for (int i = rhs.m_numInStack - 1 ; i > -1 ; i--) {

    push(rhs.peek(i));

  }

  // Check for extra node in rhs stack, allocate one if true
  if (m_hasExtra) {
    extraNode = new LlamaNode<T, LN_SIZE>;
    extraNode->m_next = cursor;
  }


  return *this;
}

#endif
