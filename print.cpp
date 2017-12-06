#include <stdio.h>
#include <memory>

#include "ast.h"

void print(const Tree_ptr&& tree)
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
    print(std::move(tree->value.oper.left));
    printf(" %c ", tree->value.oper.operType);
    print(std::move(tree->value.oper.right));
    printf(" )");
  }
}

void printTree(const Tree_ptr&& tree)
{
  print(std::move(tree));
  printf("\n");
}
