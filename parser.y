%{
#include <assert.h>
#include <limits.h>
#include <ctype.h>
#include <stdio.h>

#define YYSTYPE int

int yylex ();
void yyerror (char const *s);

%}

%define api.value.type {int}
%define parse.error verbose

%token INTEGER
%token OVERFLOW

%%
stmt:  add ';' {printf("result = %d\n", $1);}
;

add:  mul         {$$ = $1;}
    | add '+' mul {$$ = $1 + $3;}
    | add '-' mul {$$ = $1 - $3;}

;

mul:    prim       {$$=$1;}
    | mul '*' prim {$$ = $1 * $3;}
    | mul '/' prim {$$ = $1 / $3;}
;

prim:   INTEGER       {$$=$1;}
    |'('add')'      {$$ = $2;}
;

%%

int yylex ()
{
  char c = getc(stdin);
  if (isdigit(c))
  {
    yylval = 0;
    while (isdigit(c))                
    {
      yylval = yylval * 10 + (c - '0');
      c = getc(stdin);
    }
    ungetc(c, stdin);
    return INTEGER;
  }
  else if (c == '\n')
  {  
    return 0;
  }
  else
  {
    return c;                                
  }
}

void yyerror (char const *s)
{
  printf("%s\n", s);
}

int main()
{
  return yyparse();
}
