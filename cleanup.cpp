#include "ast.h"

void clearStmt(TreeStmt * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  clearAdd(tree->add);
  delete tree;
}

void clearAdd(TreeAdd * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  switch (tree->type)
  {
  case TreeAdd::TreeAddType::ADD1:
    clearMul(tree->payload.add1);
    break;
  case TreeAdd::TreeAddType::ADD2:
    clearAdd(tree->payload.add2.add);
    clearMul(tree->payload.add2.mul);
    break;
  }
  delete tree;
}

void clearMul(TreeMul * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  switch (tree->type)
  {
  case TreeMul::TreeMulType::MUL1:
    clearPrim(tree->payload.mul1);
    break;
  case TreeMul::TreeMulType::MUL2:
    clearMul(tree->payload.mul2.mul);
    clearPrim(tree->payload.mul2.prim);
    break;
  }
  delete tree;
}

void clearPrim(TreePrim * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  switch (tree->type)
  {
  case TreePrim::TreePrimType::ADD:
    clearAdd(tree->payload.add);
    break;
  case TreePrim::TreePrimType::NUM:
    clearNum(tree->payload.num);
    break;
  }
  delete tree;
}

void clearNum(TreeNum * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  switch (tree->type)
  {
  case TreeNum::TreeNumType::NUM1:
    clearDigit(tree->payload.num1);
    break;
  case TreeNum::TreeNumType::NUM2:
    clearNum(tree->payload.num2.num);
    clearDigit(tree->payload.num2.digit);
    break;
  }
  delete tree;
}

void clearDigit(TreeDigit * tree)
{
  if (tree == nullptr)
  {
    return;
  }
  delete tree;
}