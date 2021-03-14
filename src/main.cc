#include<parser.h>
#include<string>
#include<iostream>

int main()
{

  std::string expr = "a+1.005+2+30.7*44.00+2+a";

  Parser parser;

  bool success = parser.growTree(expr);

  std::cout << "printing out the root:";

  parser.printTree(parser.treeRoot);

  std::cout << "finished:" << success << " value:"
            << std::get<char>(parser.treeRoot -> value) << "\n"
            << "calculation result: " << parser.evaluateExpr(parser.treeRoot) << "\n";

  std::cout << "\n";
}

