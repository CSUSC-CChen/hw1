/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
// WRITE YOUR CODE HERE
  //base case
  if (in == NULL)
    return;
  //create a current node to track
  Node* current = in;
  //advance one step of in
  in = in->next;
  //detach current node from in
  current->next = NULL;

  //split
  if (current->value % 2 != 0){
    //move current to odds
    current->next = odds;
    //set odds' head to current
    odds = current;
  }
  //evens
  else{
    current->next = evens;
    evens = current;
  }

  //recursive step
  split(in,odds,evens);
}

/* If you needed a helper function, write it here */
