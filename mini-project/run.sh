#!/bin/sh

lex lexer.l
yacc -d parser.y
gcc lex.yy.c y.tab.c -o parser
./parser