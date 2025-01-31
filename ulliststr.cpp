#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
/**
   * Adds a new value to the back of the list
   *   - MUST RUN in O(1)
   */
  void ULListStr::push_back(const std::string& val){
    //case1: if list is empty, create a new node as the new value, O(1)
    if (tail_ == NULL){
      tail_ = new Item();
      head_ = tail_;
      tail_->val[0] = val;
      //set first and last index
      tail_->first = 0;
      tail_->last = 1;
    }
    //case2: there is at least one space in the last array, add to that array, O(1)
    else if (tail_->last < ARRSIZE)//EXCLUSIVE!!!
    {
      //set the last index new value
      tail_->val[tail_->last] = val;
      //update last idx
      tail_->last++;
    }
    //case3: no space, need a new array like case1, O(1)
    else{
      Item* newItem = new Item();
      //same setup as case1
      newItem->val[0] = val;
      newItem->first = 0;
      newItem->last = 1;
      //update newItem's prev
      newItem->prev = tail_;
      tail_->next = newItem;
      tail_ = newItem;
    }
    //update size, O(1)
    size_++;
  }

  /**
   * Removes a value from the back of the list
   *   - MUST RUN in O(1)
   */
  void ULListStr::pop_back(){
    //case1: already empty
    if (empty()) throw std::invalid_argument("Empty list");
    //case2: More than one value in last array, remove the last value, O(1)
    if (tail_->last - tail_->first > 1)
      tail_->last--;
    //case3: Only 1 value, just delete last array, O(1)
    else{
      Item* temp = tail_;
      tail_ = tail_->prev;//update tail to prev node
      //check for edge case: only one element in whole list
      if (tail_ != NULL){
        tail_->next = NULL;
      }
      //empty: head and tail both null
      else head_ = NULL;
      delete temp;
    }
    //update size, O(1)
    size_--;
  }
  
  /**
   * Adds a new value to the front of the list.
   * If there is room before the 'first' value in
   * the head node add it there, otherwise, 
   * allocate a new head node.
   *   - MUST RUN in O(1)
   */
  void ULListStr::push_front(const std::string& val){
    //overall reversed logic of push_back
    //case1: if list is empty, create a new node as the new value, O(1)
    if (head_ == NULL){
      head_ = new Item();
      tail_ = head_;
      head_->val[ARRSIZE-1] = val;
      //set first and last index
      head_->first = ARRSIZE-1;
      head_->last = ARRSIZE;
    }
    //case2: there is at least one space in the first array, add to that array, O(1)
    else if (head_->first > 0)
    {
      //set the first idx-1 new value, cuz inclusive
      head_->val[head_->first-1] = val;
      //update first idx
      head_->first--;
    }
    //case3: no space, need a new array like case1, O(1)
    else{
      Item* newItem = new Item();
      //same setup as case1
      newItem->val[ARRSIZE-1] = val;
      newItem->first = ARRSIZE-1;
      newItem->last = ARRSIZE;
      //update newItem's next
      newItem->next = head_;
      head_->prev = newItem;
      head_ = newItem;
    }
    //update size, O(1)
    size_++;
  }

  /**
   * Removes a value from the front of the list
   *   - MUST RUN in O(1)
   */
  void ULListStr::pop_front(){
    //overall reversed logic of pop_back
    //case1: already empty
    if (empty()) throw std::invalid_argument("Empty list");
    //case2: More than one value in first array, remove the first value, O(1)
    if (head_->last - head_->first > 1)
      head_->first++;
    //case3: Only 1 value, just delete first array, O(1)
    else{
      Item* temp = head_;
      head_ = head_->next;//update head to next node
      //check for edge case: only one element in whole list
      if (head_ != NULL){
        head_->prev = NULL;
      }
      //empty: head and tail both null
      else tail_ = NULL;
      delete temp;
    }
    //update size, O(1)
    size_--;
  }
  
  /**
   * Returns a const reference to the back element
   *   - MUST RUN in O(1)
   */
  std::string const & ULListStr::back() const{
    //case1: already empty
    if (empty()) throw std::invalid_argument("Empty list");
    else return tail_->val[tail_->last - 1];//return last element of last array, O(1)
    //LAST IS EXCLUSIVE!!!
  }

  /**
   * Returns a const reference to the front element
   *   - MUST RUN in O(1)
   */
  std::string const & ULListStr::front() const{
    //case1: already empty
    if (empty()) throw std::invalid_argument("Empty list");
    else return head_->val[head_->first];//return first element of first array, O(1)
    //FIRST IS INCLUSIVE!!!
  }
  /** 
   * Returns a pointer to the item at index, loc,
   *  if loc is valid and NULL otherwise
   *   - MUST RUN in O(n) 
   */
  std::string* ULListStr::getValAtLoc(size_t loc) const{
    //check if loc is valid
    if (loc >= size_) return NULL;
    Item* current = head_;
    size_t count = 0; //track how many values have been traversed
    while (current!=NULL){//O(n)
      //calculate # of values of current node, O(1)
      size_t numValues = current->last - current->first;
      //check if exceeding loc using count n # of elements,O(1)
      if (count + numValues > loc)
        //exceeding means loc is inside current node
        return &(current->val[current->first +(loc-count)]);
      //if not,continue finding
      //add # of current node to count
      count += numValues;
      //proceed to next node
      current = current->next;
    }
    return NULL;
  }

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
