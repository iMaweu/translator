#include <assert.h>
#include<climits>

#include "ast.h"

int interpret(const Tree * tree)
{
  if (tree == nullptr)
  {
    return INT_MAX;
  }
  else if (tree->type == Tree::TreeType::NUMBER)
  {
    if (tree->value.number == INT_MAX)
    {
      return INT_MAX;
    }
    return tree->value.number;
  }
  else if (tree->type == Tree::TreeType::OPER)
  {
    int left = interpret(tree->value.oper.left);
    int right = interpret(tree->value.oper.right);

    if (left == INT_MAX || right == INT_MAX)
    {
      return INT_MAX;
    }

    switch (tree->value.oper.operType)
    {
    case '+':
      return  left + right;

    case '-':
      return left - right;

    case '*':
      return left * right;

    case '/':
      return left / right;
    }
  }
}