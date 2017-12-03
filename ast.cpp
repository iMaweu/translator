#include<iostream>
#include <assert.h>
#include <stdio.h>

#include "ast.h"

Tree *  generate_tree(Tree* _left, Tree * _right, char _operType)
{
  return new Tree{ _left,_right,_operType };
}

Tree * generate_branch(int number)
{
  return new Tree{ number };
}