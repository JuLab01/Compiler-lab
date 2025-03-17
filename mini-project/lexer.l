%{
#include "y.tab.h"      /* Include the generated header from Bison */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to convert a string to an integer
int string_to_int(const char* str) {
    return atoi(str);
}

// Helper function to convert a string to a float
double string_to_float(const char* str) {
    return atof(str);
}

// Helper function to copy a string literal (removing the surrounding quotes)
char* copy_string_literal(const char* str) {
    size_t len = strlen(str);
    if (len < 2) return strdup("");
    char* copied_str = (char*)malloc(len - 1); /* Allocates len-2 for the characters plus 1 for null terminator */
    if (copied_str == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(copied_str, str + 1, len - 2);  /* Copy without the quotes */
    copied_str[len - 2] = '\0';
    return copied_str;
}
%}

/* Define regular expression patterns for tokens */
DIGIT       [0-9]
INTEGER     {DIGIT}+
FLOAT       {DIGIT}*"."{DIGIT}+
IDENTIFIER  [a-zA-Z_][a-zA-Z0-9_]*
STRING      \"([^"]*)\"
BOOLEAN     "True"|"False"
KEYWORD_FOR "for"
KEYWORD_IN  "in"
KEYWORD_PRINT "print"
KEYWORD_ENDFOR "endfor"

%%
{KEYWORD_FOR}     { return FOR; }
{KEYWORD_IN}      { return IN; }
{KEYWORD_PRINT}   { return PRINT; }
{KEYWORD_ENDFOR}  { return ENDFOR; }
{BOOLEAN}         { yylval.bool_val = (strcmp(yytext, "True") == 0); return BOOLEAN; }
{INTEGER}         { yylval.int_val = string_to_int(yytext); return INTEGER; }
{FLOAT}           { yylval.float_val = string_to_float(yytext); return FLOAT; }
{STRING}          { yylval.string_val = copy_string_literal(yytext); return STRING; }
{IDENTIFIER}      { yylval.string_val = strdup(yytext); return IDENTIFIER; }

"="             { return ASSIGN; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return DIVIDE; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
","             { return COMMA; }
":"             { return COLON; }

/* Skip whitespace */
[ \t\n]+       ;

/* Catch-all for any unrecognized characters */
.               { fprintf(stderr, "Lexer error: Unknown character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
