#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <assert.h>
using namespace std;

typedef struct ParseTreeNode{
    char c;
    bool isLeafNode = true;
    int id = 0;
    int left = -1, right = -1;
}ParseTreeNode;

class ParseTree{
    vector<ParseTreeNode> NodePool;
    int ID = 0;

    void createLeafNode(char c){
        ParseTreeNode p;
        p.c = c;
        p.id = ID++;
        NodePool.push_back(p);
    }
};

int main(){
    ParseTree* p = new ParseTree();
    ParseTree* p2 = new ParseTree();
    
    cout<<(p != p2)<<endl;
}