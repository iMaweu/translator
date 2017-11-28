#include<iostream>

struct Tree
{
  Tree * left;
  Tree * right;
};

void print(const Tree * tree)
{
  if (tree == nullptr)
  {
    std::cout << "NULL";
  }
  else
  {
    std::cout << "Tree(";
    print(tree->left);
    std::cout << ",";
    print(tree->right);
    std::cout << ")";
  }

}

Tree * generateTree()
{
  Tree * root = new Tree{ nullptr, nullptr };
  root->left = new Tree{nullptr, nullptr};
  return root;
}

void clearTree(Tree * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  clearTree(tree->left);
  clearTree(tree->right);
  delete tree;
}

int main()
{
  Tree * t = generateTree();
  print(t);
  clearTree(t);
  //print(t);
  char wait; std::cin >> wait;
  return 0;
}