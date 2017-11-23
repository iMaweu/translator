%{
#include <ctype.h>
#include <stdio.h>

#define YYSTYPE int

int yylex ();
void yyerror (char const *s);

%}

%define api.value.type {int}
%token DIGIT

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

prim:   DIGIT       {$$=$1;}
    |'('add')'      {$$ = $2;}
;
%%

int yylex ()
{
  int c = getc(stdin);
  if (isdigit (c))                
  {
     yylval = c - '0';
     return DIGIT;
  }
  else if (c == '\n')
  {  
    return 0;
  }
  return c;                                
}

void yyerror (char const *s)
{
  printf("%s\n", s);
}

int main()
{
  return yyparse();
}
