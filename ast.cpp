#include<iostream>
#include <assert.h>
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


TreeDigit * generate_digit(int d)
{
  return new TreeDigit{ d };
}
TreeNum * generate_num1(TreeDigit * digit)
{
  return new TreeNum{ digit };
}
TreeNum * generate_num2(TreeNum * num,TreeDigit * digit)
{
  return new TreeNum{ num,digit };
}
TreePrim * generate_prim(TreeNum * num)
{
  return new TreePrim{ num };
}
TreePrim * generate_prim(TreeAdd * add)
{
  return new TreePrim{ add };
}
TreeMul * generate_mul1(TreePrim * mul)
{
  return new TreeMul{ mul };
}
TreeMul * generate_mul2(TreeMul * mul,TreePrim * prim, char op)
{
  return new TreeMul{ mul, prim, op };
}
TreeAdd * generate_add1(TreeMul * mul)
{
  return new TreeAdd{ mul };
}
TreeAdd * generate_add2(TreeAdd * add, TreeMul * mul,char op)
{
  return new TreeAdd{ add,mul,op };
}
TreeStmt * generate_stmt(TreeAdd * add)
{
  return new TreeStmt{ add };
}

void clearStmt(TreeStmt * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  clearAdd(tree->add);
  delete tree;
}

void clearAdd(TreeAdd * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  switch (tree->type)
  {
  case TreeAdd::TreeAddType::ADD1:
    clearMul(tree->payload.add1);
    break;
  case TreeAdd::TreeAddType::ADD2:
    clearAdd(tree->payload.add2.add);
    clearMul(tree->payload.add2.mul);
    break;
  }
  delete tree;
}

void clearMul(TreeMul * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  switch (tree->type)
  {
  case TreeMul::TreeMulType::MUL1:
    clearPrim(tree->payload.mul1);
    break;
  case TreeMul::TreeMulType::MUL2:
    clearMul(tree->payload.mul2.mul);
    clearPrim(tree->payload.mul2.prim);
    break;
  }
  delete tree;
}

void clearPrim(TreePrim * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  switch (tree->type)
  {
  case TreePrim::TreePrimType::ADD:
    clearAdd(tree->payload.add);
    break;
  case TreePrim::TreePrimType::NUM:
    clearNum(tree->payload.num);
    break;
  }
  delete tree;
}

void clearNum(TreeNum * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  switch (tree->type)
  {
  case TreeNum::TreeNumType::NUM1:
    clearDigit(tree->payload.num1);
    break;
  case TreeNum::TreeNumType::NUM2:
    clearNum(tree->payload.num2.num);
    clearDigit(tree->payload.num2.digit);
    break;
  }
  delete tree;
}

void clearDigit(TreeDigit * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  delete tree;
}

void test()
{
  //expression: 0/4-(1*3)
  TreeAdd * t =
    generate_add2(
      generate_add1(
        generate_mul2(
          generate_mul1(
            generate_prim(
              generate_num1(
                generate_digit(0)))),
          generate_prim(
            generate_num1(
              generate_digit(4))),
        '/')),
      generate_mul1(
        generate_prim(
          generate_add1(
            generate_mul2(
              generate_mul1(
                generate_prim(
                  generate_num1(
                    generate_digit(1)))),
              generate_prim(
                generate_num1(
                  generate_digit(3))),
              '*')))),
      '-');
  printAdd(t);
  clearAdd(t);
  printf("\n");

  TreeNum * t2 = generate_num1(generate_digit(3));
  printNum(t2);
  clearNum(t2);
  printf("\n");

  TreePrim * t3 =generate_prim(generate_num1(generate_digit(6)));
  printPrim(t3);
  clearPrim(t3);
  printf("\n");

  TreePrim * t4 = generate_prim(generate_num1(generate_digit(0)));
  printPrim(t4);
  clearPrim(t4);
  printf("\n");

  TreePrim * t5 = generate_prim(generate_num1(generate_digit(1)));
  printPrim(t5);
  clearPrim(t5);
  printf("\n");

  TreeMul * t6 = 
    generate_mul2(
      generate_mul1(
        generate_prim(
          generate_num1(
            generate_digit(0)))),
      generate_prim(
        generate_num1(
          generate_digit(4))),
      '/');
  printMul(t6);
  clearMul(t6);
  printf("\n");

  TreeMul * t7 = 
    generate_mul2(
      generate_mul1(
        generate_prim(
          generate_num1(nullptr))),
      generate_prim(
        generate_num1(nullptr)),
      '*');
  printMul(t7);
  clearMul(t7);
  printf("\n");

  TreeMul * t8 = generate_mul2(generate_mul1(generate_prim(generate_num1(generate_digit(8)))), nullptr,'*');
  printMul(t8);
  clearMul(t8);
  printf("\n");

}

