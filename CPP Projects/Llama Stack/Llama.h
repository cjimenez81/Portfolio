#ifndef _LLAMA_H_
#define _LLAMA_H_

/************************************************************
 File:    Llama.h
 Project: CMSC 341 Project 1, Fall 2016
 Author:  Chris Jimenez
 Date:    9/22/16
 Section: 03
 Email:   fp42134@umbc.edu

   This file contains the Llama class declaration. The Llama
 class uses a combination of arrays and linked list nodes,
 defined as the LlamaNode class, to form a templated data stack.

 ************************************************************/

#include <stdexcept>
#include <string>
#include "LlamaNode.h"

using namespace std ;


class LlamaUnderflow : public std::out_of_range {

 public:

 LlamaUnderflow(const string& what) : std::out_of_range(what) { }

} ;


template <class T, int LN_SIZE>
  class Llama {

 public:

  Llama() ;
  Llama(const Llama<T,LN_SIZE>& other) ;   // copy constructor
  ~Llama() ;



  //---------------------------------------------------------
  // Name: size
  // Pre-condition:  none
  // Post-condition: Returns the number of items in the stack
  //---------------------------------------------------------
  int size() ;

  //---------------------------------------------------------
  // Name: dump
  // Pre-condition:  none
  // Post-condition: This function helps with debugging. It
  // prints important information regarding the stack to cerr
  //---------------------------------------------------------
  void dump() ;

  //---------------------------------------------------------
  // Name: push
  // Pre-condition:  none
  // Post-condition: Adds a templated value to the top of the stack
  //---------------------------------------------------------
  void push(const T& data) ;

  //---------------------------------------------------------
  // Name: pop
  // Pre-condition:  there is at least one value in the stack
  // Post-condition: Removes and returns the top value in the stack
  //---------------------------------------------------------
  T pop() ;



  //---------------------------------------------------------
  // Name: dup
  // Pre-condition:  there is at least one value in the stack
  // Post-condition: Duplicates the top value in the stack
  //---------------------------------------------------------
  void dup() ;    //  (top) A B C D -> A A B C D

  //---------------------------------------------------------
  // Name: swap
  // Pre-condition:  there are at least 2 values in the stack
  // Post-condition: Switches the top 2 values in the stack
  //---------------------------------------------------------
  void swap() ;   //  (top) A B C D -> B A C D

  //---------------------------------------------------------
  // Name: rot
  // Pre-condition:  there are at least 3 values in the stack
  // Post-condition: Rotates the top 3 values in the stack (see below)
  //---------------------------------------------------------
  void rot() ;    //  (top) A B C D -> C A B D



  //---------------------------------------------------------
  // Name: peek
  // Pre-condition:  the offset is <= the total # of stack elements
  // Post-condition: Returns the value at the offset index(starting from the top)
  //---------------------------------------------------------
  T peek(int offset) const ;


  // overloaded assignment operator
  //
  const Llama<T,LN_SIZE>& operator=(const Llama<T,LN_SIZE>& rhs) ;


  //
  // Add your public member functions & public data mebers here:
  //

 private:

  //
  // Add your private member functions & private data mebers here:
  //

  int m_numInStack;  // Tracks the total # of elements in the Llama stack

  int m_numInNode;   // Tracks the total # of elements in the top node.
                     // Always resets to 0 with new node at top

  bool m_hasExtra;   // Tracks if there is an extra node or not

  LlamaNode<T, LN_SIZE> *stackHead;   // Pointer to the bottom node
  LlamaNode<T, LN_SIZE> *cursor;      // Pointer to the top node
  LlamaNode<T, LN_SIZE> *extraNode;   // Pointer to the extra node

} ;


#include "Llama.cpp"


#endif
