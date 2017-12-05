#include <stdio.h>
#include <assert.h>

#include "ast.h"
#include "parser.h"

Status parse(const char * s, int expect)
{
  Tree * tree = stmt(s);
  if (!tree || s[0] != ';')
  {
    clearTree(tree);
    return Status::SYNTAX_ERROR;
  }
  else if (interpret(tree) == expect)
  {
    printTree(tree);
    clearTree(tree);
    return Status::OK;
  }
  else
  {
    clearTree(tree);
    return Status::WRONG_RESULT;
  }
}

Tree * stmt(const char * &s)
{
  return add(s);
}

Tree * add(const char * &s)
{
  Tree * tree = mul(s);
  if (!tree)
  {
    return nullptr;
  }
  while (s[0] == '+' || s[0] == '-')
  {
    char operType = s[0];
    s++;
    Tree * tree2 = mul(s);
    if (!tree2)
    {
      return nullptr;
    }
    tree = new Tree{ tree, tree2, operType };
  }
  return tree;
}

Tree * mul(const char * &s)
{
  Tree * tree = prim(s);
  if (!tree)
  {
    return nullptr;
  }

  while (s[0] == '*' || s[0] == '/')
  {
    char operType = s[0];
    s++;
    Tree * tree2 = prim(s);
    if (!tree2)
    {
      return nullptr;
    }
    tree = new Tree{ tree, tree2, operType };
  }
  return tree;
}

Tree * prim(const char * &s)
{
  if (s[0] == '(')
  {
    s++;
    Tree * tree = add(s);
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

Tree * num(const char * &s)
{
  if (s[0] >= '0' && s[0] <= '9')
  {
    Tree * tree = new Tree{ s[0] - '0' };
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

void run_asserts()
{
  assert(parse("1;", 1) == Status::OK);
  assert(parse("1+2;", 3) == Status::OK);
  assert(parse("1+2+3;", 6) == Status::OK);
  assert(parse("1+2+3+4;", 10) == Status::OK);

  assert(parse("1++;", 1) == Status::SYNTAX_ERROR);

  assert(parse("1;", 1) == Status::OK);
  assert(parse("1-2;", -1) == Status::OK);
  assert(parse("1-2-3;", -4) == Status::OK);
  assert(parse("1-2-3-4;", -8) == Status::OK);

  assert(parse("9*1;", 9) == Status::OK);
  assert(parse("9*1*3;", 27) == Status::OK);
  assert(parse("1*2*3*4;", 24) == Status::OK);

  assert(parse("2/1;", 2) == Status::OK);
  assert(parse("5/2/1;", 2) == Status::OK);
  assert(parse("9/2/3;", 1) == Status::OK);

  assert(parse("9/1/3;", 1) == Status::WRONG_RESULT);
  assert(parse("9/2/1/1;", 2) == Status::WRONG_RESULT);

  assert(parse("/1/3;", 1) == Status::SYNTAX_ERROR);
  assert(parse("9//3;", 1) == Status::SYNTAX_ERROR);
  assert(parse("9/1/;", 1) == Status::SYNTAX_ERROR);

  assert(parse("(1-2)-(3-4);", 0) == Status::OK);
  assert(parse("(1-2)-(3+4);", -8) == Status::OK);
  assert(parse("(1-2)+(3-4);", -2) == Status::OK);
  assert(parse("(1+2)-(3+4);", -4) == Status::OK);
  assert(parse("(1-2)-(3-4)-(5-6);", 1) == Status::OK);

  assert(parse("((4/3)/(2/1));", 0) == Status::OK);
  assert(parse("(((8/4)/1)*5);", 10) == Status::OK);
  assert(parse("((5/2)*(2*(7/3)));", 8) == Status::OK);
  assert(parse("((03*4)*(1*2/(6-5)));", 24) == Status::OK);
  assert(parse("(9/(2)/(8))+((4)-(1)/2);", 4) == Status::OK);

  assert(parse("((40/3)/(2/1));", 6) == Status::OK);
  assert(parse("(1+23)-(3+17);", 4) == Status::OK);
  assert(parse("90/9/3;", 3) == Status::OK);
  assert(parse("10*2*30;", 600) == Status::OK);

  assert(parse("(6-2)*2;", 8) == Status::OK);
  assert(parse("(6-2)*2;", 7) == Status::WRONG_RESULT);
  assert(parse("(6-2)*2", 8) == Status::SYNTAX_ERROR);
}