BIN = 0|1

%{ 
#include<stdio.h> 
#include<string.h> 
%} 

%%

(1(1|0|.)*101) {printf("Got message!");}
"\n" {printf("Enter a Message: ");}

%%
int yywrap(void){} 
int main(){
    printf("Enter a Message: ");
    yylex();
}


