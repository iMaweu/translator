#include <assert.h>

#include "ast.h"

int calculateStmt(TreeStmt * tree)
{
  if (tree == nullptr)
  {
    // TODO: track errors
    assert(false);
  }
  return calculateAdd(tree->add);
}

int calculateAdd(TreeAdd * tree)
{
  if (tree == nullptr)
  {
    // TODO: track errors
    assert(false);
  }
  else if(tree->type == TreeAdd::TreeAddType::ADD1)
  {
    return calculateMul(tree->payload.add1);
  }
  else if (tree->type == TreeAdd::TreeAddType::ADD2)
  {
    switch (tree->payload.add2.operation)
    {
    case '+':
      return calculateAdd(tree->payload.add2.add) + calculateMul(tree->payload.add2.mul);
    case '-':
      return calculateAdd(tree->payload.add2.add) - calculateMul(tree->payload.add2.mul);
    }
    assert(false);
  }
}

int calculateMul(TreeMul * tree)
{
  if (tree == nullptr)
  {

  }
  else if (tree->type == TreeMul::TreeMulType::MUL1)
  {
    return calculatePrim(tree->payload.mul1);
  }
  else if (tree->type == TreeMul::TreeMulType::MUL2)
  {
    switch (tree->payload.mul2.operation)
    {
    case '*':
      return calculateMul(tree->payload.mul2.mul) * calculatePrim(tree->payload.mul2.prim);
    case '/':
      return calculateMul(tree->payload.mul2.mul) / calculatePrim(tree->payload.mul2.prim);
    }
    assert(false);
  }
}

int calculatePrim(TreePrim * tree)
{
  if (tree == nullptr)
  {
    // TODO: track errors
    assert(false);
  }
  else if (tree->type == TreePrim::TreePrimType::NUM)
  {
    return calculateNum(tree->payload.num);
  }
  else if (tree->type == TreePrim::TreePrimType::ADD)
  {
    return calculateAdd(tree->payload.add);
  }
  assert(false);
}

int calculateNum(TreeNum * tree)
{
  if (tree == nullptr)
  {
    // TODO: track errors
    assert(false);
  }
  else if (tree->type == TreeNum::TreeNumType::NUM1)
  {
    return calculateDigit(tree->payload.num1);
  }
  else if (tree->type == TreeNum::TreeNumType::NUM2)
  {
    return (calculateNum(tree->payload.num2.num)*10) + calculateDigit(tree->payload.num2.digit);
  }
  assert(false);
}

int calculateDigit(TreeDigit * tree)
{
  if (tree == nullptr)
  {
    // TODO: track errors
    assert(false);
  }
  return tree->value;
}