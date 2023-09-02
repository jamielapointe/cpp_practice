///\file linked_list.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief A linked list implementation
///\version 0.1
///\date 2023-08-03
///\details This shows examples of simple singly and doubly linked list
/// implementation as well as linked lists with sentinel nodes and dummy
/// pointers.  It also shows how to use a linked list to implement a stack and a
/// queue. \todo Add a circular linked list implementation.
///@copyright Copyright (c) 2023
///

#pragma once

#include <iostream>
#include <memory>
#include <ostream>

namespace cpp_practice::cpp_20::linked_list {

template <typename T>
concept Printable = requires(std::ostream& os, T t) {
  { os << t } -> std::convertible_to<std::ostream&>;
};

///\brief A simple singly linked list node
///\details This single linked list owns the next node.  It is not a sentinel
/// node and does not have a dummy pointer.
///\tparam T The type of data to store in the node; T must be printable (e.g.,
/// implement the << operator)
template <Printable T>
struct SinglyLinkedListNode {
  T data;
  std::unique_ptr<SinglyLinkedListNode<T>> next{nullptr};

  explicit SinglyLinkedListNode(T data_in) : data{data_in} {}
};

template <Printable T>
class SinglyLinkedList {
 public:
  template <Printable T1>
  friend std::ostream& operator<<(std::ostream& os,
                                  SinglyLinkedList<T1> const& list);
  void push(T data);
  void reverse();

 private:
  std::unique_ptr<SinglyLinkedListNode<T>> head{};
};

template <Printable T>
std::ostream& operator<<(std::ostream& os, SinglyLinkedList<T> const& list) {
  auto head = list.head.get();
  while (head != nullptr) {
    std::cout << head->data << std::endl;
    head = head->next.get();
  }
  return os;
}

template <Printable T>
void SinglyLinkedList<T>::push(T data) {
  auto temp = make_unique<SinglyLinkedListNode<T>>(data);
  if (head != nullptr) {
    temp->next = move(head);
    head = move(temp);
  } else {
    head = move(temp);
  }
}

template <Printable T>
void SinglyLinkedList<T>::reverse() {
  std::unique_ptr<SinglyLinkedListNode<T>> prev = nullptr;
  auto curr = move(head);
  while (curr != nullptr) {
    auto next_node = move(curr->next);
    curr->next = move(prev);
    prev = move(curr);
    curr = move(next_node);
  }
  head = move(prev);
}

template <typename T>
struct DoublyLinkedListNode {
  T data;
  std::unique_ptr<DoublyLinkedListNode<T>> next{nullptr};
  std::unique_ptr<DoublyLinkedListNode<T>> prev{nullptr};
  explicit DoublyLinkedListNode(T data_in) : data{data_in} {}
};

}  // namespace cpp_practice::cpp_20::linked_list
