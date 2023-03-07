#include <gtest/gtest.h>

#include "controller.h"
#include "model.h"
#include "stack.h"

TEST(ErrorTest, test1) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("(5.4.3+2)");
  std::string error = a.getError();
  if (error.empty() == 1 && polish.empty() == 0) {
    a.calulation(polish, 0);
    error = a.getError();
  }
  ASSERT_EQ(error, "Error 7: stop polish counting");
}

TEST(ErrorTest, test2) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("(5+4");
  std::string error = a.getError();
  ASSERT_EQ(error, "Error 2: incorrect bracket");
}

TEST(ErrorTest, test3) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("(fgdfgj(8))");
  std::string error = a.getError();
  ASSERT_EQ(error, "Error 3: incorrect symbol");
}

TEST(ErrorTest, test4) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("(5/+2)");
  std::string error = a.getError();
  ASSERT_EQ(error, "Error 4: more than one operator");
}

TEST(ErrorTest, test5) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("slrt(5)");
  std::string error = a.getError();
  ASSERT_EQ(error, "Error 5: incorrect function name");
}

TEST(ErrorTest, test6) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("38/mod5");
  std::string error = a.getError();
  ASSERT_EQ(error, "Error 6: incorrect mod function");
}

TEST(ErrorTest, test7) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("sin(7)cos(8)");
  std::string error = a.getError();
  if (error.empty() == 1 && polish.empty() == 0) {
    a.calulation(polish, 0);
    error = a.getError();
  }
  ASSERT_EQ(error, "Error 7: stop polish counting");
}

TEST(ErrorTest, test8) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("35+8-");
  std::string error = a.getError();
  if (error.empty() == 1 && polish.empty() == 0) {
    a.calulation(polish, 0);
    error = a.getError();
  }
  ASSERT_EQ(error, "Error 8: stop polish counting");
}
TEST(ErrorTest, test9) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("cos");
  std::string error = a.getError();
  ASSERT_EQ(error, "Error 9: is not enough operand for function");
}
TEST(ErrorTest, test10) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("2*3-.+6");
  std::string error = a.getError();
  ASSERT_EQ(error, "Error 1: incorect operand");
}
TEST(ErrorTest, test11) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("6mod*2");
  std::string error = a.getError();
  ASSERT_EQ(error, "Error 6: incorrect mod function");
}
TEST(EqualTest, test1) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish =
      a.parser("56+21-376+(56-22)-(13+10)+(-5)+(11+(7-(3+2)))");
  std::string error = a.getError();
  double res = 0;
  if (error.empty() == 1 && polish.empty() == 0) {
    res = a.calulation(polish, 0);
  }
  ASSERT_EQ(res, -280);
}
TEST(EqualTest, test2) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("5+3*sin(10)");
  std::string error = a.getError();
  double res = 0;
  if (error.empty() == 1 && polish.empty() == 0) {
    res = a.calulation(polish, 0);
  }
  ASSERT_NEAR(res, 3.3679366673319, 0.000000001);
}
TEST(EqualTest, test3) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("(15-5)mod(5^3)");
  std::string error = a.getError();
  double res = 0;
  if (error.empty() == 1 && polish.empty() == 0) {
    res = a.calulation(polish, 0);
  }
  ASSERT_EQ(res, 10);
}
TEST(EqualTest, test4) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("tan(10)+ln(4)-log(8)");
  std::string error = a.getError();
  double res = 0;
  if (error.empty() == 1 && polish.empty() == 0) {
    res = a.calulation(polish, 0);
  }
  ASSERT_NEAR(res, 1.131565201587, 0.000000001);
}
TEST(EqualTest, test5) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("+5+(+4)+x");
  std::string error = a.getError();
  double res = 0;
  if (error.empty() == 1 && polish.empty() == 0) {
    res = a.calulation(polish, 10);
  }
  ASSERT_EQ(res, 19);
}
TEST(EqualTest, test6) {
  Model model;
  Controller a(&model);
  std::list<std::string> polish = a.parser("acos-0.25");
  std::string error = a.getError();
  double res = 0;
  if (error.empty() == 1 && polish.empty() == 0) {
    res = a.calulation(polish, 10);
  }
  ASSERT_NEAR(res, 1.823476581937, 0.000000001);
}
int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
