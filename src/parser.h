#ifndef PARSER_H
#define PARSER_H

#include<nodes.h>

#include<string>
#include<ctype.h>
#include<stack>
#include<vector>
#include<unordered_map>


class Parser
{

  public:

    Parser() = default;
    ~Parser() = default;
    
    bool growTree(std::string& exprString);
    //unique_ptr<Node> growTree(std::string& exprString);

    unique_ptr<Node> treeRoot;

    void printTree(const unique_ptr<Node>& root) const;
    void printNodes() const;
    void printChars() const;


  private:
    //ExprTree _exprTree;
    unique_ptr<Node> _tempLeft  = nullptr;
    unique_ptr<Node> _tempRight = nullptr;
    std::stack<unique_ptr<Node>> nodeStack;
    std::vector<unique_ptr<Node>> nodeVec;
    // Stack of nodes, not pointers to nodes;
    //std::stack<Node> nodeStack;
    std::stack<char> valueStack;

    // To enforce correct associativity.
    const std::unordered_map<char, char> _priority = {
      {')',0},
      {'+',1},
      {'-',1},
      {'/',2},
      {'*',2}
    };

    // Iterates through a string to get a number out, also modifies the iterator
    // to the first non-numeric character.
    double _getNumber(std::string&           exprString,    
                      std::string::iterator& it) const;

    // Gets a priority of associativity for a char
    char _getPriority(char c);
};

#endif
