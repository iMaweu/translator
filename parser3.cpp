#include <stdio.h>
#include <assert.h>
#include "ast.h"

enum class Status
{
  OK,
  WRONG_RESULT,
  SYNTAX_ERROR
};

bool stmt(const char * s, Tree  * &tree);
bool add(const char * &s, Tree * &tree);
bool mul(const char * &s, Tree * &tree);
bool prim(const char * &s, Tree * &tree);
bool digit(const char * &s, Tree * &tree);
bool integer(const char * &s, Tree * &tree);
Status parse(const char * s, int expect);

bool stmt(const char * s, Tree * &tree)
{
  bool validAdd = add(s, tree);
  if (validAdd && s[0] == ';')
  {
    tree = generate_stmt(tree);
    return true;
  }
  return false;
}

bool add(const char * &s, Tree* &tree)
{
  if (!mul(s, tree))
  {
    return false;
  }

  Tree * tree2{ nullptr };
  while (true)
  {
    switch (*s)
    {
    case '+':
      s++;
      if (!mul(s, tree2))
      {
        return false;
      }
      tree = generate_add2(tree, tree2, '+');
      break;
    case '-':
      s++;
      if (!mul(s, tree2))
      {
        return false;
      }
      tree = generate_add2(tree, tree2, '-');
      break;
    default:
      tree = generate_add1(tree);
      return true;
    }
  }
}

bool mul(const char * &s, Tree * &tree)
{
  if (!prim(s, tree))
  {
    return false;
  }

  Tree * tree2{ nullptr };
  while (true)
  {
    switch (*s)
    {
    case '*':
      s++;
      if (!prim(s, tree2))
      {
        return false;
      }
      tree = generate_mul2(tree, tree2, '*');
      break;
    case '/':
      s++;
      if (!prim(s, tree2))
      {
        return false;
      }
      tree = generate_mul2(tree, tree2, '/');
      break;
    default:
      tree = generate_mul1(tree);
      return true;
    }
  }
}

bool prim(const char * &s, Tree * &tree)
{
  if (s[0] == '(')
  {
    if (!add(++s, tree) || s[0] != ')')
    {
      return false;
    }
    ++s;
  }
  else if (!integer(s, tree))
  {
    return false;
  }
  tree = generate_prim(tree);
  return true;
}

bool integer(const char * &s, Tree* &tree)
{

  if (digit(s, tree))
  {
    tree = generate_num1(tree);
    Tree * tree2{ nullptr };
    while (digit(s, tree2))
    {
      tree = generate_num2(tree, tree2);
    }
    return true;
  }
  else
  {
    return false;
  }
}

bool digit(const char * &s, Tree * &tree)
{
  if (s[0] >= '0' && s[0] <= '9')
  {
    tree = generate_digit(s[0] - '0');
    s++;
    return true;
  }
  else
  {
    return false;
  }
}

Status parse(const char * s, int expect)
{
  Tree * tree{ nullptr };
  if (!stmt(s, tree))
  {
    return Status::SYNTAX_ERROR;
  }
  else
  {
    return calculateTree(tree) == expect ? Status::OK : Status::WRONG_RESULT;
  }
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
  assert(parse("((3*4)*(1*2/(6-5)));", 24) == Status::OK);
  assert(parse("(9/(2)/(8))+((4)-(1)/2);", 4) == Status::OK);

  assert(parse("((40/3)/(2/1));", 6) == Status::OK);
  assert(parse("(1+23)-(3+17);", 4) == Status::OK);
  assert(parse("90/9/3;", 3) == Status::OK);
  assert(parse("10*2*30;", 600) == Status::OK);

  assert(parse("(6-2)*2;", 8) == Status::OK);
  assert(parse("(6-2)*2;", 7) == Status::WRONG_RESULT);
  assert(parse("(6-2)*2", 8) == Status::SYNTAX_ERROR);

}

int main1()
{
  run_asserts();
  char wait = getc(stdin);
  return 0;
}