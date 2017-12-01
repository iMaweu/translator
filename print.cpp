#include <stdio.h>

#include "ast.h"

void printStmt(const TreeStmt * tree)
{
  if (tree == nullptr)
  {
    printf("NULL");
    return;
  }
  printf("Stmt( ");
  printAdd(tree->add);
  printf(" )");
}

void printAdd(const TreeAdd * tree)
{
  if (tree == nullptr)
  {
    printf("NULL");
    return;
  }
  switch (tree->type)
  {
  case TreeAdd::TreeAddType::ADD1:
    printf("Add1( ");
    printMul(tree->payload.add1);
    printf(")");
    return;
  case TreeAdd::TreeAddType::ADD2:
    printf("Add2( ");
    printAdd(tree->payload.add2.add);
    printf(", ");
    printMul(tree->payload.add2.mul);
    printf(" )");
    return;
  }
}

void printMul(const TreeMul * tree)
{
  if (tree == nullptr)
  {
    printf("NULL");
    return;
  }
  switch (tree->type)
  {
  case TreeMul::TreeMulType::MUL1:
    printf("Mul1( ");
    printPrim(tree->payload.mul1);
    printf(" )");
    return;
  case TreeMul::TreeMulType::MUL2:
    printf("Mul2( ");
    printMul(tree->payload.mul2.mul);
    printf(", ");
    printPrim(tree->payload.mul2.prim);
    printf(" )");
    return;
  }
}

void printPrim(const TreePrim * tree)
{
  if (tree == nullptr)
  {
    printf("NULL");
    return;
  }
  switch (tree->type)
  {
  case TreePrim::TreePrimType::NUM:
    printf("Prim( ");
    printNum(tree->payload.num);
    printf(" )");
    return;
  case TreePrim::TreePrimType::ADD:
    printf("Prim( ");
    printAdd(tree->payload.add);
    printf(" )");
    return;
  }
}

void printNum(const TreeNum * tree)
{
  if (tree == nullptr)
  {
    printf("NULL");
    return;
  }
  switch (tree->type)
  {
  case TreeNum::TreeNumType::NUM1:
    printf("Num1( ");
    printDigit(tree->payload.num1);
    printf(" )");
    return;
  case TreeNum::TreeNumType::NUM2:
    printf("Num2( ");
    printNum(tree->payload.num2.num);
    printf(", ");
    printDigit(tree->payload.num2.digit);
    printf(" )");
    return;
  }
}

void printDigit(const TreeDigit * tree)
{
  if (tree == nullptr)
  {
    printf("NULL");
    return;
  }
  printf("Digit ( %d )", tree->value);
  return;
}