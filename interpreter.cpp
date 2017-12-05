#include <assert.h>

#include "ast.h"

int interpret(const Tree * tree)
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
      return interpret(tree->value.oper.left) +
        interpret(tree->value.oper.right);

    case '-':
      return interpret(tree->value.oper.left) - 
        interpret(tree->value.oper.right);

    case '*':
      return interpret(tree->value.oper.left) * 
        interpret(tree->value.oper.right);

    case '/':
      return interpret(tree->value.oper.left) / 
        interpret(tree->value.oper.right);
    }
  }
}