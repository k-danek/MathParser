#include<parser.h>

bool Parser::growTree(std::string& expr)
{
  std::cout << "Started growing a tree from: " << expr << "\n";

  // Make sure the vectors, stacks and root are clean.
  nodeVec.clear();
  valueStack=std::stack<char>();
  treeRoot = nullptr;
  
  // Replaces variables with values
  // TODO: includes a bug while it does not replace all the instances
  //       of the variable.
  for(auto c: expr)
  {
    if(isalpha(c))
    {
      _fillUnknowns(expr, c);
    }  
  }

  for(std::string::iterator it = expr.begin(); it < expr.end(); ++it)
  {

    // Debugging output
    //std::cout << "*read char:" << *it << "\n";

    if(isdigit(*it))
    {
      
      // Beware! This function shifts the iterator to the first
      // non-number character.
      double leafValue = _getNumber(expr, it);

      nodeVec.push_back(std::make_unique<Node>(leafValue));

      // Patch the case when expression ends with a number
      std::string::iterator itp1 = it+1;
      if(itp1 == expr.end())
      {
        while(!valueStack.empty())
        {
          _tempRight = std::move(nodeVec.back());
          nodeVec.pop_back();               
          
          _tempLeft = std::move(nodeVec.back());
          nodeVec.pop_back();

          unique_ptr<Node> t = std::make_unique<Node>(valueStack.top(),
                                                          _tempLeft,
                                                          _tempRight);
          valueStack.pop();
          nodeVec.push_back(std::move(t));
        }
      }
    }
    else if(*it == '(')
    {
      valueStack.push('(');
      std::cout << "**it was '(', #chars=" << valueStack.size() << "\n";
    }
    else
    {
      {
        char priority = _getPriority(*it);

        while (!valueStack.empty() && valueStack.top() != '('
               && _getPriority(valueStack.top()) >= priority)
        {
           _tempRight = std::move(nodeVec.back());
           nodeVec.pop_back();               
           
           _tempLeft = std::move(nodeVec.back());
           nodeVec.pop_back();

           unique_ptr<Node> t = std::make_unique<Node>(valueStack.top(),
                                                       _tempLeft,
                                                       _tempRight);
           valueStack.pop();
           nodeVec.push_back(std::move(t));
        }
        
        if(*it == ')')
        {
          valueStack.pop();
        }
        else
        {
          valueStack.push(*it);  
        }

        // Debugging outputs
        //std::cout << "** it was an operation, #nodes=" << nodeVec.size()
        //          << ", #chars=" << valueStack.size();
       
        //std::cout << "***";  
        //printChars();
        //std::cout << "***";  
        //printNodes();

      }
    }
  }

  std::cout << "** finished with #nodes=" << nodeVec.size()
            << ", #chars=" << valueStack.size();
           
  //if(nodeVec.back())
  //{
  //  std::cout << ", current root value=" << nodeVec.back()->value << "\n";
  //}  
  //else
  //{
  //  std::cout << "\n" << "could not get the value on top\n";
  //}

  treeRoot = std::move(nodeVec.back());
           
  return true;
}

void Parser::printTree(const unique_ptr<Node>& root) const
{
  if (root) 
  {
      // value can be either char or double
      if(auto ptr = std::get_if<char>(&root->value))
      {
        std::cout << *ptr;
      }
      else if(auto ptr = std::get_if<double>(&root->value))
      {
        std::cout << *ptr;
      }
      std::cout << " ";  
      printTree(root->left);
      printTree(root->right);
  }
}

void Parser::printNodes() const
{
  
  std::cout << "Nodes: ";

  for(auto& node: nodeVec)
  {
    if(node)
    {
      // value can be either char or double
      if(auto ptr = std::get_if<char>(&node->value))
      {
        std::cout << *ptr;
      }
      else if(auto ptr = std::get_if<double>(&node->value))
      {
        std::cout << *ptr;
      }  

      std::cout << ", ";
    }    
    else
    {
      std::cout << "NULL, ";
    }
  }
  
  std::cout << "\n";
}

void Parser::printChars() const
{
  std::stack<char> valueCopy = valueStack;
  
  std::cout << "Values: ";
  while(!valueCopy.empty())
  {
    std::cout << valueCopy.top() << ", ";
    valueCopy.pop();
  }
  std::cout << "\n";
}

char Parser::_getPriority(char c)
{
  auto search = _priority.find(c);
  if(search != _priority.end())
  {
    return search->second;
  }
  else
  {
    return 0;
  }
}

double Parser::_getNumber(const std::string&     exprString,    
                          std::string::iterator& it) const
{
  //std::string numStr = std::string(it, exprString.end());
  std::string numStr = exprString.substr(it-exprString.begin());
  std::string::size_type endOfNumber;
  double num = std::stod(numStr, &endOfNumber);

  it = it + endOfNumber - 1;

  return num;
}

double Parser::evaluateExpr(const unique_ptr<Node>& root) const
{
  if(root) 
  {
      // value can be either char or double
      if(auto valPtr = std::get_if<char>(&root->value))
      {
        switch(*valPtr)
        {
          case '+':
            return evaluateExpr(root->left)+evaluateExpr(root->right);
            break;
          case '-':
            return evaluateExpr(root->left)-evaluateExpr(root->right);
            break;
          case '*':
            return evaluateExpr(root->left)*evaluateExpr(root->right);
            break;
          case '/':
            return evaluateExpr(root->left)/evaluateExpr(root->right);
            break;
        }
      }
      else if(auto valPtr = std::get_if<double>(&root->value))
      {
        return *valPtr;
      }
  }
  else
  {
    std::cout << "WARNING: Root not found!\n";
    return 0.0;
  }
}

void Parser::_fillUnknowns(std::string& exprString,
                           char         c)
{
  double value;
  std::string valueStr;

  std::cout << "\nUnknown variable found: " << c << "\n"
            << "Please fill in its numerical value:";

  std::cin >> valueStr;

  // User is free in input rubbish.
  try
  {
   value = std::stod(valueStr);
  }
  catch(const char* msg)
  {
    std::cout << msg << "\nPlease try again\n";
    _fillUnknowns(exprString, c);
  }

  // And going back to string for replacement.
  // Lazy formatting for a good measure.
  valueStr = std::to_string(value);

  std::cout << "Setting " << c << " = " << valueStr << "\n";   

  // TODO: rewrite so that position of the first instance would be known.
  std::string::size_type pos = 0; 
  // Replacing all the instances of the variable.
  while( (pos = exprString.find(c, pos)) != std::string::npos)
  {
    exprString.replace(pos, 1, valueStr);
    pos += valueStr.size();
  }

  std::cout << "The expr string is now: " << exprString << "\n";
}

