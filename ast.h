#ifndef AST_H
#define AST_H

struct Tree
{
  enum TreeType {NUMBER,OPER} type;
  union 
  {
    struct
    {
      Tree * left;
      Tree * right;
      char operType;
    } oper;
    int number;
  } value;

  Tree(Tree* _left, Tree * _right, char _operType) : type{ OPER }, value { _left, _right, _operType } {}
  Tree(int _number) : type{ NUMBER }
  {
    value.number = _number;
  }
};

void printTree(const Tree * tree);

void clearTree(Tree * &tree);

int interpret(const Tree * tree);

#endif
