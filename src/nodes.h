#ifndef NODES_H
#define NODES_H

#include <iostream>
#include <memory>

using std::unique_ptr;

// Base structure that should not be instantiated.
struct Node
{
  Node(){};

  Node(unique_ptr<Node>&  l,
       unique_ptr<Node>&  r
      ): left(std::move(l)),
         right(std::move(r))
  {};

  virtual ~Node(){};

  //const char value;
  unique_ptr<Node> left;
  unique_ptr<Node> right;
};

// Operator node, its value is char
struct OperNode: public Node
{
  OperNode(char               val,
           unique_ptr<Node>&  l,
           unique_ptr<Node>&  r
          ): value(val),
             left(std::move(l)),
             right(std::move(r))
  {};

  const char value;
  unique_ptr<Node> left;
  unique_ptr<Node> right;
};

// Operator node, its value is char
struct LeafNode: public Node
{
  LeafNode(char value): value(value),
                        left(nullptr),
                        right(nullptr)
  {};

  const double value;
  unique_ptr<Node> left;
  unique_ptr<Node> right;
};

#endif

