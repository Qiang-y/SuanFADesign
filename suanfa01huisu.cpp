
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
    int W; // 背包的最大承载重量
    cout << "输入capacity：" << endl;
    cin >> W;
    int n;// 物品的数量
    cout << "输入n：" << endl;
    cin >> n;


    vector<int> w;// 物品的重量
	vector<int> v;// 物品的价值
	cout << "输入weight：" << endl;
	int a=0;
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		w.push_back(a);
	}
    cout << "输入profit：" << endl;
    int b = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> b;
        v.push_back(b);
    }
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
