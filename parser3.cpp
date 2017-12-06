#include <stdio.h>

#include "ast.h"
#include "parser.h"

Status parse(const char * s, int expect)
{
  std::shared_ptr<Tree> tree = stmt(s);
  if (!tree || s[0] != ';')
  {
    return Status::SYNTAX_ERROR;
  }
  else if (interpret(tree) == expect)
  {
    printTree(tree);
    return Status::OK;
  }
  else
  {
    return Status::WRONG_RESULT;
  }
}

std::shared_ptr<Tree> stmt(const char * &s)
{
  return add(s);
}

std::shared_ptr<Tree> add(const char * &s)
{
  std::shared_ptr<Tree> tree = mul(s);

  if (!tree)
  {
    return nullptr;
  }
  while (s[0] == '+' || s[0] == '-')
  {
    char operType = s[0];
    s++;
    std::shared_ptr<Tree> tree2{ mul(s) };
    if (!tree2)
    {
      return nullptr;
    }
    std::shared_ptr<Tree> tree3{ new Tree{ tree, tree2, operType } };
    tree = tree3;
  }
  return tree;
}

std::shared_ptr<Tree> mul(const char * &s)
{
  std::shared_ptr<Tree> tree = prim(s);
  if (!tree)
  {
    return nullptr;
  }

  while (s[0] == '*' || s[0] == '/')
  {
    char operType = s[0];
    s++;
    std::shared_ptr<Tree> tree2{ prim(s) };
    if (!tree2)
    {
      return nullptr;
    }
    std::shared_ptr<Tree> tree3{ new Tree{ tree, tree2, operType } };
    tree = tree3;
  }
  return tree;
}

std::shared_ptr<Tree> prim(const char * &s)
{
  if (s[0] == '(')
  {
    s++;
    std::shared_ptr<Tree> tree = add(s);
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

std::shared_ptr<Tree> num(const char * &s)
{
  if (s[0] >= '0' && s[0] <= '9')
  {
    std::shared_ptr<Tree> tree{ new Tree{ s[0] - '0' } };
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

