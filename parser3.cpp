#include <stdio.h>
#include <assert.h>

enum class Status
{
  OK,
  WRONG_RESULT,
  SYNTAX_ERROR
};

bool stmt(const char * s, unsigned int& result);
bool add(const char * &s, unsigned int& result);
bool mul(const char * &s, unsigned int& result);
bool prim(const char * &s, unsigned int& result);
bool digit(const char * &s, unsigned int& result);
bool integer(const char * &s, unsigned int& result);
Status parse(const char * s, int expect);

bool stmt(const char * s, unsigned int& result)
{
  bool validAdd = add(s, result);
  if (validAdd && s[0] == ';')
  {
    s++;
    return true;
  }
  return false;
}

bool add(const char * &s, unsigned int& result)
{
  if (!mul(s, result))
  {
    return false;
  }

  unsigned int p;
  while (true)
  {
    switch (*s)
    {
    case '+':
      s++;
      if (!mul(s, p))
      {
        return false;
      }
      result += p;
      break;
    case '-':
      s++;
      if (!mul(s, p))
      {
        return false;
      }
      result -= p;
      break;
    default:
      break;
    }
  }
  return true;
}

bool mul(const char * &s, unsigned int& result)
{
  if (!prim(s, result))
  {
    return false;
  }

  unsigned int p;
  while (true)
  {
    switch (*s)
    {
    case '*':
      s++;
      if (!prim(s, p))
      {
        return false;
      }
      result *= p;
      break;
    case '/':
      s++;
      if (!prim(s, p))
      {
        return false;
      }
      result /= p;
      break;
    default:
      break;
    }
  }
  return true;
}


bool prim(const char * &s, unsigned int& result)
{
  if (s[0] == '(')
  {
    s++;
    if (!add(s, result) || s[0] != ')')
    {
      return false;
    }
    else
    {
      s++;
      return true;
    }
  }
  else
  {
    return (integer(s, result));
  }
}

bool integer(const char * &s, unsigned int& result)
{
  unsigned int i{ 0 };
  if (digit(s, i))
  {
    result = i;
    while (digit(s, i))
    {
      result = 10 * result + i;
    }
    return true;
  }
  else
  {
    return false;
  }
}

bool digit(const char * &s, unsigned int& result)
{
  if (s[0] >= '0' && s[0] <= '9')
  {
    result = s[0] - '0';
    s++;
    return true;
  }
  else
  {
    return false;
  }
}

Status parse(const char * s, int expect)
{
  unsigned int result;
  if (!stmt(s, result))
  {
    return Status::SYNTAX_ERROR;
  }
  else if (result == expect)
  {
    return Status::OK;
  }
  else
  {
    return Status::WRONG_RESULT;
  }
}

void run_asserts()
{
  assert(parse("1;", 1) == Status::OK);
  assert(parse("1+2;", 3) == Status::OK);
  assert(parse("1+2+3;", 6) == Status::OK);
  assert(parse("1+2+3+4;", 10) == Status::OK);

  assert(parse("1++;", 1) == Status::SYNTAX_ERROR);

  assert(parse("1;", 1) == Status::OK);
  assert(parse("1-2;", -1) == Status::OK);
  assert(parse("1-2-3;", -4) == Status::OK);
  assert(parse("1-2-3-4;", -8) == Status::OK);

  assert(parse("9*1;", 9) == Status::OK);
  assert(parse("9*1*3;", 27) == Status::OK);
  assert(parse("1*2*3*4;", 24) == Status::OK);

  assert(parse("2/1;", 2) == Status::OK);
  assert(parse("5/2/1;", 2) == Status::OK);
  assert(parse("9/2/3;", 1) == Status::OK);

  assert(parse("9/1/3;", 1) == Status::WRONG_RESULT);
  assert(parse("9/2/1/1;", 2) == Status::WRONG_RESULT);

  assert(parse("/1/3;", 1) == Status::SYNTAX_ERROR);
  assert(parse("9//3;", 1) == Status::SYNTAX_ERROR);
  assert(parse("9/1/;", 1) == Status::SYNTAX_ERROR);

  assert(parse("(1-2)-(3-4);", 0) == Status::OK);
  assert(parse("(1-2)-(3+4);", -8) == Status::OK);
  assert(parse("(1-2)+(3-4);", -2) == Status::OK);
  assert(parse("(1+2)-(3+4);", -4) == Status::OK);
  assert(parse("(1-2)-(3-4)-(5-6);", 1) == Status::OK);

  assert(parse("((4/3)/(2/1));", 0) == Status::OK);
  assert(parse("(((8/4)/1)*5);", 10) == Status::OK);
  assert(parse("((5/2)*(2*(7/3)));", 8) == Status::OK);
  assert(parse("((3*4)*(1*2/(6-5)));", 24) == Status::OK);
  assert(parse("(9/(2)/(8))+((4)-(1)/2);", 4) == Status::OK);

  assert(parse("((40/3)/(2/1));", 6) == Status::OK);
  assert(parse("(1+23)-(3+17);", 4) == Status::OK);
  assert(parse("90/9/3;", 3) == Status::OK);
  assert(parse("10*2*30;", 600) == Status::OK);

  assert(parse("(6-2)*2;", 8) == Status::OK);
  assert(parse("(6-2)*2;", 7) == Status::WRONG_RESULT);
  assert(parse("(6-2)*2", 8) == Status::SYNTAX_ERROR);
}

int main()
{
  run_asserts();
  char wait = getc(stdin);
  return 0;
}