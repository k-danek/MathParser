#ifndef NODES_H
#define NODES_H

#include <iostream>
#include <memory>
#include <variant>

using std::unique_ptr;

// Base structure that should not be instantiated.
struct Node
{
  Node() = default;
  ~Node() = default;

  // char version for operator nodes 
  Node(char               val, 
       unique_ptr<Node>&  l,
       unique_ptr<Node>&  r
      ): value(val),
         left(std::move(l)),
         right(std::move(r))
  {};

  // double version for leafs nodes
  Node(double val): value(val),
                    left(nullptr),
                    right(nullptr)
  {};

  const std::variant<char,double> value;
  unique_ptr<Node> left;
  unique_ptr<Node> right;
};

#endif

