#include<iostream>
using namespace std;


int f(int a, float b = 0.2){
    return a * b;
    int* a = &a;
    cout<<(a*)<<endl;
}
int main(){
    cout<<f(1,2);
}