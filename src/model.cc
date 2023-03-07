#include "model.h"
/* -------------------------------Create_polish_notasion-------------------------------------*/
std::list<std::string> Model::create_polish_notation(const std::string &value) {
  str_value = value;
  replacement_unary();
  check_operator();
  check_bracket();
  check_mod();
  while (str_value.size() != 0 && _error == 0) {
    if (str_value[0] == ')' || str_value[0] == '(') {
      get_bracket();
    } else if (find_operand(str_value[0]) == 1 || str_value[0] == '.') {
      get_operand();
    } else if (find_operator(str_value[0]) == 1 ||
               find_unury(str_value[0]) == 1) {
      get_operator();
    } else if (str_value[0] == 'x') {
      std::string temp(1, 'x');
      polish_string.push_back(temp);
      str_value = str_value.substr(1);
    } else if (find_function(str_value[0]) == 1) {
      get_function();
    } else {
      _error = 3;
    }
  }
  while (stack_lexem.empty() == 0) {
    std::string temp(1, stack_lexem.pop());
    polish_string.push_back(temp);
  }
  return polish_string;
}
/* -------------------------------Get_method-------------------------------------*/
void Model::get_operand() {
  size_t count = 0;
  if ((str_value[0] == '.' && find_operand(str_value[1]) == 0)) {
    _error = 1;
  } else {
    double number = std::stod(str_value, &count);
    if (count > 0 && _error == 0) {
      polish_string.push_back(std::to_string(number));
      str_value = str_value.substr(count);
    }
  }
}

void Model::get_operator() {
  if (stack_lexem.empty() == 1) {
    stack_lexem.push(str_value[0]);
  } else {
    while (stack_lexem.empty() == 0 &&
           (priority(stack_lexem.back()) > priority(str_value[0]) ||
            (priority(stack_lexem.back()) == priority(str_value[0]) &&
             associativity(str_value[0]) == 0))) {
      std::string temp(1, stack_lexem.pop());
      polish_string.push_back(temp);
    }
    stack_lexem.push(str_value[0]);
  }
  str_value = str_value.substr(1);
}

void Model::get_bracket() {
  if (str_value[0] == '(') {
    stack_lexem.push(str_value[0]);
  } else {
    while (stack_lexem.empty() == 0 && stack_lexem.back() != '(') {
      std::string temp(1, stack_lexem.pop());
      polish_string.push_back(temp);
    }
    stack_lexem.pop();
  }
  str_value = str_value.substr(1);
}
void Model::get_function() {
  std::string funct_str = "sincotaqrlgmdup";
  size_t count = str_value.find_first_not_of(funct_str, 0);
  std::string function = str_value.substr(0, count);
  if (count > str_value.size()) _error = 9;
  check_function(function);
  if (_error == 0) {
    char small_fanct = 0;
    small_fanct = convert_funct(function);
    if (stack_lexem.empty() == 1) {
      stack_lexem.push(small_fanct);
    } else {
      while (stack_lexem.empty() == 0 &&
             (priority(stack_lexem.back()) > priority(small_fanct) ||
              (priority(stack_lexem.back()) == priority(small_fanct) &&
               associativity(small_fanct)))) {
        std::string temp(1, stack_lexem.pop());
        polish_string.push_back(temp);
      }
      stack_lexem.push(small_fanct);
    }
    str_value = str_value.substr(count);
  }
}

/* ---------------------------------Check_method-----------------------------------*/
void Model::check_function(std::string function) {
  std::set<std::string> control{"sin",  "cos",  "tan",  "b",  "p",
                                "asin", "acos", "atan", "k",  "u",
                                "ln",   "sqrt", "log",  "mod"};
  std::set<std::string>::iterator reply = control.find(function);
  if (reply == control.end()) _error = 5;
}
void Model::check_operator() {
  std::string::iterator it = str_value.begin();
  int count_oper = 0;
  for (; it != str_value.end() && count_oper < 2; ++it) {
    if (find_operator(*it) == 1) {
      ++count_oper;
    } else {
      count_oper = 0;
    }
  }
  if (count_oper == 2) _error = 4;
}
void Model::check_bracket() {
  std::string::iterator it = str_value.begin();
  int bracket_start = 0;
  int bracket_end = 0;

  for (; it != str_value.end() && bracket_start >= bracket_end; ++it) {
    if (*it == '(') ++bracket_start;
    if (*it == ')') ++bracket_end;
  }
  if (bracket_start != bracket_end) _error = 2;
}
void Model::check_mod() {
  if (str_value[0] == 'm' || str_value[(str_value.size() - 1)] == 'd') {
    _error = 6;
  } else {
    for (unsigned int i = 1; i < str_value.size(); i++) {
      if (str_value[i] == 'm' &&
          (str_value[i - 1] == '-' || str_value[i - 1] == '+' ||
           str_value[i - 1] == '*' || str_value[i - 1] == '/' ||
           str_value[i - 1] == 'u' || str_value[i - 1] == 'p' ||
           str_value[i - 1] == '(')) {
        _error = 6;
      }
      if (str_value[i] == 'd' &&
          (str_value[i + 1] == '-' || str_value[i + 1] == '+' ||
           str_value[i + 1] == '*' || str_value[i + 1] == '/' ||
           str_value[i + 1] == 'u' || str_value[i + 1] == 'p' ||
           str_value[i + 1] == ')')) {
        _error = 6;
      }
    }
  }
}
/* -------------------------------Find_method-------------------------------------*/
int Model::find_operator(char op) {
  int find = 0;
  if (op == '+' || op == '-' || op == '/' || op == '*' || op == '^') find = 1;
  return find;
}

