#ifndef PARSER_H
#define PARSER_H

enum class Status
{
  OK,
  WRONG_RESULT,
  SYNTAX_ERROR
};

Status parse(const char * s, int expect);

std::shared_ptr<Tree> stmt(const char * &s);
std::shared_ptr<Tree> add(const char * &s);
std::shared_ptr<Tree> mul(const char * &s);
std::shared_ptr<Tree> prim(const char * &s);
std::shared_ptr<Tree> num(const char * &s);

#endif