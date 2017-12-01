#include <stdio.h>

#include "ast.h"
#include "parser.h"

int main()
{
  test();
  run_asserts();

  char wait = getc(stdin);
  return 0;
}