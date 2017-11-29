#include<iostream>
#include "ast.h"

void print(const Tree * tree)
{
  if (tree == nullptr)
  {
    std::cout << "NULL";
    return;
  }

  switch (tree->type)
  {
  case TreeType::DIGIT:
  {
    std::cout << "DIGIT ( "<< tree->payload.value << " )";
    break;
  }
  case TreeType::NUM1:
  {
    std::cout << "NUM1 (";
    print(tree->payload.branch);
    std::cout << ")";
    break;
  }
  case TreeType::NUM2:
  {
    std::cout << "NUM2 (";
    print(tree->payload.branches.left);
    std::cout << ", ";
    print(tree->payload.branches.right);
    std::cout << ")";
    break;
  }
  case TreeType::PRIM:
  {
    std::cout << "PRIM (";
    print(tree->payload.branch);
    std::cout << ")";
    break;
  }
  case TreeType::MUL1:
  {
    std::cout << "MUL1 (";
    print(tree->payload.branch);
    std::cout << ")";
    break;
  }
  case TreeType::MUL2:
  {
    std::cout << "MUL2 (";
    print(tree->payload.branches.left);
    std::cout << ", ";
    print(tree->payload.branches.right);
    std::cout << ")";
    break;
  }
  case TreeType::ADD1:
  {
    std::cout << "ADD1 (";
    print(tree->payload.branch);
    std::cout << ")";
    break;
  }
  case TreeType::ADD2:
  {
    std::cout << "ADD2 (";
    print(tree->payload.branches.left);
    std::cout << ", ";
    print(tree->payload.branches.right);
    std::cout << ")";
    break;
  }
  case TreeType::STMT:
  {
    std::cout << "STMT (";
    print(tree->payload.branch);
    std::cout << ")";
    break;
  }
  }
}

void printTree(const Tree * tree)
{
  print(tree);
  std::cout << std::endl << std::endl;
}
Tree * generate(TreeType treeType, TreePayload treePayload)
{
    Tree * tree = new Tree{ treeType, treePayload };
  return tree;
}

Tree * generate_num1(Tree * branch)
{
  return new Tree{ TreeType::NUM1, {branch}};
}

Tree *generate_num2(Tree *branch1, Tree *branch2)
{
  return new Tree{ TreeType::NUM2,{branch1,branch2,'\0'} };
}

Tree * generate_prim(Tree * branch)
{
  return new Tree{ TreeType::PRIM, {branch}};
}

Tree * generate_add1(Tree * branch)
{
  return new Tree{ TreeType::ADD1, {branch}};
}

Tree * generate_add2(Tree * branch1, Tree* branch2, char op)
{
  return new Tree{ TreeType::ADD2, {branch1,branch2,op}};
}


Tree * generate_mul1(Tree * branch)
{
  return new Tree{ TreeType::MUL1, {branch}};
}

Tree * generate_mul2(Tree * branch1, Tree* branch2, char op)
{
  return new Tree{ TreeType::MUL2, {branch1,branch2,op}};
}


Tree * generate_digit(int d)
{
  return new Tree{ TreeType::DIGIT, {d} };
}

Tree *generate_stmt(Tree * branch)
{
  return new Tree{ TreeType::STMT,{branch} };
}

void clear(Tree * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  switch (tree->type)
  {
  case TreeType::ADD1:
  {
    clear(tree->payload.branch);
    break;
  }
  case TreeType::ADD2:
  {
    clear(tree->payload.branches.left);
    clear(tree->payload.branches.right);
    break;
  }
  case TreeType::MUL1:
  {
    clear(tree->payload.branch);
    break;
  }
  case TreeType::MUL2:
  {
    clear(tree->payload.branches.left);
    clear(tree->payload.branches.right);
    break;
  }
  case TreeType::PRIM:
  {
    clear(tree->payload.branch);
    break;
  }
  case TreeType::NUM1:
  {
    clear(tree->payload.branch);
    break;
  }
  case TreeType::NUM2:
  {
    clear(tree->payload.branches.left);
    clear(tree->payload.branches.right);
    break;
  }
  case TreeType::STMT:
  {
    clear(tree->payload.branch);
    break;
  }
  case TreeType::DIGIT:
  {
    break;
  }
  }
  delete tree;
}


void test()
{
  Tree * t1 = generate_add2(generate_mul2(generate_prim(generate_num1(generate_digit(0))),generate_prim(generate_num1(generate_digit(4))),'/' ),
                            generate_mul2(generate_prim(generate_num1(generate_digit(1))),generate_prim(generate_num1(generate_digit(3))),'*' ),'-');
  printTree(t1);
  clear(t1);

  Tree * t2 = generate_num1(generate_digit(3));
  printTree(t2);
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

  Tree * t6 = generate_mul2(generate_prim(generate_num1(generate_digit(0))),generate_prim(generate_num1(generate_digit(4))),'/');
  printTree(t6);
  clear(t6);

  Tree * t7 = generate_mul2(generate_prim(nullptr), generate_prim(nullptr),'*');
  printTree(t7);
  clear(t7);

  Tree * t8 = generate_mul2(generate_prim(generate_num1(generate_digit(8))), nullptr,'*');
  printTree(t8);
  clear(t8);

}

/*int calculateTree(Tree * tree)
{
  if (tree == nullptr)
  {
    return 0;
  }
  switch (tree->type)
  {
  case TreeType::STMT:
  {
    clear(tree->payload.branch);
    break;
  }
  case TreeType::ADD1:
  {
    break;
  }
  case TreeType::ADD2:
  {
    clear(tree->payload.branches.left);
    clear(tree->payload.branches.right);
    break;
  }
  case TreeType::MUL1:
  {
    clear(tree->payload.branch);
    break;
  }
  case TreeType::MUL2:
  {
    clear(tree->payload.branches.left);
    clear(tree->payload.branches.right);
    break;
  }
  case TreeType::PRIM:
  {
    clear(tree->payload.branch);
    break;
  }
  case TreeType::NUM1:
  {
    return calculateTree(tree->payload.branch);
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
}*/

int main()
{
  test();
  char wait; std::cin >> wait;
  return 0;
}