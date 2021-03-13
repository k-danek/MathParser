#ifndef NODES_H
#define NODES_H

#include <iostream>
#include <memory>

using std::unique_ptr;

struct Node
{
 
  Node(char value): value(value),
                    left(nullptr),
                    right(nullptr)
  {};

  Node(char               value,
       unique_ptr<Node>&  l,
       unique_ptr<Node>&  r
      ): value(value),
         left(std::move(l)),
         right(std::move(r))
  {};

  const char value;
  unique_ptr<Node> left;
  unique_ptr<Node> right;
};


#endif
