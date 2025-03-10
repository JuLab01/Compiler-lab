%{
#include <stdlib.h>
#include <string.h>
void yyerror(char *);
#include "y.tab.h"
%}

%%

A   { return A; }
B   { return B; }
\n  { return '\n'; }
[ \t] ; //tabs are skipped
.   {yyerror("invalid character"); return *yytext; } 

%%

int yywrap(void) {
    return 1;
}
