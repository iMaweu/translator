#include <stdio.h>
#include <assert.h>

#include "ast.h"
#include "parser.h"

Status parse(const char * s, int expect)
{
  Tree * tree = generate_branch(0);
  if (!stmt(s, tree) || s[0] != ';')
  {
    return Status::SYNTAX_ERROR;
  }
  else if (calculateTree(tree) == expect)
  {
    printTree(tree);
    return Status::OK;
  }
  else
  {
    return Status::WRONG_RESULT;
  }
}

bool stmt(const char * &s, Tree * &tree)
{
  return add(s,tree);
}

bool add(const char * &s, Tree * &tree)
{
  if (!mul(s, tree))
  {
    return false;
  }
  while (s[0] == '+' || s[0] == '-')
  {
    char operType = s[0];
    s++;
    Tree * tree2 = generate_branch(0);
    if (!mul(s, tree2))
    {
      return false;
    }
    tree = generate_tree(tree, tree2, operType);
  }
  return true;
}

bool mul(const char * &s, Tree * &tree)
{
  if (!prim(s, tree))
  {
    return false;
  }

  while (s[0] == '*' || s[0] == '/')
  {
    char operType = s[0];
    s++;
    Tree * tree2 = generate_branch(0);
    if (!prim(s, tree2))
    {
      return false;
    }
    tree = generate_tree(tree, tree2, operType);
  }
  return true;
}

bool prim(const char * &s, Tree * &tree)
{
  if (s[0] == '(')
  {
    s++;
    add(s, tree);
    if (s[0] == ')')
    {
      s++;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return num(s, tree);
  }
}

bool num(const char * &s, Tree * &tree)
{
  if (s[0] >= '0' && s[0] <= '9')
  {
    Tree * tree2 = generate_branch(s[0] - '0');
    s++;
    while (s[0] >= '0' && s[0] <= '9')
    {
      tree2->value.number *= 10;
      tree2->value.number += (s[0] - '0');
      s++;
    }
    tree = tree2;
    return true;
  }
  return false;
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