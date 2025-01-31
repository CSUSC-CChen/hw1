/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/

#include "split.h"
#include <iostream>

void print(Node* head){
  while (head!=nullptr){
    std::cout<<head->value<<"->";
    head = head->next;
  }
  std::cout<<"NULL"<<std::endl;
}
Node* arrtoll(int arr[],int size){
  if (size==0){
    return nullptr;}
    Node* head = new Node(arr[0],nullptr);
    Node* current = head;
    for (int i=1; i<size;i++){
      current->next = new Node(arr[i],nullptr);
      current = current->next;
    }
    return head;
}
void deletell(Node*& head){
  while (head!=nullptr){
    Node* temp=head;
    head=head->next;
    delete temp;
  }
}
int main(int argc, char* argv[])
{
  int arr[] = {1,3,4,6,8,10,13};
  int size =7;
  Node* list = arrtoll(arr,size);
  Node* odds = nullptr;
  Node* evens = nullptr;
  split(list,odds,evens);
  std::cout<<"Odds: ";
  print(odds);
  std::cout<<"Evens: ";
  print(evens);
  deletell(odds);
  deletell(evens);
}
