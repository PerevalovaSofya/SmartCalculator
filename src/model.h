#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <cmath>
#include <iostream>
#include <list>
#include <set>
#include <string>

#include "stack.h"
class Model {
 private:
  stack<char> stack_lexem;
  stack<double> stack_number;
  int _error;
  std::string str_value;
  std::list<std::string> polish_string;

  void check_operator();
  void check_bracket();
  void check_mod();
  void check_function(std::string function);

  void get_operand();
  void get_operator();
  void get_bracket();
  void get_function();

  int find_operator(char op);
  int find_function(char op);
  int find_operand(char op);
  int find_unury(char op);

  int priority(char op);
  int associativity(char op);
  char convert_funct(const std::string &function);
  void replacement_unary();
  void calculation_fanction(std::string buf);

 public:
  Model() : _error(0) {}
  std::list<std::string> create_polish_notation(const std::string &value);
  double calculation_polish_notasion(
      const std::list<std::string> &polish_notasion, double double_variable);
  int error() { return _error; }
};

#endif  // SRC_MODEL_H_
