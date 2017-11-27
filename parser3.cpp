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
bool op2(const char * &s, char &c);
bool mul(const char * &s, unsigned int& result);
bool op1(const char * &s, char &symbol);
bool prim(const char * &s, unsigned int& result);
bool digit(const char * &s, unsigned int& result);
bool integer(const char * &s, unsigned int& result);
Status parse(const char * s, int expect);

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
    unsigned int m;
    char symbol;
    
    while (true)
    {
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
          continue;
        }
        else
        {
          return false;
        }
      }
      else
      {
        break;
      }
    }
    return true;
  }
  else
  {
    return false;
  }
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
  if (prim(s, result))
  {
    char symbol;
    unsigned int p;
    while (true)
    {
      if (op1(s, symbol))
      {
        if (prim(s, p))
        {
          switch (symbol)
          {
          case '*': result = result*p;
            break;
          case '/': result = result / p;
            break;
          default: return false;
          }
          continue;
        }
        else
        {
          return false;
        }
      }
      return true;
    }
  }
  else
  {
    return false;
  }
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
    if(!add(s, result) && s[0] != ')')
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

int main()
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

  char wait = getc(stdin);
  return 0;
}