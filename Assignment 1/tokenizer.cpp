#include<iostream>
#include<bits/stdc++.h>
#include<regex>
#include <fstream>
using namespace std;

vector<string> tokenizer(string line) {
    vector<string> words;
    string token = "";
    regex alpha_numeric_character("[0-9]|[A-Za-z]");  

    for (size_t i = 0; i < line.length(); i++) {
        char c = line[i];
        
        if (c == ' ') {  
            if (token.empty()) continue;
            words.push_back(token);  
            token = "";  
            
        } else {
            if (!regex_match(string(1, c), alpha_numeric_character)) {  
                if (!token.empty()) { 
                    words.push_back(token);
                    token = "";
                }
                words.push_back(string(1, c));  
            } else {
                token += c;  
            }
        }
    }

    if (!token.empty()) {
        words.push_back(token);
    }

    return words;
}

int main() {
    string filePath = "test.txt";

    //read line from file
    ifstream file(filePath);
    string cppLine;
    getline(file, cppLine);
    
    vector<string> tokens = tokenizer(cppLine);
    for (size_t i = 0; i < tokens.size(); i++) {
        cout << tokens[i] << "  ";
    }

    return 0;
}