int calculateStmt(TreeStmt * tree)
{
  if (tree == nullptr)
  {
    // TODO: track errors
    assert(false);
  }
  return calculateAdd(tree->add);
}

int calculateAdd(TreeAdd * tree)
{
  if (tree == nullptr)
  {
    // TODO: track errors
    assert(false);
  }
  else if(tree->type == TreeAdd::TreeAddType::ADD1)
  {
    return calculateMul(tree->payload.add1);
  }
  else if (tree->type == TreeAdd::TreeAddType::ADD2)
  {
    switch (tree->payload.add2.operation)
    {
    case '+':
      return calculateAdd(tree->payload.add2.add) + calculateMul(tree->payload.add2.mul);
    case '-':
      return calculateAdd(tree->payload.add2.add) - calculateMul(tree->payload.add2.mul);
    }
    assert(false);
  }
}

int calculateMul(TreeMul * tree)
{
  if (tree == nullptr)
  {
    
  }
  else if (tree->type == TreeMul::TreeMulType::MUL1)
  {
    return calculatePrim(tree->payload.mul1);
  }
  else if (tree->type == TreeMul::TreeMulType::MUL2)
  {
    switch (tree->payload.mul2.operation)
    {
    case '*':
      return calculateMul(tree->payload.mul2.mul) * calculatePrim(tree->payload.mul2.prim);
    case '/':
      return calculateMul(tree->payload.mul2.mul) / calculatePrim(tree->payload.mul2.prim);
    }
    assert(false);
  }
}

int calculatePrim(TreePrim * tree)
{
  if (tree == nullptr)
  {
    // TODO: track errors
    assert(false);
  }
  else if (tree->type == TreePrim::TreePrimType::NUM)
  {
    return calculateNum(tree->payload.num);
  }
  else if (tree->type == TreePrim::TreePrimType::ADD)
  {
    return calculateAdd(tree->payload.add);
  }
  assert(false);
}

int calculateNum(TreeNum * tree)
{
  if (tree == nullptr)
  {
    // TODO: track errors
    assert(false);
  }
  else if (tree->type == TreeNum::TreeNumType::NUM1)
  {
    return calculateDigit(tree->payload.num1);
  }
  else if (tree->type == TreeNum::TreeNumType::NUM2)
  {
    return (calculateNum(tree->payload.num2.num)*10) + calculateDigit(tree->payload.num2.digit);
  }
  assert(false);
}

int calculateDigit(TreeDigit * tree)
{
  if (tree == nullptr)
  {
    // TODO: track errors
    assert(false);
  }
  return tree->value;
}

/*
int calculateTree(Tree * tree)
{
  if (tree == nullptr)
  {
    // TODO: track errors
    assert(false);
    return 0;
  }
  switch (tree->type)
  {
  case TreeType::STMT:
  case TreeType::ADD1:
  case TreeType::PRIM:
  case TreeType::NUM1:
  case TreeType::MUL1:
  {
    return calculateTree(tree->payload.branch);
  }
  case TreeType::ADD2:
  {
    switch (tree->payload.branches.operation)
    {
    case '+':
      return calculateTree(tree->payload.branches.left) + calculateTree(tree->payload.branches.right);
    case '-':
      return calculateTree(tree->payload.branches.left) - calculateTree(tree->payload.branches.right);
    }
  }
  case TreeType::MUL2:
  {
    switch (tree->payload.branches.operation)
    {
    case '*':
      return calculateTree(tree->payload.branches.left) * calculateTree(tree->payload.branches.right);
    case '/':
      return calculateTree(tree->payload.branches.left) / calculateTree(tree->payload.branches.right);
    }
  }
  case TreeType::NUM2:
  {
    return (calculateTree(tree->payload.branches.left) * 10) + calculateTree(tree->payload.branches.right);
  }
  
  case TreeType::DIGIT:
  {
    return tree->payload.value;
  }
  }
}
*/
int main()
{
  test();
  char wait; std::cin >> wait;
  return 0;
}