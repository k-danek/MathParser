#ifndef PARSER_H
#define PARSER_H

#include<nodes.h>

#include<string>
#include<cctype>
#include<stack>
#include<vector>
#include<unordered_map>
#include<iterator>

class Parser
{

  public:

    Parser() = default;
    ~Parser() = default;
 
    // Main method that constructs the tree from the 
    // algebraic expression.
    bool growTree(std::string& exprString);

    unique_ptr<Node> treeRoot;

    void printTree(const unique_ptr<Node>& root) const;

    void printNodes() const;
    void printChars() const;

    // evaluates the expression tree into a single number.
    double evaluateExpr(const unique_ptr<Node>& root) const;

  private:
    unique_ptr<Node> _tempLeft  = nullptr;
    unique_ptr<Node> _tempRight = nullptr;
    
    // nodes are in vector for easier printing of the values.
    std::vector<unique_ptr<Node>> nodeVec;
    std::stack<char> valueStack;

    // To enforce correct associativity.
    const std::unordered_map<char, char> _priority = {
      {')',0},
      {'+',1},
      {'-',1},
      {'/',2},
      {'*',2}
    };

    // Variable values are stored in this map.
    std::unordered_map<char,double> _variableMap;

    // Iterates through a string to get a number out, also modifies the iterator
    // to the first non-numeric character.
    double _getNumber(const std::string&     exprString,    
                      std::string::iterator& it) const;

    // Gets a priority of associativity for a char
    char _getPriority(char c);

    // A function with a dialog to fill numbers for algebraic terms.
    // The assumption is that variables are alphabetical chars.
    // Changes the entered string in the process.
    // Includes a dialog.
    void _fillUnknowns(std::string& exprString,
                       char         c);

    // Prompts user to fill a value for a variable.
    double _getVariable(const std::string& exprString,
                        char               c);
};

#endif
