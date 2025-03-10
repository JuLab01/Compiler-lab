%{
    #include <stdio.h>
    int yylex(void);
    void yyerror(char *);
%}


%token INTEGER 
%left '-' 
%left '+'  
%left '*' 
%left '/'       

%{
    void yyerror(char *);
    int yylex(void);
%}
%%
program:
        program statement '\n'
        |
        ;
statement:
        expr { printf("Result: %d\n", $1); }
        ;
expr:
    INTEGER
    | expr '-' expr { $$ = $1 - $3; printf("- Result: %d \n",$$); } 
    | expr '+' expr { $$ = $1 + $3; printf("+ Result: %d \n",$$); }
    | expr '*' expr { $$ = $1 * $3; printf("* Result: %d \n",$$); }
    | expr '/' expr { $$ = $1 / $3; printf("/ Result: %d \n",$$); }
    | '(' expr ')' { $$ = $2; }
    ;
%%



void yyerror(char *s) {
    printf("%s\n", s);
    return ;
}
int main(void) {
    yyparse();
    return 0;
}