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
    std::cout << "DIGIT( "<< tree->payload.value << " )";
    break;
  }
  case TreeType::NUM:
  {
    std::cout << "NUM(";
    print(tree->payload.branch);
    std::cout << ")";
    break;
  }
  case TreeType::PRIM:
  {
    std::cout << "PRIM( ";
    print(tree->payload.branch);
    std::cout << " )";
    break;
  }
  case TreeType::MUL1:
  {
    std::cout << "MUL1( ";
    print(tree->payload.branch);
    std::cout << " )";
    break;
  }
  case TreeType::MUL2:
  {
    std::cout << "MUL( ";
    print(tree->payload.branches.left);
    std::cout << ", ";
    print(tree->payload.branches.right);
    std::cout << " )";
    break;
  }
  case TreeType::ADD1:
  {
    std::cout << "ADD1( ";
    print(tree->payload.branch);
    std::cout << " )";
    break;
  }
  case TreeType::ADD2:
  {
    std::cout << "ADD2( ";
    print(tree->payload.branches.left);
    std::cout << ", ";
    print(tree->payload.branches.right);
    std::cout << " )";
    break;
  }
  }
}

void printTree(const Tree * tree)
{
  print(tree);
  std::cout << std::endl;
}
Tree * generate(TreeType treeType, TreePayload treePayload)
{
    Tree * tree = new Tree{ treeType, treePayload };
  return tree;
}

Tree * generate_num(Tree * branch)
{
  return new Tree{ TreeType::NUM, {branch}};
}

Tree * generate_prim(Tree * branch)
{
  return new Tree{ TreeType::PRIM, {branch}};
}

Tree * generate_add1(Tree * branch)
{
  return new Tree{ TreeType::ADD1, {branch}};
}

Tree * generate_add2(Tree * branch1, Tree* branch2)
{
  return new Tree{ TreeType::ADD2, {branch1,branch2}};
}

Tree * generate_mul1(Tree * branch)
{
  return new Tree{ TreeType::MUL1, {branch}};
}

Tree * generate_mul2(Tree * branch1, Tree* branch2)
{
  return new Tree{ TreeType::MUL2, {branch1,branch2}};
}

Tree * generate_digit(int d)
{
  return new Tree{ TreeType::DIGIT, {d} };
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
  case TreeType::NUM:
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

/*void print_test()
{
  Tree * t1 = generate( TreeType::ADD2,{nullptr,nullptr});
  print(t1);
  std::cout << "\n";

  Tree * t2 = generate(TreeType::NUM, 3 );
  print(t2);
  std::cout << "\n";

  Tree * t3 = generate(TreeType::PRIM, {t2} );
  print(t3);
  std::cout << "\n";

  Tree * t4 = generate(TreeType::PRIM, {nullptr} );
  print(t4);
  std::cout << "\n";

  Tree * t5 = generate(TreeType::PRIM, t1 );
  print(t5);
  std::cout << "\n";

  Tree * t6 = generate(TreeType::MUL2,{nullptr,nullptr} );
  print(t6);
  std::cout << "\n";

  Tree * t7 = generate(TreeType::MUL2,{t4,t4} );
  print(t7);
  std::cout << "\n";

  Tree * t8 = generate(TreeType::MUL2, { generate(TreeType::PRIM,{generate(TreeType::NUM,8)}), nullptr});
  print(t8);
  std::cout << "\n";
}*/

void clear_test()
{
  /*Tree * t1 = generate_add2(generate_mul2(generate_prim(generate_num(generate_digit(0))),generate_prim(generate_num(generate_digit(4))) ),
                            generate_mul2(generate_prim(generate_num(generate_digit(1))),generate_prim(generate_num(generate_digit(3))) ));
  printTree(t1);
  clear(t1);*/

  Tree * t2 = generate_num(generate_digit(3));
  printTree(t2);
  clear(t2);

  Tree * t3 =generate_prim(generate_num(generate_digit(6)));
  printTree(t3);
  clear(t3);

  Tree * t4 = generate_num(generate_digit(0));
  printTree(t4);
  clear(t4);

  /*Tree * t5 = generate(TreeType::PRIM,  {generate(TreeType::NUM,generate(TreeType::DIGIT, 1))} );
  clear(t5);
  printTree(t5);*/

  /*Tree * t6 = generate_mul2(generate_prim(generate_num(generate_digit(0))),generate_prim(generate_num(generate_digit(4))) );
  printTree(t6);
  clear(t6);*/

//  Tree * t7 = generate(TreeType::MUL2,{generate(TreeType::PRIM, {nullptr} ),generate(TreeType::PRIM, {nullptr} )} );
//  clear(t7);
//  printTree(t7);
//
//  Tree * t8 = generate(TreeType::MUL2, { generate(TreeType::PRIM,{generate(TreeType::NUM,generate(TreeType::DIGIT, 8))}), nullptr});
//  clear(t8);
//  printTree(t8);
}

int main()
{
  clear_test();
  char wait; std::cin >> wait;
  return 0;
}