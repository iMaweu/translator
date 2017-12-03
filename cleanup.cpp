#include "ast.h"

void clearTree(Tree * &tree)
{
  if (tree == nullptr)
  {
    return;
  }
  else if (tree->type == Tree::TreeType::OPER)
  {
    clearTree(tree->value.oper.left);
    clearTree(tree->value.oper.right);
  }
  delete tree;
  tree = nullptr;
}
