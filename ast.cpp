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
  case TreeType::NUM:
  {
    std::cout << "NUM(";
    std::cout << tree->payload.value;
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
  case TreeType::MUL:
  {
    std::cout << "MUL( ";
    print(tree->payload.branches.left);
    std::cout << ", ";
    print(tree->payload.branches.right);
    std::cout << " )";
    break;
  }
  case TreeType::ADD:
  {
    std::cout << "ADD( ";
    print(tree->payload.branches.left);
    std::cout << ", ";
    print(tree->payload.branches.right);
    std::cout << " )";
    break;
  }
  }
}

/*Tree * generateTree(TreeType treeType, TreePayload treePayload)
{
    Tree * tree = new Tree{ treeType, treePayload };
  return tree;
}*/

/*void clearTree(Tree * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  clearTree(tree->left);
  clearTree(tree->right);
  delete tree;
}*/

void print_test()
{
  Tree * t1 = new Tree{ TreeType::ADD,{nullptr,nullptr} };
  print(t1);
  std::cout << "\n";

  Tree * t2 = new Tree{ TreeType::NUM, 6 };
  print(t2);
  std::cout << "\n";

  Tree * t3 = new Tree{ TreeType::PRIM, {t2} };
  print(t3);
  std::cout << "\n";

  Tree * t4 = new Tree{ TreeType::PRIM, {nullptr} };
  print(t4);
  std::cout << "\n";

  Tree * t5 = new Tree{ TreeType::PRIM, t1 };
  print(t5);
  std::cout << "\n";

  Tree * t6 = new Tree{ TreeType::MUL,{nullptr,nullptr} };
  print(t6);
  std::cout << "\n";

  Tree * t7 = new Tree{ TreeType::MUL,{t4,t4} };
  print(t7);
  std::cout << "\n";
}

int main()
{
  print_test();
  // Tree * t = generateTree();
  //clearTree(t);
  char wait; std::cin >> wait;
  return 0;
}