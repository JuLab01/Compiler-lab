
#include<map>
#include<set>
#include<vector>
#include<iostream>
#include<string>
// #include "./infix_to_postfix.cpp"
#include "./NFA.cpp"
using namespace std;

void debug(set<int>& s){
    for(int i : s){
        cout<<i<<" ";
    }
    cout<<endl;
}


class DFA{
    int ID = 0;
    public:
    unordered_map<int,unordered_map<char,int>> transitions;
    int startState = 0;
    set<int> finalState;

    DFA(NFA nfa){
        map<set<int>,int> Dstates;
        stack<set<int>> states;
        states.push(nfa.epsilon_closure(nfa.startState));
        Dstates[states.top()] = ID++;


        while(!states.empty()){
            set<int> state = states.top();
            states.pop();

            // debug(state);

            if(state.find(nfa.finalState) != state.end()){
                finalState.insert(Dstates[state]);
            }

            for(char c : nfa.alphabets){
                set<int> next = nfa.epsilon_closure(nfa.move(state, c));
                if(next.size() == 0) continue;
                if(Dstates.find(next) == Dstates.end()){
                    Dstates[next] = ID++;
                    states.push(next);
                }

                
                transitions[Dstates[state]][c] = Dstates[next];
            }
        }
    }

    DFA (string regex){
        NFA nfa(regex);
        DFA dfa(nfa);
        *this = dfa;
    }

    void printTransitions(){

        cout<<"startState: "<<startState<<" finalState: ";
        for(int i : finalState) cout<<i<<" ";
        cout<<endl;

        for(const pair<int,unordered_map<char,int>>& transition : transitions){
            for(const pair<char,int>& transition2 : transition.second){
                cout<<transition.first<<" -> "<<transition2.first<<" -> "<<transition2.second<<endl;
            }
        }
    }

    bool check(string s){
        int S = startState;
        for(char c : s){
            s = transitions[S][c];
        }

        return finalState.find(S) != finalState.end();
    }



};



int main(){
    
    NFA a("(0+1+2+3+4+5+6+7+8+9)*&.&(0+1+2+3+4+5+6+7+8+9)*");
    // NFA b("(0|1|2|3|4|5|6|7|8|9)*&.&(0|1|2|3|4|5|6|7|8|9)*");
    // DFA a("(0|1|2|3|4|5|6|7|8|9)*&.&(0|1|2|3|4|5|6|7|8|9)*");
    DFA b(a);


    // NFA x("(0+1)*");

    // x.printTransitions();
    
    
    cout<<a.check("987.908")<<endl;

    b.printTransitions();
}