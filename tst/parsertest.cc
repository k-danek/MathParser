#include "gtest/gtest.h"
#include <parser.h>

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <string>

const double eps = 1.0e-10;


TEST(parserEval, singleNumber)
{
  Parser parser;
  std::string expr = "1";
  
  ASSERT_TRUE(parser.growTree(expr));
  ASSERT_TRUE(parser.treeRoot);

  double result = parser.evaluateExpr(parser.treeRoot);

  EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST(parserEval, simpleAddition)
{
  Parser parser;
  std::string expr = "1+2";
  
  ASSERT_TRUE(parser.growTree(expr));
  ASSERT_TRUE(parser.treeRoot);

  double result = parser.evaluateExpr(parser.treeRoot);

  EXPECT_DOUBLE_EQ(result, 3.0);
}

TEST(parserEval, simpleBrackets)
{
  Parser parser;
  std::string expr = "(1+2)";
  
  ASSERT_TRUE(parser.growTree(expr));
  ASSERT_TRUE(parser.treeRoot);

  double result = parser.evaluateExpr(parser.treeRoot);

  EXPECT_DOUBLE_EQ(result, 3.0);
}


