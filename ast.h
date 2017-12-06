#ifndef AST_H
#define AST_H
#include <memory>

struct Tree;

typedef std::unique_ptr<Tree>  Tree_ptr;

struct Tree
{
  Tree(Tree_ptr&& _left, Tree_ptr&& _right, const char _operType) : type{ OPER }, value { std::move(_left), std::move(_right), _operType  } {}
  Tree(const int _number) : type{ NUMBER }, value { _number } {}
  Tree() : type{ NUMBER }, value { 0 } {}

  enum TreeType {NUMBER,OPER} type;

  union TreePayload
  {
    TreePayload(Tree_ptr&& _left, Tree_ptr&& _right, const char _operType) : oper{ std::move(_left), std::move(_right), _operType } {}
    TreePayload(const int _number) : number{ _number } {}
    ~TreePayload() {}

    struct operation
    {
      operation& operator=(const operation &) = delete;
      operation(Tree_ptr&& _left, Tree_ptr&& _right, const char _operType) : left{ std::move(_left) }, right{ std::move(_right) }, operType{ _operType } {}

      Tree_ptr left;
      Tree_ptr right;
      char operType;
    } oper;

    int number;

  } value;
};

void printTree(const Tree_ptr&& tree);

//void clearTree(Tree * &tree);

int interpret(const Tree_ptr&& tree);

#endif
