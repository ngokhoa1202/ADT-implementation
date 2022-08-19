

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
#include "List.h"
#include <stdexcept>

template<class T>
class SinglyLinkedList : public List<T> {
private: // forward declaration
  class Node;
private:
  Node* head;
  Node* tail;
  int count;
  void checkIndex(const int& index, bool isAddFunc = false) const;
  Node* getNodeAt(int index) const;
  T removeAfter(Node*& curr);
  void addHead(const T& element); // add head when list has at least one ele
public:
  SinglyLinkedList(); // may be updated default arg: head, tail and count
  void add(const T& element); // add tail including empty list
  void addAt(int index, const T& element);
  int size() const;
  bool checkEmpty() const;
  T getAt(int index) const;
  void setAt(int index, const T& element);
  T operator [](int index) const;
  int indexOf(const T& item) const;
  bool contains(const T& item) const;
  T removeHead();
  T removeAt(int index);
  bool removeItem(const T& element);
  void clear();
  void getInfo() const;
  ~SinglyLinkedList();
private:
  class Node {
  public:
    T data;
    Node* next;
    explicit Node(const T& _data, Node* _next = NULL) : data(_data), next(_next) {}
  };
};

template<class T>
void SinglyLinkedList<T>::checkIndex(const int& index, bool isAddFunc) const {
  if (isAddFunc) {
    if (index < 0 || index > this->count)
      throw std::out_of_range("Index is out of range");
  }
  else if (index < 0 || index >= this->count)
    throw std::out_of_range("Index is out of range");
}

template<class T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::getNodeAt(int index) const {
  this->checkIndex(index);

  if (index == 0) return this->head;
  if (index == this->count-1) return this->tail;

  Node* curr = this->head;
  while (index > 0) {
    curr = curr->next;
    index--;
  }

  return curr;
}

template<class T>
T SinglyLinkedList<T>::removeAfter(Node*& curr) {
  Node* deletedNode = curr->next;
  curr->next = curr->next->next;

  if (deletedNode == this->tail) { // Delete the last element
    this->tail = curr;
  }

  T res = deletedNode->data;

  this->count--;
  delete deletedNode;
  return res;
}


template<class T>
void SinglyLinkedList<T>::addHead(const T& element) {
  this->head = new Node(element, this->head);
  this->count++;
}

template<class T>
T SinglyLinkedList<T>::removeHead() {
  T res = this->head->data;
  Node* deletedNode = this->head;

  if (this->count == 1) {
    this->head = this->tail = NULL;
  }
  else {
    this->head = this->head->next;
  }

  delete deletedNode;
  this->count--;

  return res;
}

template<class T>
SinglyLinkedList<T>::SinglyLinkedList() : head{NULL}, tail{NULL}, count{0} {}

template<class T>
void SinglyLinkedList<T>::add(const T& element) {
  if (this->checkEmpty()) {
    this->head = this->tail = new Node(element);
  }
  else {
    this->tail->next = new Node(element);
    this->tail = this->tail->next;
  }
  this->count++;
}

template<class T>
void SinglyLinkedList<T>::addAt(int index, const T& element) {
  this->checkIndex(index, true);

  if (index == this->count) { // Add at tail, we solve the case empty list in add tail func
    this->add(element);
  }
  else if (index == 0) { // Add at head, now that list has at least one ele
    this->addHead(element);
  }
  else { // Otherwise: add at middle
    Node* prev = this->getNodeAt(index-1);
    prev->next = new Node(element, prev->next);
    this->count++;
  }
}

template<class T>
int SinglyLinkedList<T>::size() const {
  return this->count;
}

template<class T>
bool SinglyLinkedList<T>::checkEmpty() const {
  return (this->head == NULL);
}

template<class T>
T SinglyLinkedList<T>::getAt(int index) const {
  this->checkIndex(index);

  if (index == 0) return this->head->data;
  if (index == this->count-1) return this->tail->data;
  
  return this->getNodeAt(index)->data;
}

template<class T>
void SinglyLinkedList<T>::setAt(int index, const T& element) {
  this->checkIndex(index);
  
  if (index == 0) {
    this->head->data = element;
    return;
  }
  if (index == this->count-1) {
    this->tail->data = element;
    return;
  }

  this->getNodeAt(index)->data = element;
}

template<class T>
T SinglyLinkedList<T>::operator [](int index) const {
  return this->getAt(index);
}

template<class T>
int SinglyLinkedList<T>::indexOf(const T& item) const {
  Node* curr = this->head;
  for (int i = 0; i < this->count; i++) {
    if (curr->data == item)
      return i;
    else curr = curr->next;
  }
  return -1;
}

template<class T>
bool SinglyLinkedList<T>::contains(const T& item) const {
  Node* curr = this->head;
  for (int i = 0; i < this->count; i++) {
    if (curr->data == item)
      return true;
    else curr = curr->next;
  }
  return false;
}

template<class T>
T SinglyLinkedList<T>::removeAt(int index) {
  this->checkIndex(index);

  if (index == 0) {
    return this->removeHead();
  }
  else {
    Node* prev = this->getNodeAt(index-1);
    return this->removeAfter(prev);
  }
}

template<class T>
bool SinglyLinkedList<T>::removeItem(const T& element) {
  if (this->checkEmpty()) return false;

  if (this->head->data == element) {
    this->removeHead();
    return true;
  }
  else {
    Node* prev = this->head;
    while (prev->next != NULL && prev->next->data != element) {
      prev = prev->next;
    }
    if (prev->next != NULL) {
      Node* deletedNode = prev->next;
      prev->next = prev->next->next;

      if (prev->next == NULL) {
        this->tail = prev;
      }
      this->count--;
      delete deletedNode;
      return true;
    }
  }

  return false;
}

template<class T>
void SinglyLinkedList<T>::clear() {
  Node* curr = this->head;
  while (curr != NULL) {
    Node* next = curr->next;
    delete curr;
    curr = next;
  }

  this->head = NULL;
  this->tail = NULL;
  this->count = 0;
}

template<class T>
void SinglyLinkedList<T>::getInfo() const {
  std::cout << "Size of list: " << this->count << '\n'
            << "Elements of list: ";

  Node* curr = this->head;
  for (int i = 0; i < this->count-1; ++i) {
    std::cout << curr->data << +"-->";
    curr = curr->next;
  }
  if (curr != NULL) {
    std::cout << curr->data << "\n\n";
  }
}

template<class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
  this->clear();
}


#endif //LIST_IMPLEMENTATION_BYARRAY_SINGLYLINKEDLISTIMPLEMENTATION_H
