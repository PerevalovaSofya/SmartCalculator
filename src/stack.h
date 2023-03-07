#ifndef SRC_STACK_H_
#define SRC_STACK_H_
#include <iostream>
template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  class Node {
   public:
    value_type _data;
    Node *_next;
    explicit Node(const_reference value) : _data(value), _next(nullptr) {}
  };
  stack();
  explicit stack(const stack &s);
  stack(stack &&s);
  ~stack();
  void clear();
  stack &operator=(stack &&s);
  stack &operator=(const stack &s);

  size_type size() { return _size; }
  // 1 = пустой, 0 = нет
  bool empty() { return size() > 0 ? 0 : 1; }

  void push(const_reference value);
  value_type pop();
  const_reference back();

 private:
  size_t _size;
  Node *_head;
};
#include "stack.inl"
#endif  // SRC_STACK_H_
