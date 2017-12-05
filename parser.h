#ifndef PARSER_H
#define PARSER_H

enum class Status
{
  OK,
  WRONG_RESULT,
  SYNTAX_ERROR
};

Status parse(const char * s, int expect);

Tree * stmt(const char * &s);
Tree * add(const char * &s);
Tree * mul(const char * &s);
Tree * prim(const char * &s);
Tree * num(const char * &s);

void run_asserts();

#endif