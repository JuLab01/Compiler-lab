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
    program expr '\n' { 
        printf("Valid String\n");
    }
    | error '\n' {
        printf("Invalid String\n");
    }
    ;

expr: A B
    | A expr B { $$ = $2; } ;

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
