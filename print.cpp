#include <stdio.h>
#include <memory>

#include "ast.h"

void print(const std::shared_ptr<Tree> tree)
{
  if (tree == nullptr)
  {
    return;
  }
  if (tree->type == Tree::TreeType::NUMBER)
  {
    printf("( %d )", tree->value.number);
    return;
  }
  else if (tree->type == Tree::TreeType::OPER)
  {
    printf("( ");
    print(tree->value.oper.left);
    printf(" %c ", tree->value.oper.operType);
    print(tree->value.oper.right);
    printf(" )");
  }
}

void printTree(const std::shared_ptr<Tree> tree)
{
  print(tree);
  printf("\n");
}
