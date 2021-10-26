// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>

// doubly linked list class
template <typename T>
class TemplatedDLList {
public:
// doubly linked list node
  struct DLListNode {
    T obj;
    DLListNode *prev, *next;
    // constructor
    DLListNode(T e=T(), DLListNode *p=nullptr, DLListNode *n=nullptr): obj(e), prev(p), next(n) {}
  };
private:
  DLListNode header, trailer;
public:
  TemplatedDLList(void){
    header.next = &trailer;
    trailer.prev = &header;
  } // default constructor  

  TemplatedDLList(const TemplatedDLList<T>& dll)
  :header(), trailer(){
    //loop through list to copy onto current linked-list
    //pointer referencing first node of the inputList
    header.next = &trailer;
    trailer.prev = &header;
    const typename TemplatedDLList<T>::DLListNode* cursor = dll.first_node();
    while((cursor = cursor->next)) insert_last(cursor->prev->obj);
  } // copy constructor

  TemplatedDLList(TemplatedDLList<T>&& dll)
  : header(dll.header), trailer(dll.trailer){
    if(dll.is_empty()){
      header.next = &trailer;
      trailer.prev = &header;
      return;
    }
    header.next->prev = &header;
    trailer.prev->next = &trailer;
    dll.header.next = &dll.trailer;
    dll.trailer.prev = &dll.header;
  } // move constructor

  ~TemplatedDLList(){
    make_empty();
  } // destructor

  TemplatedDLList<T>& operator=(const TemplatedDLList<T>& dll){
    if(this != &dll){
      make_empty();
      header.next = &trailer;
      trailer.prev = &header;
      const typename TemplatedDLList<T>::DLListNode* cursor = dll.first_node();
      while((cursor = cursor->next)) insert_last(cursor->prev->obj);  
    }

    return *this;
  } // copy assignment operator

  TemplatedDLList<T>& operator=(TemplatedDLList<T>&& dll){
    if(this != &dll){
      make_empty();
      if(dll.is_empty()){
        header.next = &trailer;
        trailer.prev = &header;
        return *this;
      }
      header.next = dll.header.next;
      trailer.prev = dll.trailer.prev;
      header.next->prev = &header;
      trailer.prev->next = &trailer;
      dll.header.next = &dll.trailer;
      dll.trailer.prev = &dll.header;
    }
    return *this;
  } // move assignment operator

  // return the pointer to the first node
  DLListNode *first_node(void) const{
    return header.next;
  }

  // return the pointer to the trailer
  const DLListNode *after_last_node(void) const{
    return &trailer;
  }

  // return true if the list is empty
  bool is_empty(void) const{
    return header.next == &trailer;
  }

  T first(void) const{
    return first_node()->obj;
  } // return the first object

  T last(void) const{
    return after_last_node()->prev->obj;
  } // return the last object

  void insert_first(const T obj){
    insert_after(header,obj);  
  } // insert to the first node

  T remove_first(){
    return remove_after(header);
  } // remove the first node

  void insert_last(const T obj){
    insert_before(trailer,obj);
  } // insert to the last node

  T remove_last(){
    return remove_before(trailer);
  }

  void insert_after(DLListNode &p, const T obj){
    if(p.next != nullptr){
        DLListNode *newNode = new DLListNode;
        newNode->obj = obj;             //gives newNode a value
        newNode->next = p.next;         //gives newNode a next value
        newNode->prev = p.next->prev;   //gives newNode a prev value
        p.next->prev = newNode;        //gives the  a new prev value
        p.next = newNode;              //gives p a new next value
    }
  }

  void insert_before(DLListNode &p, const T obj){
    if(p.prev->prev == nullptr){
        insert_after(header, obj);
    }
    else if(p.prev == nullptr){
        throw "invalid argument";
    }
    else{
        insert_after(*p.prev,obj);
    }
  }

  T remove_after(DLListNode &p){
    if(this->is_empty()){
        throw "empty list, cannot remove any more elements";
    }
    else if(p.next == nullptr || p.next->next == nullptr){
        throw "cannot remove a nonexistent element";
    }
    else{
        DLListNode* tmp = p.next;
        p.next = p.next->next;
        p.next->prev = &p;
        auto output = tmp->obj;
        delete tmp;
        return output;
    }
  }

  T remove_before(DLListNode &p){
    if(this->is_empty()){
        throw "empty list, cannot remove any more elements";
    }
    else if(p.prev == nullptr || p.prev->prev == nullptr){
        throw "cannot remove a nonexistent element";
    }
    else{
        return remove_after(*p.prev->prev);
    }
  }
  
  void make_empty(void){
    DLListNode *prev_node, *node = header.next;
    while (!is_empty()) remove_last();
  }
};

// output operator
template <typename T>
std::ostream& operator<<(std::ostream& os, const TemplatedDLList<T>& dll){
  const auto *node = dll.first_node();
    while (node = node->next) os << node->prev->obj << ", ";
  return os;
}

#endif
