%{ 
#include<stdio.h> 
#include<string.h> 
int isOk = 0;
%} 

%% 
((A+)(B+))  {printf("%s matches \n", yytext);} 
.+  {printf("Invalid Input\n");}

%% 
int yywrap(){}

int main() 
{ 
	printf("Enter a Message: ");
	yylex(); 


	return 0; 
} 
