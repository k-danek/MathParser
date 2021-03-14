#include<parser.h>
#include<string>
#include<iostream>

int main()
{


  std::string expr = "(1+2+3*4)";

  Parser parser;

  bool success = parser.growTree(expr);

  std::cout << "finished:" << success << " value:"
            << parser.treeRoot -> value << "\n";

  std::cout << "printing out the root:";

  parser.printTree(parser.treeRoot);

  std::cout << "\n";
}

