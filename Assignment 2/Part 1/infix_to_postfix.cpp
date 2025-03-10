#include <stack>    
#include <string>
#include <unordered_map>
using namespace std;


string infixToPostfix(const string& regex) {
    string postfix;
    stack<char> operators;
    unordered_map<char, int> precedence = {
        {'*', 3}, 
        {'&', 2}, 
        {'+', 1}, 
        {'(', 0}  
    };

    for (char c : regex) {
        if (isalnum(c) || c == '.') { 
            postfix += c;
        } else if (c == '(') { 
            operators.push(c);
        } else if (c == ')') { 
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            if (!operators.empty()) operators.pop(); 
        } else { 
            while (!operators.empty() &&
                    precedence[operators.top()] >= precedence[c]) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}
