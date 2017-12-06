#ifndef AST_H
#define AST_H
#include <memory>

struct Tree
{
  Tree(const std::shared_ptr<Tree>  _left, const std::shared_ptr<Tree> _right, const char _operType) : type{ OPER }, value { _left, _right, _operType } {}
  Tree(const int _number) : type{ NUMBER }, value { _number } {}
  Tree() : type{ NUMBER }, value { 0 } {}

  enum TreeType {NUMBER,OPER} type;

  union TreePayload
  {
    TreePayload(const std::shared_ptr<Tree> _left, const std::shared_ptr<Tree> _right, const char _operType) : oper{ _left, _right, _operType } {}
    TreePayload(const int _number) : number{ _number } {}
    ~TreePayload() {}

    struct operation
    {
      operation(const std::shared_ptr<Tree> _left, const std::shared_ptr<Tree> _right, const char _operType) : left{ _left }, right{ _right }, operType { _operType } {}

      std::shared_ptr<Tree> left;
      std::shared_ptr<Tree> right;
      char operType;
    } oper;

    int number;

  } value;
};

void printTree(const std::shared_ptr<Tree> tree);

//void clearTree(Tree * &tree);

int interpret(const std::shared_ptr<Tree> tree);

#endif
