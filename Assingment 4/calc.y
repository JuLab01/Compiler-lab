%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char *);
%}


%%




%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
