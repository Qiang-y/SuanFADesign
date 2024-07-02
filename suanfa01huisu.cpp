
///*
#include <cstdlib> 
#include <iostream>
#include <vector>
#include<stack>
using namespace std;
struct StackFrame {
    int W;
    int n;
};
stack<StackFrame>stk;
void printStack(stack<StackFrame> stk) {
    cout << "当前栈内容：" << endl;
    while (!stk.empty()) {
        StackFrame frame = stk.top();
        cout << "W: " << frame.W << ", n: " << frame.n << endl;
        stk.pop();
    }
}
// 递归计算0/1背包问题的最优值
int knapsack_recursive(int W, const vector<int>& w, const vector<int>& v, int n, int& steps, int& maxDepth, int currentDepth,stack<StackFrame>stk) {
    steps++;
    maxDepth = max(maxDepth, currentDepth);
    StackFrame frame = { W,n };
    stk.push(frame);
   
    cout << "steps: " << steps << endl << "maxDepth: " << maxDepth << endl;
    printStack(stk);
    system("pause");
    system("cls");
    maxDepth = max(maxDepth, currentDepth);
    cout << "调用(W=" << W << ", n=" << n << "), maxDepth: " << currentDepth << endl;
    if (n == 0 || W == 0) {
        cout << "不能再装了" << endl;
       
        return 0;
    }
    if (w[n - 1] > W) {
        int result = knapsack_recursive(W, w, v, n - 1, steps, maxDepth, currentDepth + 1,stk);
        return result;
    }
    else {
        int include = v[n - 1] + knapsack_recursive(W - w[n - 1], w, v, n - 1, steps, maxDepth, currentDepth + 1,stk);
        int exclude = knapsack_recursive(W, w, v, n - 1, steps, maxDepth, currentDepth + 1,stk);
        int result = max(include, exclude);
        return result;
    }
}

int main() {
    int W = 50; // 背包的最大承载重量
    vector<int> w = { 10, 20, 30 }; // 物品的重量
    vector<int> v = { 60, 100, 120 }; // 物品的价值
    int n = w.size(); // 物品的数量

    int steps = 0;
    int maxDepth = 0;
    int result = knapsack_recursive(W, w, v, n, steps, maxDepth, 1,stk);
    system("pause");
    system("cls");
    cout<<"////////////"<<endl;
    cout << "result:" << result << endl;
    cout << "steps: " << steps << endl;
    cout << "maxDepth: " << maxDepth << endl;

    return 0;
}
