#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "ulliststr.h"

//Use this file to test your ulliststr implementation before running the test suite
void printList(ULListStr& list){
  for (size_t i=0; i<list.size();i++){
    std::cout<<list.get(i)<<" ";
  }
  std::cout<<"\n";
}
int main(int argc, char* argv[])
{
  ULListStr dat;
  dat.push_front("K");
  dat.push_back("F");
  dat.push_back("C");
  dat.push_back("I am hungry");
  printList(dat);
  std::cout<<dat.size()<<std::endl;
  std::cout<<dat.front()<<std::endl;//K
  std::cout<<dat.back()<<std::endl;
  dat.pop_back();
  dat.pop_front();
  printList(dat);
  dat.pop_back();
  printList(dat);
  dat.pop_front();
  printList(dat);
  std::cout<<dat.front()<<std::endl;
}
