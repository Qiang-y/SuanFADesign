#include<iostream>
#include<memory>
#include<vector>
#include"../include/myStack.h"
using namespace std;


int main(){
    myStack<int> stack = {4,5,6};
    // stack.push(4);
    // stack.push(5);
    // stack.push(6);
    cout << stack.top() << endl;
    stack.pop();
    cout << stack.top() << endl;
    return 0;
}