#include "controller.h"

std::list<std::string> Controller::parser(std::string str_value) {
  error_string.clear();
  std::list<std::string> polish_notasion;

  polish_notasion = model->create_polish_notation(str_value);
  if (model->error() > 0) {
    polish_notasion.clear();
    setError(model->error());
  }
  return polish_notasion;
}

double Controller::calulation(std::list<std::string> polish_notasion,
                              double double_variable) {
  double answer = 0;
  if (polish_notasion.empty() == 0) {
    answer =
        model->calculation_polish_notasion(polish_notasion, double_variable);
    if (model->error() > 0) {
      setError(model->error());
    }
  }
  return answer;
}

void Controller::setError(int error) {
  std::map<int, std::string>::iterator it = error_map.find(error);
  if (it != error_map.end()) {
    error_string = it->second;
  }
}
