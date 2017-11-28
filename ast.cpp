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

Tree * generate(TreeType treeType, TreePayload treePayload)
{
    Tree * tree = new Tree{ treeType, treePayload };
  return tree;
}

void clear(Tree * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  switch (tree->type)
  {
  case TreeType::ADD:
  {
    clear(tree->payload.branches.left);
    clear(tree->payload.branches.right);
    delete tree;
    break;
  }
  case TreeType::MUL:
  {
    clear(tree->payload.branches.left);
    clear(tree->payload.branches.right);
    delete tree;
    break;
  }
  case TreeType::PRIM:
  {
    clear(tree->payload.branch);
    delete tree;
    break;
  }
  case TreeType::NUM:
  {
    delete tree;
    return;
  }
  }
}

void print_test()
{
  Tree * t1 = generate( TreeType::ADD,{nullptr,nullptr});
  print(t1);
  std::cout << "\n";

  Tree * t2 = generate(TreeType::NUM, 6 );
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

  Tree * t6 = generate(TreeType::MUL,{nullptr,nullptr} );
  print(t6);
  std::cout << "\n";

  Tree * t7 = generate(TreeType::MUL,{t4,t4} );
  print(t7);
  std::cout << "\n";

  Tree * t8 = generate(TreeType::MUL, { generate(TreeType::PRIM,{generate(TreeType::NUM,8)}), nullptr});
  print(t8);
  std::cout << "\n";
}

void clear_test()
{
  Tree * t1 = generate( TreeType::ADD,{nullptr,nullptr});
  clear(t1);
  print(t1);

  Tree * t2 = generate(TreeType::NUM, 6 );
  clear(t2);
  print(t2);

  Tree * t3 = generate(TreeType::PRIM, {generate(TreeType::NUM, 6 )} );
  clear(t3);
  print(t3);

  Tree * t4 = generate(TreeType::PRIM, {nullptr} );
  clear(t4);
  print(t4);

  Tree * t5 = generate(TreeType::PRIM, {generate(TreeType::NUM,11)} );
  clear(t5);
  print(t5);

  Tree * t6 = generate(TreeType::MUL,{nullptr,nullptr} );
  clear(t6);
  print(t6);
  std::cout << "\n";

  Tree * t7 = generate(TreeType::MUL,{generate(TreeType::PRIM, {nullptr} ),generate(TreeType::PRIM, {nullptr} )} );
  clear(t7);
  print(t7);

  Tree * t8 = generate(TreeType::MUL, { generate(TreeType::PRIM,{generate(TreeType::NUM,8)}), nullptr});
  clear(t8);
  print(t8);
}

int main()
{
  print_test();
  clear_test();
  char wait; std::cin >> wait;
  return 0;
}