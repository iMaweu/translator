#ifndef AST_H
#define AST_H
struct Tree;

enum class TreeType { ADD, MUL, PRIM, NUM };

union TreePayload
{
  TreePayload::TreePayload() {}
  TreePayload::TreePayload(Tree * _branch) : branch(_branch) {}
  TreePayload::TreePayload(int _value) : value(_value) {}
  TreePayload::TreePayload(Tree * _left, Tree * _right) 
  {
    branches.left = _left;
    branches.right = _right;
  }

  int value;
  Tree * branch;
  struct
  {
    Tree * left;
    Tree * right;
  } branches;
};

struct Tree
{
  TreeType type;
  TreePayload payload;
};

void print(const Tree * tree);
Tree * generate(TreeType treeType, TreePayload treePayload);
void clear(Tree * tree);

#endif
