
%{

#include <stdio.h>
#include <string.h>
int count = -1;
%}

%% 
((A+)(B+)) {count = 0;
            for(int i = 0; i < strlen(yytext); i++){
                if(yytext[i] == 'A') count++;
                if(yytext[i] == 'B') count--;
            }
}

.+  {printf("Invalid Input\n");}


"\n" {
    
    if(count == 0) printf("Equal\n");
    else if( count == -1) ;
    else printf("Unequal\n");
    count = -1;
    printf("Enter next Message: ");
}

%% 
int yywrap(){ return 1;}
    
int main() 
{ 
	printf("Enter a Message: ");
	yylex(); 
    


	return 0; 
} 

