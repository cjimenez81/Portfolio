/************************************************************
 File:    Driver.cpp
 Project: CMSC 341 Project 1, Fall 2016
 Author:  Chris Jimenez
 Date:    9/22/16
 Section: 03
 Email:   fp42134@umbc.edu

   This file contains the main driver program for Project 1.
 

 ************************************************************/
#include <iostream>
#include <string>

#include "LlamaNode.h"
#include "Llama.h"

using namespace std;

int main() {

  //*********************************************************
  // INT Llama
  cout << "*********************************************************" << endl;
  cout << "INT Llama\n" << endl;

  Llama<int, 50> int1 = Llama<int, 50>();

  int i;

  // pushes 51 items, should create extra node with 1 value
  for (i = 1 ; i <= 51 ; i++) {
    int1.push(i);
    //cerr << "pushed " << i << endl;
  }
  cout << "total values pushed: " << (i - 1) << endl;

  int1.dump();

  // peek() test
  cout << "peek(0): " << int1.peek(0) << endl;
  cout << "peek(10): " << int1.peek(10) << endl;
  cout << "peek(21): " << int1.peek(21) << endl;
  cout << "peek(47): " << int1.peek(47) << endl;


  // removes 25 items from the stack, extra node should still exist
  int data;
  for (i = 0 ; i < 25 ; i++) {
    data = int1.pop();
    //cerr << "popped: " << data << endl;
  }
  cout << "\ntotal popped: " << i << endl;

  int1.dump();

  // pops one more item and should remove extra node
  data = int1.pop();
  int1.dump();
  
  
  //*********************************************************
  // STRING Llamas

  cout << "*********************************************************" << endl;
  cout << "STRING Llamas\n" << endl;

  Llama<string, 3> string1 = Llama<string, 3>();

  // Copy Constructor test
  //
  // this Llama will test dup()
  Llama<string, 3> stringDup = Llama<string, 3>(string1);

  // Assignment operator test
  //
  // this Llama will test swap()
  Llama<string, 3> stringSwap = Llama<string, 3>();
  stringSwap = string1;

  // Copy Constructor
  //
  // this Llama will test rot()
  Llama<string, 3> stringRot = Llama<string, 3>(string1);



  // pop LlamaUnderFlow test
  try {
  	string data2 = string1.pop();
	}
	catch(LlamaUnderflow popError) {
    cerr << popError.what() << endl;
  }
  data = 'a';


  cout <<"\n\n\n" << endl;

  // Duplicate:

  // dup() LlamaUnderFlow test
  try {
    stringDup.dup();
  }
  catch(LlamaUnderflow popError) {
    cerr << popError.what() << endl;
  }

  stringDup.push("A");
  stringDup.dup();
  cout << "\n\n----- stringDup dump -----" << endl;
  cout << "----- duplicate test -----" << endl;
  stringDup.dump();


  cout <<"\n\n\n" << endl;

  // Swap:

  stringSwap.push("B");

  // swap() LlamaUnderFlow test
  try {
    stringSwap.swap();
  }
  catch(LlamaUnderflow popError) {
    cerr << popError.what() << endl;
  }

  stringSwap.push("A");
  stringSwap.swap();
  cout << "\n\n----- stringSwap dump -----" << endl;
  cout << "-------  swap test  -------" << endl;
  stringSwap.dump();


  cout <<"\n\n\n" << endl;

  // Rotate:

  stringRot.push("C");
  stringRot.push("B");

  // rot() LlamaUnderFlow test
  try {
    stringRot.rot();
  }
  catch(LlamaUnderflow popError) {
    cerr << popError.what() << endl;
  }

  stringRot.push("A");
  stringRot.rot();
  cout << "\n\n----- stringRot dump -----" << endl;
  cout << "-----  rotate  test  -----" << endl;
  stringRot.dump();

  return 0;
}