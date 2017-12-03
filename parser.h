#ifndef PARSER_H
#define PARSER_H

enum class Status
{
  OK,
  WRONG_RESULT,
  SYNTAX_ERROR
};

Status parse(const char * s, int expect);

bool stmt(const char * &s, Tree * &tree);
bool add(const char * &s, Tree * &tree);
bool mul(const char * &s, Tree * &tree);
bool prim(const char * &s, Tree * &tree);
bool num(const char * &s, Tree * &tree);

void run_asserts();

#endif