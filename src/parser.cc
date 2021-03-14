#include<parser.h>

bool Parser::growTree(std::string& expr)
{
  std::cout << "Started growing a tree from: " << expr << "\n";

  for(std::string::iterator it = expr.begin(); it < expr.end(); ++it)
  {

    std::cout << "*read char:" << *it << "\n";

    // Dirty hack how to handle missing closing bracket
    //if(it == expr.end())
    //{
    //  *it = ')';
    //  if(valueStack.empty())
    //  {
    //    valueStack.push('(');
    //  } 
    //}

    if(isdigit(*it))
    {
      //nodeStack.push(std::make_unique<Node>(*it));

      //std::cout << "**it was a digit, #nodes=" << nodeStack.size()
      //          << " node on top value= " << nodeStack.top()->value << "\n";

      nodeVec.push_back(std::make_unique<Node>(*it));

      std::cout << "**it was a digit, #nodes=" << nodeVec.size()
                << " node on top value= " << nodeVec.back()->value << "\n";

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
        //if(*it != ')')
        {

          std::cout << "**Before while:\n";
          std::cout << "***";  
          printChars();
          std::cout << "***";  
          printNodes();

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

          std::cout << "** it was an operation, #nodes=" << nodeVec.size()
                    << ", #chars=" << valueStack.size();
         
          if(nodeVec.back())
          {
            std::cout << ", current root value=" << nodeVec.back()->value << "\n";
          }
          else
          {
            std::cout << ", current root value=NULL" << "\n";
          }

          std::cout << "***";  
          printChars();
          std::cout << "***";  
          printNodes();

        }
        //else if(*it == ')')
        //{
        //   while (!valueStack.empty() && valueStack.top() != '(') 
        //   {

        //       _tempRight = std::move(nodeVec.back());
        //       nodeVec.pop_back();               
        //       
        //       _tempLeft = std::move(nodeVec.back());
        //       nodeVec.pop_back();

        //       unique_ptr<Node> t = std::make_unique<Node>(valueStack.top(),
        //                                                   _tempLeft,
        //                                                   _tempRight);
        //       valueStack.pop();
        //       nodeVec.push_back(std::move(t));
        //    
        //   }
        //   valueStack.pop();

        //   std::cout << "** it was ')', #nodes=" << nodeVec.size()
        //             << ", #chars=" << valueStack.size() << ", current root value="
        //             << nodeVec.back()->value << "\n";

        //   std::cout << "***";  
        //   printChars();
        //   std::cout << "***";  
        //   printNodes();
 
        //}
        //else
        //{
        //  std::cout << "Some weird shit has happened \n";
        //  return false;
        //}
    }
  }

  std::cout << "** finished with #nodes=" << nodeVec.size()
            << ", #chars=" << valueStack.size();
           
  if(nodeVec.back())
  {
    std::cout << ", current root value=" << nodeVec.back()->value << "\n";
  }  
  else
  {
    std::cout << "\n" << "could not get the value on top\n";
  }

  treeRoot = std::move(nodeVec.back());
           
  return true;
}

void Parser::printTree(const unique_ptr<Node>& root) const
{

  if (root) 
  {
      std::cout << root->value;
      printTree(root->left);
      printTree(root->right);
      //std::cout << root->value;
  }

}

void Parser::printNodes() const
{
  
  std::cout << "Nodes: ";

  for(auto& node: nodeVec)
  {
    if(node)
    {
      std::cout << node->value << ", ";
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