int Model::find_operand(char op) {
  int find = 0;
  if ((op >= '0' && op <= '9')) find = 1;
  return find;
}
int Model::find_function(char op) {
  int find = 0;
  if (op == 's' || op == 'c' || op == 't' || op == 'a' || op == 'l' ||
      op == 'm')
    find = 1;
  return find;
}
int Model::find_unury(char op) {
  int find = 0;
  if (op == 'u' || op == 'p' || op == 'b' || op == 'k') find = 1;
  return find;
}

/* -------------------------------Priority-------------------------------------*/
int Model::priority(char op) {
  int rank = 0;
  if (op == 'k' || op == 'b') {
    rank = 5;
  } else if (op == 's' || op == 'c' || op == 't' || op == 'i' || op == 'o' ||
             op == 'a' || op == 'q' || op == 'n' || op == 'l') {
    rank = 4;
  } else if (op == '/' || op == '*' || op == 'm') {
    rank = 2;
  } else if (op == '^' || op == 'u' || op == 'p') {
    rank = 3;
  } else if (op == '-' || op == '+') {
    rank = 1;
  }
  return rank;
}

/* -------------------------------Associativity-------------------------------------*/
int Model::associativity(char op) {
  int rank = 0;
  if (op == 's' || op == 'c' || op == 't' || op == 'i' || op == 'o' ||
      op == 'a' || op == 'q' || op == 'n' || op == 'l' || op == 'k' ||
      op == 'b' || op == 'u' || op == 'p' || op == '^') {
    rank = 1;
  }
  return rank;
}

/* -------------------------------Convert_funct-------------------------------------*/
char Model::convert_funct(const std::string &function) {
  char small_fanct = '0';
  if ("sin" == function) small_fanct = 's';
  if ("cos" == function) small_fanct = 'c';
  if ("tan" == function) small_fanct = 't';
  if ("asin" == function) small_fanct = 'i';
  if ("acos" == function) small_fanct = 'o';
  if ("atan" == function) small_fanct = 'a';
  if ("sqrt" == function) small_fanct = 'q';
  if ("ln" == function) small_fanct = 'n';
  if ("log" == function) small_fanct = 'l';
  if ("mod" == function) small_fanct = 'm';
  if ("u" == function) small_fanct = 'u';
  if ("p" == function) small_fanct = 'p';
  if ("k" == function) small_fanct = 'k';
  if ("b" == function) small_fanct = 'b';
  return small_fanct;
}
/* -------------------------------Replacement_unary-------------------------------------*/
void Model::replacement_unary() {
  if (str_value[0] == '-') str_value[0] = 'u';
  if (str_value[0] == '+') str_value[0] = 'p';
  for (size_t i = 0; i < str_value.size(); i++) {
    if ((str_value[i] == '(') && str_value[i + 1] == '-')
      str_value[i + 1] = 'u';
    if ((str_value[i] == '(') && str_value[i + 1] == '+')
      str_value[i + 1] = 'p';
    if ((str_value[i] == 'n' || str_value[i] == 's' || str_value[i] == 'g' ||
         str_value[i] == 't' || str_value[i] == 'd') &&
        str_value[i + 1] == '-') {
      str_value[i + 1] = 'k';
    }
    if ((str_value[i] == 'n' || str_value[i] == 's' || str_value[i] == 'g' ||
         str_value[i] == 't' || str_value[i] == 'd') &&
        str_value[i + 1] == '+') {
      str_value[i + 1] = 'b';
    }
  }
}

/* -------------------------------Calculation_polish_notasion-------------------------------------*/
double Model::calculation_polish_notasion(
    const std::list<std::string> &polish_notasion, double double_variable) {
  double res = 0;
  polish_string = polish_notasion;
  while (polish_string.empty() == 0) {
    std::string buf = polish_string.front();
    if (find_operand(buf[0]) == 1) {
      stack_number.push(std::stod(buf));
    } else if (buf == "x") {
      stack_number.push(double_variable);
    } else {
      calculation_fanction(buf);
    }
    polish_string.pop_front();
  }
  if (_error == 0) res = stack_number.pop();
  if (stack_number.empty() == 0) {
    _error = 7;
    while (stack_number.empty() == 0) {
      stack_number.pop();
    }
  }

  return res;
}

void Model::calculation_fanction(std::string buf) {
  double res = 0;
  if (stack_number.empty() == 0) {
    double var1 = 0;
    var1 = stack_number.pop();
    if (find_operator(buf[0]) == 1 || buf[0] == 'm') {
      if (stack_number.empty() == 0) {
        double var2 = stack_number.pop();
        if (buf == "+") res = var2 + var1;
        if (buf == "-") res = var2 - var1;
        if (buf == "*") res = var2 * var1;
        if (buf == "/") res = var2 / var1;
        if (buf == "^") res = pow(var2, var1);
        if (buf == "m") res = fmod(var2, var1);
      } else {
        _error = 8;
      }
    } else {
      if (buf == "s") res = sin(var1);
      if (buf == "c") res = cos(var1);
      if (buf == "t") res = tan(var1);
      if (buf == "i") res = asin(var1);
      if (buf == "o") res = acos(var1);
      if (buf == "a") res = atan(var1);
      if (buf == "q") res = sqrt(var1);
      if (buf == "n") res = log(var1);
      if (buf == "l") res = log10(var1);
      if (buf == "p" || buf == "b") res = var1;
      if (buf == "u" || buf == "k") res = (-1) * var1;
    }
  } else {
    _error = 8;
  }
  if (_error == 0) stack_number.push(res);
}
