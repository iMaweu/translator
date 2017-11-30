#ifndef AST_H
#define AST_H
struct Tree;

enum class TreeType { STMT,ADD1,ADD2, MUL1, MUL2, PRIM, NUM1, NUM2, DIGIT};

union TreePayload
{
  TreePayload::TreePayload(Tree * _branch) : branch(_branch) {}
  TreePayload::TreePayload(int _value) : value(_value) {}
  TreePayload::TreePayload(Tree * _left, Tree * _right, char _operation) 
  {
    branches.left = _left;
    branches.right = _right;
    branches.operation = _operation;
  }

  int value;
  Tree * branch;
  struct
  {
    Tree * left;
    Tree * right;
    char operation;
  } branches;
};

struct Tree
{
  TreeType type;
  TreePayload payload;
};

Tree *generate_num1(Tree *);
Tree *generate_num2(Tree *,Tree *);
Tree *generate_prim(Tree *);
Tree *generate_add1(Tree *);
Tree *generate_mul1(Tree *);
Tree *generate_add2(Tree *,Tree*,char);
Tree *generate_mul2(Tree *,Tree*, char);
Tree *generate_stmt(Tree*);
Tree *generate_digit(int);

void clear(Tree * tree);

void printTree(const Tree * tree);
void print(const Tree * tree);

void test();

int calculateTree(Tree *);
#endif
