#include <stdio.h>
#include <assert.h>

#include "ast.h"
#include "parser.h"

bool stmt(const char * s, TreeStmt * &tree)
{
  TreeStmt * tree2 = generate_stmt(nullptr);
  bool validAdd = add(s, tree2->add);
  tree = tree2;
  if (validAdd && s[0] == ';')
  {
    return true;
  }
  return false;
}

bool add(const char * &s, TreeAdd * &tree)
{
  TreeAdd * tree2 = generate_add1(nullptr);
  if (!mul(s, tree2->payload.add1))
  {
    return false;
  }

  tree = tree2;
  TreeAdd * tree3 = generate_add1(nullptr);
  while (true)
  {
    switch (*s)
    {
    case '+':
      s++;
      if (!mul(s, tree3->payload.add1))
      {
        return false;
      }
      tree = generate_add2(tree, tree3->payload.add1, '+');
      break;
    case '-':
      s++;
      if (!mul(s, tree3->payload.add1))
      {
        return false;
      }
      tree = generate_add2(tree, tree3->payload.add1, '-');
      break;
    default:
      return true;
    }
  }
}

bool mul(const char * &s, TreeMul * &tree)
{
  TreeMul * tree2 = generate_mul1(nullptr);
  if (!prim(s, tree2->payload.mul1))
  {
    return false;
  }

  tree = tree2;
  TreeMul* tree3 = generate_mul1(nullptr);
  while (true)
  {
    switch (*s)
    {
    case '*':
      s++;
      if (!prim(s, tree3->payload.mul1))
      {
        return false;
      }
      tree = generate_mul2(tree, tree3->payload.mul1, '*');
      break;
    case '/':
      s++;
      if (!prim(s, tree3->payload.mul1))
      {
        return false;
      }
      tree = generate_mul2(tree, tree3->payload.mul1, '/');
      break;
    default:
      return true;
    }
  }
}

bool prim(const char * &s, TreePrim * &tree)
{
  if (s[0] == '(')
  {
    TreePrim * tree2 = generate_prim_add(nullptr);
    s++;
    if (add(s, tree2->payload.add) && s[0] == ')')
    {
      tree = tree2;
      s++;
      return true;
    }
    return false;
  }

  TreePrim * tree3 = generate_prim_num(nullptr);
  if (num(s, tree3->payload.num))
  {
    tree = tree3;
    return true;
  }
  return false;
}

bool num(const char * &s, TreeNum * &tree)
{
  TreeNum * tree2 = generate_num1(nullptr);
  if (digit(s, tree2->payload.num1))
  {
    tree = tree2;
    TreeNum * tree3 = generate_num1(nullptr);
    while (digit(s, tree3->payload.num1))
    {
      tree = generate_num2(tree, tree3->payload.num1);
    }
    return true;
  }
  else
  {
    return false;
  }
}

bool digit(const char * &s, TreeDigit * &tree)
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
  TreeStmt * tree = generate_stmt(nullptr);
  if (!stmt(s, tree))
  {
    clearStmt(tree);
    return Status::SYNTAX_ERROR;
  }
  else if ( calculateStmt(tree) == expect)
  {
    printStmt(tree);
    printf("\n");
    clearStmt(tree);
    return Status::OK;
  }
  else
  {
    clearStmt(tree);
    return Status::WRONG_RESULT;
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

