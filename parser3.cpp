#include <stdio.h>

#include "ast.h"
#include "parser.h"

Status parse(const char * s, int expect)
{
  Tree_ptr tree = stmt(s);
  if (!tree || s[0] != ';')
  {
    return Status::SYNTAX_ERROR;
  }
  else if (interpret(std::move(tree)) == expect)
  {
    printTree(std::move(tree));
    return Status::OK;
  }
  else
  {
    return Status::WRONG_RESULT;
  }
}

Tree_ptr stmt(const char * &s)
{
  return add(s);
}

Tree_ptr add(const char * &s)
{
  Tree_ptr tree = mul(s);

  if (!tree)
  {
    return nullptr;
  }
  while (s[0] == '+' || s[0] == '-')
  {
    char operType = s[0];
    s++;
    Tree_ptr tree2= mul(s);
    if (!tree2)
    {
      return nullptr;
    }
    Tree_ptr tree3{ new Tree{std::move(tree), std::move(tree2), operType} };
    tree = std::move(tree3);
  }
  return tree;
}

Tree_ptr mul(const char * &s)
{
  Tree_ptr tree = prim(s);
  if (!tree)
  {
    return nullptr;
  }

  while (s[0] == '*' || s[0] == '/')
  {
    char operType = s[0];
    s++;
    Tree_ptr tree2 = prim(s);
    if (!tree2)
    {
      return nullptr;
    }
    Tree_ptr tree3{ new Tree {std::move(tree), std::move(tree2), operType} };
    tree = std::move(tree3);
  }
  return tree;
}

Tree_ptr prim(const char * &s)
{
  if (s[0] == '(')
  {
    s++;
    Tree_ptr tree = add(s);
    if (s[0] == ')')
    {
      s++;
      return tree;
    }
    else
    {
      return nullptr;
    }
  }
  else
  {
    return num(s);
  }
}

Tree_ptr num(const char * &s)
{
  if (s[0] >= '0' && s[0] <= '9')
  {
    Tree_ptr tree{ new Tree {s[0] - '0'} };
    s++;
    while (s[0] >= '0' && s[0] <= '9')
    {
      tree->value.number *= 10;
      tree->value.number += (s[0] - '0');
      s++;
    }
    return tree;
  }
  return nullptr;
}

