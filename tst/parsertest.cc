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

TEST(parserEval, simpleSubstraction)
{
  Parser parser;
  std::string expr = "1-2";
  
  ASSERT_TRUE(parser.growTree(expr));
  ASSERT_TRUE(parser.treeRoot);

  double result = parser.evaluateExpr(parser.treeRoot);

  EXPECT_DOUBLE_EQ(result, -1.0);
}

TEST(parserEval, simpleMultiplication)
{
  Parser parser;
  std::string expr = "1*2";
  
  ASSERT_TRUE(parser.growTree(expr));
  ASSERT_TRUE(parser.treeRoot);

  double result = parser.evaluateExpr(parser.treeRoot);

  EXPECT_DOUBLE_EQ(result, 2.0);
}

TEST(parserEval, simpleDivision)
{
  Parser parser;
  std::string expr = "1/2";
  
  ASSERT_TRUE(parser.growTree(expr));
  ASSERT_TRUE(parser.treeRoot);

  double result = parser.evaluateExpr(parser.treeRoot);

  EXPECT_DOUBLE_EQ(result, 0.5);
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

TEST(parserEval, complexBracket)
{
  Parser parser;
  std::string expr = "(1+2)*(3-2)-((4))/(11-12)";
  
  ASSERT_TRUE(parser.growTree(expr));
  ASSERT_TRUE(parser.treeRoot);

  double result = parser.evaluateExpr(parser.treeRoot);

  EXPECT_DOUBLE_EQ(result, -1.0);
}

TEST(parserEval, numAtTheEnd)
{
  Parser parser;
  std::string expr = "(1+2)*(3-2)-4";
  
  ASSERT_TRUE(parser.growTree(expr));
  ASSERT_TRUE(parser.treeRoot);

  double result = parser.evaluateExpr(parser.treeRoot);

  EXPECT_DOUBLE_EQ(result, -1.0);
}
