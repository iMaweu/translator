#ifndef PARSER_H
#define PARSER_H

enum class Status
{
  OK,
  WRONG_RESULT,
  SYNTAX_ERROR
};

bool stmt(const char * s, TreeStmt  * &tree);
bool add(const char * &s, TreeAdd * &tree);
bool mul(const char * &s, TreeMul * &tree);
bool prim(const char * &s, TreePrim * &tree);
bool digit(const char * &s, TreeDigit * &tree);
bool num(const char * &s, TreeNum * &tree);
Status parse(const char * s, int expect);

void run_asserts();

#endif