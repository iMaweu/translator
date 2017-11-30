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

/*
void clear(Tree * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  switch (tree->type)
  {
  case TreeType::DIGIT:
  {
    break;
  }
  case TreeType::STMT:
  case TreeType::PRIM:
  case TreeType::NUM1:
  case TreeType::MUL1:
  case TreeType::ADD1:
  {
    clear(tree->payload.branch);
    break;
  }
  case TreeType::MUL2:
  case TreeType::NUM2:
  case TreeType::ADD2:
  {
    clear(tree->payload.branches.left);
    clear(tree->payload.branches.right);
    break;
  }
  }
  delete tree;
}
*/

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
                generate_digit(0)
              )
            )
          ),
          generate_prim(
            generate_num1(
              generate_digit(4)
            )
          ),
        '/'
      )
    ),
      generate_mul1(
        generate_prim(
          generate_add1(
            generate_mul2(
              generate_mul1(
                generate_prim(
                  generate_num1(
                    generate_digit(1)
                  )
                )
              ),
              generate_prim(
                generate_num1(
                  generate_digit(3)
                )
              ),
              '*'
            )
          )
        )
      ),
      '-'
    );

  printAdd(t);

  /*TreeNum * t2 = generate_num1(generate_digit(3));
  printNum(t2);
  clear(t2);

  Tree * t3 =generate_prim(generate_num1(generate_digit(6)));
  printTree(t3);
  clear(t3);

  Tree * t4 = generate_prim(generate_digit(0));
  printTree(t4);
  clear(t4);

  Tree * t5 = generate_prim(generate_num1(generate_digit(1)));
  printTree(t5);
  clear(t5);

  TreeMul * t6 = generate_mul2(generate_mul1(generate_prim(generate_num1(generate_digit(0)))),generate_prim(generate_num1(generate_digit(4))),'/');
  printTree(t6);
  clear(t6);

  Tree * t7 = generate_mul2(generate_prim(nullptr), generate_prim(nullptr),'*');
  printTree(t7);
  clear(t7);

  Tree * t8 = generate_mul2(generate_prim(generate_num1(generate_digit(8))), nullptr,'*');
  printTree(t8);
  clear(t8);*/

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