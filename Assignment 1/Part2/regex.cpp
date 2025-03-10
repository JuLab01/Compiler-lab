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


    tokenPatterns.push_back({"COMMENT", R"(\/\/.*$|\/\*[\s\S]*?\*\/)"});
    tokenPatterns.push_back({"STRING", R"("([^"\\]|\\.)*"|'([^'\\]|\\.)*')"});
    tokenPatterns.push_back({"PREPROCESSOR_DIRECTIVE", R"(#include)"});
    tokenPatterns.push_back({"POINTER KEYWORD", R"((int\*|float\*|char\*|void\*))"});
    tokenPatterns.push_back({"KEYWORD", R"(\b(int|float|double|char|void|if|else|while|for|return|break|continue|switch|case|default|bool|string|null|true|false|std|namespace|using|include|setw|printf|scanf|getchar|malloc|free|calloc|realloc|gets|puts|strlen|strcpy|strcat|strcmp|strncmp|memcpy|memset|memmove|printf|scanf|getchar|malloc|free|calloc|realloc|gets|puts|strlen|strcpy|strcat|strcmp|strncmp|memcpy|memset|memmove)\b)"});
    tokenPatterns.push_back({"CPP SPECIFIC OPERATOR", R"(>>|<<|::|->|->\*|,|;|\.)"});
    tokenPatterns.push_back({"PARENTHESIS", R"(\(|\))"});
    tokenPatterns.push_back({"BRACKET", R"(\[|\])"});
    tokenPatterns.push_back({"BRACE", R"(\{|\})"});
    tokenPatterns.push_back({"NUMERIC OPERATOR", R"(\+|\-|\*|\/|=|==|!=|<|>|<=|>=|\+\+|\-\-)"});
    tokenPatterns.push_back({"LOGICAL OPERATOR", R"(\&\&|\|\|)"});
    tokenPatterns.push_back({"FLOATING POINT CONSTANT", R"(\b\d+\.\d+\b)"});
    tokenPatterns.push_back({"INTEGER CONSTANT", R"(\b\d+\b)"});
    tokenPatterns.push_back({"POINTER DE-REFERENCING", R"([a-zA-Z_][a-zA-Z0-9_]*\*)"});
    tokenPatterns.push_back({"IDENTIFIER", R"([a-zA-Z_][a-zA-Z0-9_]*)"});

    
    

    return tokenPatterns;
}

