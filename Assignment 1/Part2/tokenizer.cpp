#include<iostream>
#include "./regex.cpp"
#include<unordered_map>
#include<regex>
#include<fstream>
#include <iomanip>

using namespace std;

typedef struct {
	string tokenType;
	string token;
} Token;


vector<Regex> tokenPatterns = init();

void printTokens(vector<Token>& tokens) {
    if (tokens.size() == 0) return;

    cout << left << setw(25) << "Token"
            << setw(25) << "Type"
            << setw(15) << "Column" << "\n";
    cout << string(65, '-') << "\n";

    int column = 1;
    for (const auto& entry : tokens) {
        cout << left << setw(25) << entry.token
                << setw(25) << entry.tokenType
                << setw(15) << column++ << "\n";
}

}

void tokenizeLine(string& line) {
    vector<Token> tokens;

	string remaining = line;
    while(remaining.length() > 0) {

        bool isMatched = false;
        

        for(const Regex& tokenPattern : tokenPatterns) {
            regex pattern(tokenPattern.regexPattern);
            smatch match;
            
            if(regex_search(remaining, match, pattern, regex_constants::match_continuous)) {
                string token = match.str();
                if(token.length() == 0) break;

                tokens.push_back({tokenPattern.type, token});
                remaining = match.suffix().str();
                isMatched = true;
                break;
            }

        }
        if(!isMatched && remaining.length() > 0) {
            int i = 0;
            while(i< remaining.length() && isspace(remaining[i])) i++;
            if(i==0){
                tokens.push_back({"UNKNOWN", string(1, remaining[0])});
                remaining = remaining.substr(1);
                continue;
            }
            remaining = remaining.substr(i);
        }

        

    }
    
    printTokens(tokens);
    
}

int main() {
    init();
    string line = "";
    ifstream file("test.cpp");
    if (file.is_open()) {
        int LineNo = 1;
        while (getline(file, line)) {
            cout << "Line " << LineNo++ << ":" << endl;
            tokenizeLine(line);
            cout << endl<<endl;
        }
        file.close();
    }
    

}