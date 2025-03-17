#include<iostream>
#include<vector>
#include<string>
using namespace std;

typedef struct{
    string type;
    string regexPattern;
}Regex;


vector<Regex> init(){
    vector<Regex> tokenPatterns;


    tokenPatterns.push_back({"COMMENT", R"(#.*$)"});

    // Python string literals: matches both double-quoted and single-quoted strings.
    tokenPatterns.push_back({"STRING", R"("([^"\\]|\\.)*"|'([^'\\]|\\.)*')"});

    
    // // Python keywords: include common Python reserved words.
    // tokenPatterns.push_back({"KEYWORD", 
    //     R"(\b(def|class|if|elif|else|while|for|in|try|except|finally|with|as|return|break|continue|pass|import|from|global|nonlocal|lambda|True|False|None|and|or|not|is)\b)"
    // });

    // // Python operators: arithmetic and comparison operators.
    tokenPatterns.push_back({"OPERATOR", R"([\+\-\*\/%=\>\<\!]+)"});

    // // Parentheses, brackets, and braces used in Python.
    // tokenPatterns.push_back({"PARENTHESIS", R"([\(\)])"});
    // tokenPatterns.push_back({"BRACKET", R"([\[\]])"});
    // tokenPatterns.push_back({"BRACE", R"([\{\}])"});

    // // Floating point constant: a sequence of digits with a dot.
    // tokenPatterns.push_back({"FLOATING POINT CONSTANT", R"(\b\d+\.\d+\b)"  });

    // // Integer constant: a sequence of digits.
    // tokenPatterns.push_back({"INTEGER CONSTANT", R"(\b\d+\b)"});

    // // Python identifiers: start with a letter or underscore, followed by letters, digits or underscores.
    // tokenPatterns.push_back({"IDENTIFIER", R"([a-zA-Z_][a-zA-Z0-9_]*)"});

    

    return tokenPatterns;
}

