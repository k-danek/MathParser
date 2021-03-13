#include<parser.h>

bool Parser::growTree(std::string& expr)
{
  char priority = 0;

  for(std::string::iterator it = expr.begin(); it < expr.end(); ++it)
  {
    if(isdigit(*it))
    {
      //_numbers.push_back(_getNumber(expr, it));

      //if(it >= expr.end())
      //{
      //  // The number reaches up till the end of the string.
      //  return true;
      //}

      nodeStack.push(std::make_unique<Node>(*it));
    }
    else if(*it == '(')
    {
      valueStack.push('(');
    }
    else
    {
      auto search = _priority.find(*it);
      if(search != _priority.end())
      {
        if(*it != ')')
        {

          while (!valueStack.empty() && valueStack.top() != '('
                 && priority >= search->second)
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
             
            
             _tempRight = std::move(nodeStack.top());
             nodeStack.pop();               
             
             _tempLeft = std::move(nodeStack.top());
             nodeStack.pop();

             unique_ptr<Node> t = std::make_unique<Node>(valueStack.top(),
                                                         _tempLeft,
                                                         _tempRight);
             valueStack.pop();
             nodeStack.push(std::move(t));
          }
          valueStack.push(*it);  
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
                _tempRight = std::move(nodeStack.top());
               nodeStack.pop();               
               
               _tempLeft = std::move(nodeStack.top());
               nodeStack.pop();

               unique_ptr<Node> t = std::make_unique<Node>(valueStack.top(),
                                                           _tempLeft,
                                                           _tempRight);
               valueStack.pop();
               nodeStack.push(std::move(t));
            
           }
           valueStack.pop();
        }
        else
        {
          std::cout << "Some weird shit has happened \n";
          return false;
        }
      }
    }

  }

  treeRoot = std::move(nodeStack.top());

  return true;

}
