#include <stdio.h>
#include <assert.h>

bool stmt(const char * s, unsigned int& result);
bool add(const char * &s, unsigned int& result);
bool op2(const char * &s, char &c);
bool mul(const char * &s, unsigned int& result);
bool op1(const char * &s, char &symbol);
bool prim(const char * &s, unsigned int& result);
bool digit(const char * &s, unsigned int& result);
int parse(const char * s);
bool add1(const char * &s, unsigned int& result);

bool stmt(const char * s, unsigned int& result)
{
  bool validAdd = add(s, result);
  if ( validAdd && s[0] == ';')
  {
    s++;
    return true;
  }
  return false;
}

bool add(const char * &s, unsigned int& result)
{
  if (mul(s, result))
  {
    return add1(s,result);
  }
  return false;
}

bool add1(const char * &s, unsigned int& result)
{
  unsigned int m;
  char symbol;

    if (op2(s, symbol))
    {
      if (mul(s, m))
      {
        switch (symbol)
        {
        case '+': result = result + m;
          break;
        case '-': result = result - m;
          break;
        }
        add1(s,result);
      }
      else
      {
        return false;
      }
    }
    return true;
}

bool op2(const char * &s, char &c)
{
  if(s[0] == '+' || s[0] == '-')
  {
    c=s[0];
    s++;
    return true;
  }
  else 
  {
    return false;
  }
}

bool mul(const char * &s, unsigned int& result)
{
  unsigned int m;
  if (prim(s, m))
  {
    char symbol;
    if (op1(s, symbol))
    {
      unsigned int p;
      if(prim(s,p))
      {
        switch(symbol)
        {
        case '*': result = m*p;
          break;
        case '/': result = m/p;
          break;
        }
        return true;
      }
    }
    result = m;
    return true;
  }
  return false;
}

bool op1(const char * &s, char &symbol)
{
  if(s[0] == '*' || s[0] == '/')
  {
    symbol=s[0];
    s++;
    return true;
  }
  else 
  {
    return false;
  }
}


bool prim(const char * &s, unsigned int& result)
{
  if(s[0] =='(')
  {
    s++;
    unsigned int a;
    if(add(s, a))
    {
      result = a;
    }
    if (s == NULL || s[0] != ')')
    {
      return false;
    }
    s++;
    return true;
  }
  else if (digit(s,result))
  {
    return true;
  }
  return false;
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

enum class Status
{
  OK,
  WRONG_RESULT,
  SYNTAX_ERROR
};


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


int main()
{
  assert(parse("1;", 1) == Status::OK);
  assert(parse("1+2;", 3) == Status::OK);
  assert(parse("1+2+3;", 6) == Status::OK);
  assert(parse("1+2+3+4;", 10) == Status::OK);

  assert(parse("1;", 1) == Status::OK);
  assert(parse("1-2;", -1) == Status::OK);
  assert(parse("1-2-3;", -4) == Status::OK);
  assert(parse("1-2-3-4;", -8) == Status::OK);

  assert(parse("(6-2)*2;", 8) == Status::OK);
  assert(parse("(6-2)*2;", 7) == Status::WRONG_RESULT);
  assert(parse("(6-2)*2", 8) == Status::SYNTAX_ERROR);

  char wait = getc(stdin);
  return 0;
}