%{

#include <stdio.h>
#include <string.h>
#include <math.h>
int num = 0;
%}

%%

([0-9]+(\+|\-|\*|\/)[0-9]+) {
    char op;
    int i;
    for( i = 0; i < strlen(yytext); i++){
        if(yytext[i] == '+'){ op = '+'; break;}
        if(yytext[i] == '-') {op = '-'; break;}
        if(yytext[i] == '*') {op = '*';break;}
        if(yytext[i] == '/') {op = '/';break;}
    }

    int num1 = atoi(yytext+i+1);
    yytext[i] = '\0';
    int num2 = atoi(yytext);

    if(op == '+') num = num1 + num2;
    if(op == '-') num = num1 - num2;
    if(op == '*') num = num1 * num2;
    if(op == '/') num = num1 / num2;
}

"\n" {printf("Final value is %d\n", num);}

%%


int yywrap(){ return 1;}
    
int main() 
{ 
	printf("Initial value is 0\n");
	yylex(); 
    


	return 0; 
} 
