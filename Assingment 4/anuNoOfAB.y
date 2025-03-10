%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char *);
%}

%token A 
%token B

%%

program:
    program expr1 '\n' { 
        printf("Valid String\n");
    }
    | error '\n' {
        printf("Invalid String\n");
    }
    ;

expr1: A expr2
    | A expr1  { $$ = $2; } ;

expr2: B
    | B expr2  { $$ = $2; } ;
    


%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
