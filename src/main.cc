#include<parser.h>
#include<string>
#include<iostream>

int main()
{
  std::string expr = "1+2+3*4";

  Parser prsr;

  bool success = prsr.growTree(expr);

  std::cout << "finished:" << success << " value:"
            << prsr.treeRoot -> value << "\n";

}

