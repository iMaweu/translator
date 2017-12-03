#include <assert.h>

#include "ast.h"

int calculateTree(const Tree * tree)
{
  if (tree == nullptr)
  {
    // TODO: track errors
    assert(false);
  }
  else if (tree->type == Tree::TreeType::NUMBER)
  {
    return tree->value.number;
  }
  else if (tree->type == Tree::TreeType::OPER)
  {
    switch (tree->value.oper.operType)
    {
    case '+':
      return calculateTree(tree->value.oper.left) +
        calculateTree(tree->value.oper.right);

    case '-':
      return calculateTree(tree->value.oper.left) - 
        calculateTree(tree->value.oper.right);

    case '*':
      return calculateTree(tree->value.oper.left) * 
        calculateTree(tree->value.oper.right);

    case '/':
      return calculateTree(tree->value.oper.left) / 
        calculateTree(tree->value.oper.right);
    }
  }
}