#include<parser.h>

bool Parser::growTree(std::string& expr)
{
  //char priority = 0;

  std::cout << "Started growing a tree from: " << expr << "\n";

  for(std::string::iterator it = expr.begin(); it < expr.end(); ++it)
  {

    std::cout << "*read char:" << *it << "\n";

    if(isdigit(*it))
    {
      //_numbers.push_back(_getNumber(expr, it));

      //if(it >= expr.end())
      //{
      //  // The number reaches up till the end of the string.
      //  return true;
      //}

      //nodeStack.push(std::make_unique<Node>(*it));

      //std::cout << "**it was a digit, #nodes=" << nodeStack.size()
      //          << " node on top value= " << nodeStack.top()->value << "\n";

      nodeVec.push_back(std::make_unique<Node>(*it));

      std::cout << "**it was a digit, #nodes=" << nodeVec.size()
                << " node on top value= " << nodeVec.back()->value << "\n";

    }
    else if(*it == '(')
    {
      valueStack.push('(');
      std::cout << "**it was '(', #chars=" << valueStack.size() << "\n";

    }
    else
    {
      auto search = _priority.find(*it);
      if(search != _priority.end())
      {
        if(*it != ')')
        {

          std::cout << "**Before while:\n";
          std::cout << "***";  
          printChars();
          std::cout << "***";  
          printNodes();

          //priority = _getPriority(valueStack.top());       
          //priority = 0;

          while (!valueStack.empty() && valueStack.top() != '('
                 && _getPriority(valueStack.top()) >= search->second)
          {
 
             // // Get and remove the top element
             // // from the character stack
             // t = newNode(stC.top());
             // stC.pop();
 
             // // Get and remove the top element
             // // from the node stack
             // t1 = stN.top();
             // stN.pop();
 
             // // Get and remove the currently top
             // // element from the node stack
             // t2 = stN.top();
             // stN.pop();
 
             // // Update the tree
             // t->left = t2;
             // t->right = t1;
 
             // // Push the node to the node stack
             // stN.push(t);
            
             //_tempRight = std::move(nodeStack.top());
             //nodeStack.pop();               
             //
             //_tempLeft = std::move(nodeStack.top());
             //nodeStack.pop();
             
             _tempRight = std::move(nodeVec.back());
             nodeVec.pop_back();               
             
             _tempLeft = std::move(nodeVec.back());
             nodeVec.pop_back();

             unique_ptr<Node> t = std::make_unique<Node>(valueStack.top(),
                                                         _tempLeft,
                                                         _tempRight);
             
             valueStack.pop();
             nodeVec.push_back(std::move(t));
          
             std::cout << "|While loop ran|\n";
          }
          valueStack.push(*it);  

          //std::cout << "** it was an operation, #nodes=" << nodeStack.size()
          //          << ", #chars=" << valueStack.size() << ", current root value="
          //          << nodeStack.top()->value << "\n";
 
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
        else if(*it == ')')
        {
           while (!valueStack.empty() && valueStack.top() != '(') 
           {
               //t = newNode(stC.top());
               //stC.pop();
               //t1 = stN.top();
               //stN.pop();
               //t2 = stN.top();
               //stN.pop();
               //t->left = t2;
               //t->right = t1;
               // _tempRight = std::move(nodeStack.top());
               //nodeStack.pop();               
               //
               //_tempLeft = std::move(nodeStack.top());
               //nodeStack.pop();
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
           valueStack.pop();
           //std::cout << "** it was ')', #nodes=" << nodeStack.size()
           //          << ", #chars=" << valueStack.size() << ", current root value="
           //          << nodeStack.top()->value << "\n";

           std::cout << "** it was ')', #nodes=" << nodeVec.size()
                     << ", #chars=" << valueStack.size() << ", current root value="
                     << nodeVec.back()->value << "\n";

           std::cout << "***";  
           printChars();
           std::cout << "***";  
           printNodes();
 
        }
        else
        {
          std::cout << "Some weird shit has happened \n";
          return false;
        }
      }
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

