#include <bits/stdc++.h>
using namespace std;
class FSM_NODE{
    // curr state + curr key = next state
    unordered_map<char,set<FSM_NODE*>> next_state;
    public:

    void set_next_state(char c, FSM_NODE* node){
        next_state[c].insert(node);
    }
};

class FSM{
    FSM_NODE* start = new FSM_NODE();
    FSM_NODE* end = new FSM_NODE();

    public:

    FSM_NODE* get_start(){
        return start;
    }
    FSM_NODE* get_end(){
        return end;
    }

    FSM operator+ ( FSM a){
        FSM result;
        
        result.start->set_next_state('~', this->get_start());
        result.start->set_next_state('~', a.get_start());

        this->end->set_next_state('~',result.get_end());
        a.get_end()->set_next_state('~',result.get_end());
        return result;
    }

    FSM operator*(FSM a){
        FSM result;
        result.start->set_next_state('~',this->get_start());
        result.end->set_next_state('~',a.get_start());
        a.end->set_next_state('~',result.get_end());

        return result;
    }
};