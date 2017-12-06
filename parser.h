#ifndef PARSER_H
#define PARSER_H

enum class Status
{
  OK,
  WRONG_RESULT,
  SYNTAX_ERROR
};

Status parse(const char * s, int expect);

Tree_ptr stmt(const char * &s);
Tree_ptr add(const char * &s);
Tree_ptr mul(const char * &s);
Tree_ptr prim(const char * &s);
Tree_ptr num(const char * &s);

#endif