
#include <stdexcept>
template <typename T>
stack<T>::stack() : _size(0), _head(nullptr) {}

template <typename T>
stack<T>::stack(const stack &s) : stack() {
  *this = s;
}
template <typename T>
stack<T> &stack<T>::operator=(const stack &s) {
  if (this == &s) {
    throw std::out_of_range("stacks is equal");
  }
  clear();
  Node *copy = s._head;
  for (size_t i = 1; i <= s._size; i++) {
    push(copy->_data);
    copy = copy->_next;
  }
  return *this;
}

template <typename T>
stack<T>::stack(stack &&l) : stack() {
  *this = std::move(l);
}

template <typename T>
stack<T> &stack<T>::operator=(stack &&l) {
  clear();
  swap(l);
  return *this;
}

template <typename T>
stack<T>::~stack() {
  clear();
}

template <typename T>
void stack<T>::clear() {
  Node *ptr = nullptr;
  while (empty() == 0) {
    ptr = _head;
    _head = _head->_next;
    delete ptr;
  }
  _head = nullptr;
  _size = 0;
}

template <typename T>
void stack<T>::push(const_reference value) {
  Node *n_node = new Node(value);
  if (empty() == 1) {
    _head = n_node;
  } else {
    n_node->_next = _head;
    _head = n_node;
  }
  ++_size;
}

template <typename T>
typename stack<T>::value_type stack<T>::pop() {
  if (empty() == 1) {
    throw std::out_of_range("list is empty - pop()");
  }
  value_type value = _head->_data;
  Node *ptr = _head;
  _head = ptr->_next;
  delete ptr;
  --_size;
  return value;
}

template <typename T>
typename stack<T>::const_reference stack<T>::back() {
  if (_size == 0) {
    throw std::out_of_range("list is empty - back()");
  }
  return _head->_data;
}
