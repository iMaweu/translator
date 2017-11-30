#ifndef AST_H
#define AST_H

struct TreeAdd;

struct TreeDigit
{
  int value;
};

struct TreeNum
{
  enum TreeNumType {NUM1, NUM2} type;
  union TreeNumPayload
  {
    struct
    {
      TreeNum * num;
      TreeDigit * digit;
    } num2;
    TreeDigit * num1;
  } payload;

  TreeNum(TreeNum * _num, TreeDigit * _digit) : type{ TreeNumType::NUM2 }, payload { _num, _digit } {}
  TreeNum(TreeDigit * _digit) : type{ TreeNumType::NUM1 }
  {
    payload.num1 = _digit;
  }
};

struct TreePrim
{
  enum TreePrimType {NUM, ADD} type;
  union TreePrimPayload
  {
    TreeAdd * add;
    TreeNum * num;
  } payload;

  TreePrim(TreeAdd * _add) : type{ TreePrimType::ADD }, payload{ _add } {}
  TreePrim(TreeNum * _num) : type{ TreePrimType::NUM }
  {
    payload.num = _num;
  }
};

struct TreeMul
{
  enum TreeMulType {MUL1, MUL2} type;
  union TreeMulPayload
  {
    struct
    {
      TreeMul * mul;
      TreePrim * prim;
      char operation;
    } mul2;
    TreePrim * mul1;
  } payload;

  TreeMul(TreeMul * _mul, TreePrim * _prim, char _op) : type{ TreeMulType::MUL2 }, payload{ _mul,_prim,_op } {}
  TreeMul(TreePrim * _prim) : type{ TreeMulType::MUL1 }
  {
    payload.mul1 = _prim;
  }
};

struct TreeAdd
{
  enum TreeAddType {ADD1, ADD2} type;
  union TreeAddPayload
  {
    struct
    {
      TreeAdd * add;
      TreeMul * mul;
      char operation;
    } add2;
    TreeMul * add1;
  } payload;

  TreeAdd(TreeAdd * _add, TreeMul * _mul, char _op) : type{ TreeAddType::ADD2 }, payload { _add, _mul,  _op } {}
  TreeAdd(TreeMul * _mul) : type{ TreeAddType::ADD1 }
  {
    payload.add1 = _mul;
  }
};

struct TreeStmt
{
  TreeAdd * add;
  TreeStmt(TreeAdd * _add) : add(_add) {}
};

TreeDigit * generate_digit(int d);
TreeNum *generate_num1(TreeDigit *);
TreeNum *generate_num2(TreeNum *,TreeDigit *);
TreePrim *generate_prim(TreeNum *);
TreePrim *generate_prim(TreeAdd *);
TreeMul *generate_mul1(TreePrim *);
TreeMul *generate_mul2(TreeMul *,TreePrim *, char);
TreeAdd *generate_add1(TreeMul *);
TreeAdd *generate_add2(TreeAdd *,TreeMul*,char);
TreeStmt *generate_stmt(TreeAdd *);

void printStmt(const TreeStmt * tree);
void printAdd(const TreeAdd * tree);
void printMul(const TreeMul * tree);
void printPrim(const TreePrim * tree);
void printNum(const TreeNum * tree);
void printDigit(const TreeDigit * tree);

void clearStmt(TreeStmt * tree);
void clearAdd(TreeAdd * tree);
void clearMul(TreeMul * tree);
void clearPrim(TreePrim * tree);
void clearNum(TreeNum * tree);
void clearDigit(TreeDigit * tree);

void test();

int calculateTree(TreeStmt *);
#endif
