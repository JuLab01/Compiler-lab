#include<unordered_map>
#include<set>
#include<vector>
#include<iostream>
#include<string>
#include "./infix_to_postfix.cpp"
using namespace std;
int getID(){
    static int id = 0;
    return id++;
}
class NFA{
    unordered_map<int,unordered_map<char,set<int>>> transitions; // lets say ~ is epsilon
    int startState;
    int finalState;
    set<char> alphabets;
    friend class DFA;

    public:
    NFA(){
        startState = getID();
        finalState = getID();
    }

    NFA(char c){
        startState = getID(); 
        finalState = getID();  
        transitions[startState][c].insert(finalState);

        alphabets.insert(c);
    }

    NFA operator|(const NFA& other){
        NFA result;

        for(const pair<int,unordered_map<char,set<int>>>& transition : transitions){
            result.transitions[transition.first] = transition.second;
        }

        for(const pair<int,unordered_map<char,set<int>>>& transition : other.transitions){
            result.transitions[transition.first] = transition.second;
        }

        result.alphabets.insert(alphabets.begin(), alphabets.end());
        result.alphabets.insert(other.alphabets.begin(), other.alphabets.end());

        result.transitions[result.startState]['~'].insert(startState);
        result.transitions[result.startState]['~'].insert(other.startState);
        result.transitions[finalState]['~'].insert(result.finalState);
        result.transitions[other.finalState]['~'].insert(result.finalState);

        return result;
    }

    NFA operator&(const NFA& other){// concatenation
        NFA result;

        for(const pair<int,unordered_map<char,set<int>>>& transition : transitions){
            result.transitions[transition.first] = transition.second;
        }

        for(const pair<int,unordered_map<char,set<int>>>& transition : other.transitions){
            result.transitions[transition.first] = transition.second;
        }

        result.alphabets.insert(alphabets.begin(), alphabets.end());
        result.alphabets.insert(other.alphabets.begin(), other.alphabets.end());

        result.transitions[result.startState]['~'].insert(startState);
        result.transitions[finalState]['~'].insert(other.startState);
        result.transitions[other.finalState]['~'].insert(result.finalState);
        
        return result;
    } 

    NFA kleene_star(){ // kleene star
        NFA result;

        for(const pair<int,unordered_map<char,set<int>>>& transition : transitions){
            result.transitions[transition.first] = transition.second;
        }

        result.alphabets.insert(alphabets.begin(), alphabets.end());

        result.transitions[result.startState]['~'].insert(startState);
        result.transitions[finalState]['~'].insert(result.finalState);
        result.transitions[finalState]['~'].insert(startState);
        result.transitions[result.startState]['~'].insert(result.finalState);

        return result;
    }

    void  printTransitions(){
        cout<<"startState: "<<startState<<" finalState: "<<finalState<<endl;
        for(const pair<int,unordered_map<char,set<int>>>& transition : transitions){
            for(const pair<char,set<int>>& transition2 : transition.second){
                for(int i : transition2.second){
                    cout << transition.first << " -> " << transition2.first << " -> " << i << endl;
                }
            }
        }

        
    }

    void printAlphabets(){
        cout<<alphabets.size()<<" alphabets: ";
        for(char c : alphabets){
            cout<<c<<" ";
        }
    }

   

    NFA(string s){ // s -> valid is assumed # have to be fixed
        string postfix = infixToPostfix(s);
        stack<NFA> operands;

        for (char c : postfix) {
            if (isalnum(c) || c == '.') {
                operands.push(NFA(c));
            } else if (c == '*') {

                if(operands.empty()) {
                    cout<<"fuck\n";
                    exit(0) ;
                }

                NFA op = operands.top();
                operands.pop();
                operands.push(op.kleene_star());
            } else if (c == '+') {
                if(operands.empty()) {
                    cout<<"fuck\n";
                    exit(0) ;
                }

                NFA op2 = operands.top();
                operands.pop();
                if(operands.empty()) {
                    cout<<"fuck\n";
                    exit(0) ;
                }
                NFA op1 = operands.top();
                operands.pop();
                operands.push(op1 | op2);
            } else if (c == '&') { 
                if(operands.empty()) {
                    cout<<"fuck\n";
                    exit(0) ;
                }
                NFA op2 = operands.top();
                operands.pop();
                if(operands.empty()) {
                    cout<<"fuck\n";
                    exit(0) ;
                }
                NFA op1 = operands.top();
                operands.pop();
                operands.push(op1 & op2);
            }
        }

        NFA result = operands.top();
        *this = result;
    }



    void print_set(set<int> s){
        for(int i : s){
            cout<<i<<" ";
        }
        cout<<endl;
    }


    

    set<int> epsilon_closure(set<int> T){
        stack<int> st;
        for(int i : T) st.push(i);
        set<int> closure = T;

        while(!st.empty()){
            int t = st.top();
            st.pop();
            set<int> temp = transitions[t]['~']; temp.insert(t);
            for(int i: temp){
                if(closure.find(i) == closure.end()){
                    closure.insert(i);
                    st.push(i);
                }
            }
        }
        
        return closure;
    }


    set<int> epsilon_closure(int state){
        set<int> closure = {state};
        closure = epsilon_closure(closure);
        return closure;
    }

    set<int> move(set<int> T, char c){
        set<int> result;

        for(int i: T){
            if(transitions[i].find(c) == transitions[i].end()) continue;
            result.insert(transitions[i][c].begin(), transitions[i][c].end());
        }

        return result;
    }
    
    bool check(string s){
        set<int> S = epsilon_closure(startState);
        for(char c: s){
            if(S.empty()) return false;
            S = move(S, c);
            S = epsilon_closure(S);
        }

        
        cout<<endl;

        return S.find(finalState) != S.end();
    }
};



// int main() {
//     // NFA a('a');
//     // NFA b('b');
//     // NFA c = a | b;
//     // NFA d = c.kleene_star();
//     NFA e("a*");
    
//     // a.printTransitions(); cout<<endl;
//     // b.printTransitions(); cout<<endl;
//     // c.printTransitions(); cout<<endl;
//     // d.printTransitions();
//     e.printTransitions();
//     e.printAlphabets();


//     cout<<endl<<e.check("a")<<endl;
//     return 0;
// }