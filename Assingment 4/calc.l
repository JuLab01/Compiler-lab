%{
#include <stdlib.h>
#include <string.h>
void yyerror(char *);
#include "y.tab.h"
%}

%%


%%

int yywrap(void) {
    return 1;
}
