%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

/* Define the semantic value union */
%union {
    int int_val;
    double float_val;
    char* string_val;
    int bool_val;
}

/* Declare tokens along with their types */
%token <int_val> INTEGER
%token <float_val> FLOAT
%token <string_val> STRING
%token <bool_val> BOOLEAN
%token <string_val> IDENTIFIER
%token FOR IN PRINT ENDFOR
%token ASSIGN PLUS MINUS TIMES DIVIDE LPAREN RPAREN LBRACKET RBRACKET COMMA COLON

%start program

%%

program:
    statement_list
    ;

statement_list:
    statement_list statement
    | /* empty */
    ;

statement:
    assignment_statement
    | print_statement
    | for_loop
    ;

assignment_statement:
    IDENTIFIER ASSIGN expression
        { 
            printf("Rule: assignment_statement: %s = <expression>\n", $1);
            free($1); 
        }
    ;

print_statement:
    PRINT LPAREN expression RPAREN
        { printf("Rule: print_statement: print(<expression>)\n"); }
    ;

for_loop:
    FOR IDENTIFIER IN iterable COLON statement_list ENDFOR
        { 
            printf("Rule: for_loop: for %s in <iterable>:\n  <statement_list>\nendfor\n", $2);
            free($2); 
        }
    ;

iterable:
    IDENTIFIER
        { 
            printf("Rule: iterable: IDENTIFIER (%s)\n", $1); 
            free($1); 
        }
    | list
    | string_literal
    | range
    ;

expression:
    arithmetic_expression
    | list
    ;

arithmetic_expression:
    term
    | arithmetic_expression PLUS term
        { printf("Rule: arithmetic_expression: <arithmetic_expression> + <term>\n"); }
    | arithmetic_expression MINUS term
        { printf("Rule: arithmetic_expression: <arithmetic_expression> - <term>\n"); }
    ;

term:
    factor
    | term TIMES factor
        { printf("Rule: term: <term> * <factor>\n"); }
    | term DIVIDE factor
        { printf("Rule: term: <term> / <factor>\n"); }
    ;

factor:
    LPAREN arithmetic_expression RPAREN
        { printf("Rule: factor: (<arithmetic_expression>)\n"); }
    | literal
    | IDENTIFIER
        { 
            printf("Rule: factor: IDENTIFIER (%s)\n", $1);
            free($1);
        }
    ;

literal:
    integer_literal
    | float_literal
    | string_literal
    | boolean_literal
    ;

integer_literal:
    INTEGER
        { printf("Rule: integer_literal: INTEGER (%d)\n", $1); }
    ;

float_literal:
    FLOAT
        { printf("Rule: float_literal: FLOAT (%f)\n", $1); }
    ;

string_literal:
    STRING
        { 
            printf("Rule: string_literal: STRING (%s)\n", $1);
            free($1);
        }
    ;

boolean_literal:
    BOOLEAN
        { printf("Rule: boolean_literal: BOOLEAN (%d)\n", $1); }
    ;

list:
    LBRACKET element_list_opt RBRACKET
        { printf("Rule: list: [<element_list_opt>]\n"); }
    ;

range:
    LBRACKET 

element_list_opt:
    element_list
    | /* empty */
    ;

element_list:
    expression
    | element_list COMMA expression
        { printf("Rule: element_list: <element_list> , <expression>\n"); }
    ;

%%

void yyerror(const char *s) {
    extern char *yytext;
    fprintf(stderr, "Parse error near '%s': %s\n", yytext, s);
    exit(1);
}

int main() {
    extern FILE *yyin;
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        perror("Error opening input file");
        return 1;
    }
    if (yyparse() == 0) {
        printf("Parsing successful!\n");
    } else {
        fprintf(stderr, "Parsing failed!\n");
    }
    if (yyin) fclose(yyin);
    return 0;
}
