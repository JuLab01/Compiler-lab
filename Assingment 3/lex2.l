

%{

#include <stdio.h>
#include <string.h>

%}

%%

([A-Z]([a-z0-9]*#))  {printf("%s matches\n", yytext);}
.+  {printf("Invalid Input\n");}
"\n" {printf("Enter a Message: ");}

%%

int yywrap(void){} 
int main(){
    printf("Enter a Message: ");
    yylex();
}

