#include<iostream>
#include <assert.h>
#include <stdio.h>

#include "ast.h"

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
TreePrim * generate_prim_num(TreeNum * num)
{
  return new TreePrim{ num };
}
TreePrim * generate_prim_add(TreeAdd * add)
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

void test()
{
  //expression: 0/4-(1*3)
  TreeAdd * t =
    generate_add2(
      generate_add1(
        generate_mul2(
          generate_mul1(
            generate_prim_num(
              generate_num1(
                generate_digit(0)))),
          generate_prim_num(
            generate_num1(
              generate_digit(4))),
        '/')),
      generate_mul1(
        generate_prim_add(
          generate_add1(
            generate_mul2(
              generate_mul1(
                generate_prim_num(
                  generate_num1(
                    generate_digit(1)))),
              generate_prim_num(
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

  TreePrim * t3 =generate_prim_num(generate_num1(generate_digit(6)));
  printPrim(t3);
  clearPrim(t3);
  printf("\n");

  TreePrim * t4 = generate_prim_num(generate_num1(generate_digit(0)));
  printPrim(t4);
  clearPrim(t4);
  printf("\n");

  TreePrim * t5 = generate_prim_num(generate_num1(generate_digit(1)));
  printPrim(t5);
  clearPrim(t5);
  printf("\n");

  TreeMul * t6 = 
    generate_mul2(
      generate_mul1(
        generate_prim_num(
          generate_num1(
            generate_digit(0)))),
      generate_prim_num(
        generate_num1(
          generate_digit(4))),
      '/');
  printMul(t6);
  clearMul(t6);
  printf("\n");

  TreeMul * t7 = 
    generate_mul2(
      generate_mul1(
        generate_prim_num(
          generate_num1(nullptr))),
      generate_prim_num(
        generate_num1(nullptr)),
      '*');
  printMul(t7);
  clearMul(t7);
  printf("\n");

  TreeMul * t8 = generate_mul2(generate_mul1(generate_prim_num(generate_num1(generate_digit(8)))), nullptr,'*');
  printMul(t8);
  clearMul(t8);
  printf("\n");
}