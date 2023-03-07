#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include <iostream>
#include <map>
#include <string>

#include "model.h"

class Controller {
 public:
  Controller(Model *mod) : model(mod) {}
  std::list<std::string> parser(std::string str_value);
  double calulation(std::list<std::string> polish_notasion,
                    double double_variable);
  std::string getError() { return error_string; }

 private:
  std::string error_string;
  void setError(int error);
  Model *model;
  std::map<int, std::string> error_map{
      {1, "Error 1: incorect operand"},
      {2, "Error 2: incorrect bracket"},
      {3, "Error 3: incorrect symbol"},
      {4, "Error 4: more than one operator"},
      {5, "Error 5: incorrect function name"},
      {6, "Error 6: incorrect mod function"},
      {7, "Error 7: stop polish counting"},
      {8, "Error 8: stop polish counting"},
      {9, "Error 9: is not enough operand for function"}};
};

#endif  // SRC_CONTROLLER_H_
