#include<Windows.h>
#include<cstdlib>
#include <iostream>
#include <cstring>
#include<vector>
using namespace std;
int capacity, num, num0;  // 背包容量和物品数量
int readx = -1;//read的值
int j = 0, i = 1;
int ans0 = 0;
int writetape[400] = { -1 }; int writetapeindex = 0; int cmpx = 399;
int write_anstape[40]; int write_anstapeindex = 0;
int step = 0;
int temp = 0;//clam值
bool ifcla = false;
int weight[10], value[10];  // 存储每个物品的重量和价值
int M[10][100];  // 存储动态规划的最优解矩阵
string state[100] = { "readCapacity"," readNum","readWeight","readValue","writeM","readM","calM","cmp","ansM",
"cmpAnsM","writeAns"," readAns","success "
};
int ans[100];  // 解向量，存储最终选择的物品编号
// 自动机状态定义
enum State {
    readCapacity,  // 读取背包容量
    readNum,       // 读取物品数量
    readWeight,    // 读取物品重量
    readValue,     // 读取物品价值
    writeM,        // 写入最优解矩阵
    readM,         // 读取最优解矩阵
    calM,          // 计算最优解矩阵
    cmp,           // 比较最优解矩阵
    ansM,          // 读取最优解并写入解向量
    cmpAnsM,       // 比较解向量和最优解矩阵
    writeAns,      // 写入解向量
    readAns,
    success        // 成功完成模拟
};
// 自动机状态转移函数
State transition(State currentState, int tape[], int& head, int& tapePos, int& memoryPos, int& memorySize) {
    switch (currentState) {
    case readCapacity:  // 读取背包容量
        capacity = tape[head];
        j = capacity;
        head++;
        return readNum;
    case readNum:       // 读取物品数量
        num = tape[head];
        num0 = num;
        head++;
        tapePos = head + num * 2;
        head = tapePos - 2;// 跳过重量的存储位置
        tapePos -= 2;
        return readWeight;
    case readWeight:    // 读取物品重量
        weight[num - 1] = tape[head];
        head++;
        return readValue;
    case readValue:     // 读取物品价值
        value[num - 1] = tape[head];
        head--;  // 回退到上一个物品的重量位置
        return writeM;
    case writeM:        // 写入最优解矩阵
        if (memoryPos == capacity + 1) {  // 如果已经填满了最优解矩阵
            tapePos -= 2;
            head = tapePos;  // 回到下一个物品的重量位置
            memoryPos = 0;
            num--;

            if (num == 0) {  // 如果已经处理完所有物品进入写解向量阶段
                head += 2;
                return readM;
            }
            else return readWeight;
        }

        if (num == 0) {  // 如果已经处理完所有物品
            return success;
        }
        if (num < num0 && readx == -1)// 将当前物品的价值写入最优解矩阵

        {


            return readM;
        }
        if (num < num0 && readx != -1)//read之后
        {
            if (memoryPos < weight[num - 1])
            {
                M[num][memoryPos] = readx;
                readx = -1;
            }
            else
            {
                if (ifcla)
                {

                    M[num][memoryPos] = temp;
                    ifcla = false;
                    readx = -1;

                }
                else
                {

                    return calM;
                }
            }

        }
        else  if (memoryPos < weight[num - 1])M[num][memoryPos] = 0;
        else  M[num][memoryPos] = value[num - 1];

        memoryPos++; writetapeindex++;

        return writeM;
    case readM:         // 读取最优解矩阵
        if (memoryPos == capacity + 1) {  // 如果已经填满了最优解矩阵
            head = tapePos;  // 回到下一个物品的重量位置
            memoryPos = 0;
            num--;
            return readWeight;
        }
        if (num == 0) {  // 如果已经处理完所有物品
            readx = tape[head];
            head += 2;
            return ansM;
        }
        readx = M[num + 1][memoryPos];
        return writeM;
        //if (num < num0)//read;
        //{

        //}
        //else     M[num][memoryPos] = value[num - 1];
        //head = tapePos + (num - 1) * (capacity + 1) + memoryPos - 1;  // 跳转到下一个物品的最优解矩阵位置
        return writeM;
    case calM:          // 计算最优解矩阵


        temp = M[num + 1][memoryPos - weight[num - 1]] + value[num - 1];  // 计算装入当前物品的价值
        //写入work纸带
        ifcla = true;
        head += capacity + 1;  // 跳转到下一个位置
        return cmp;
    case cmp:           // 比较最优解矩阵

        if (temp > M[num + 1][memoryPos]) {  // 如果装入当前物品更优
            return writeM;  // 直接写入最优解矩阵
        }
        else {  // 否则不装入当前物品
            temp = M[num + 1][memoryPos];
            return writeM;  // 直接读取下一个位置的最优解矩阵
        }
    case ansM:          // 读取最优解并写入解向量
        //ans[memoryPos] = num;  // 将当前物品编号写入解向量
        //memoryPos++;
        return cmpAnsM;
    case cmpAnsM:       // 比较解向量和最优解矩阵
        if (M[i][j] == M[i + 1][j]) {  // 如果不装入当前物品更优

            memoryPos++; i++;
            write_anstapeindex++;
            return readM;  // 写入解向量
        }
        else {  // 否则装入当前物品
            ans0 = 1;
            return writeAns;  // 继续寻找下一个位置的解向量
        }
    case writeAns:      // 写入解向量
        ans[memoryPos] = ans0;  // 将上一个物品编号写入解向量
        ans0 = 0;
        memoryPos++;
        j -= readx;
        i++;
        write_anstapeindex++;
        if (j == 0)
            return success;
        else return readM;
    case readAns:       // 读取解向量
        return success;
    default:
        return success;
    }
}
int main() {
    cout << "请输入背包容量:" << endl;
    int tape[20]; int Capacity, n;
    cin >> Capacity;
    cout << "请输入物品数量:" << endl;
    cin >> n;
    tape[0] = Capacity, tape[1] = n;
    cout << "请输入weight value tape:" << endl;
    for (int k = 2; k < 2 * n + 2; k++)
    {
        cin >> tape[k];
    }
    int head = 0;  // 读写头位置
    int tapePos = 0;  // 纸带位置
    int memoryPos = 0;  // 内存位置
    int memorySize = 10;  // 内存大小
    State currentState = readCapacity;  // 初始状态
    while (currentState != success) {
        cout << "|----------------------------------------|" << endl;
        cout << "|      当前状态为：" << state[currentState] << "          |" << endl;
        cout << "|----------------------------------------|" << endl;
        cout << endl << endl << endl << endl;

        cout << "|----------------------------------------|" << endl;
        if (currentState == readCapacity || currentState == readNum || currentState == readValue || currentState == readWeight)
        {
            cout << "读头位置为输入纸带的：" << tape[head] << "位置：" << head << endl;
        }

        if (currentState == writeM)
        {
            cout << "写头位置为工作纸带的：" << "位置：" << writetapeindex << endl;
        }

        if (currentState == readM)
        {
            cout << "读头位置为工作纸带的：" << "位置：" << (writetapeindex)-6 << endl;
        }

        if (currentState == calM)
        {
            cout << "读头位置为工作纸带的：" << "位置：" << (3 - num) * 6 + memoryPos - weight[num - 1] << endl;
        }


        if (currentState == cmp)
        {
            cout << "写头位置为工作纸带的：" << "位置：" << cmpx << endl;
        }

        if (currentState == ansM)
        {
            cout << "读头位置为工作纸带的：" << "位置：" << "(" << i << "," << j << ")" << endl;
        }

        if (currentState == cmpAnsM)
        {
            cout << "读头位置为工作纸带的：" << "位置：" << "(" << i + 1 << "," << j << ")" << endl;
        }

        if (currentState == writeAns)
        {
            cout << "读头位置为输出纸带的：" << "位置：" << write_anstapeindex << endl;
        }
        cout << "|----------------------------------------|" << endl;
        cout << endl << endl << endl;
        cout << "二维表：" << endl;
        for (int a = 1; a <= 5; a++)
        {
            for (int b = 0; b < capacity + 1; b++)

            {
                cout << M[a][b] << " ";
            }
            cout << endl;
        }
        cout << endl << "工作纸带：";
        for (int a = num0; a >= num; a--)
        {
            for (int b = 0; b < capacity + 1; b++)

            {

                cout << M[a][b] << " ";
            }

        }
        if (temp != 0)
        {
            cout << temp;

        }
        cout << endl << "输出纸带：";
        for (int a = 0; a < num0; a++)
        {
            cout << ans[a] << " ";
        }

        cout << endl << "step：" << step++ << "        " << "grids" << writetapeindex + 400 - cmpx << endl;
        currentState = transition(currentState, tape, head, tapePos, memoryPos, memorySize);

        system("pause");
        system("cls");

        if (currentState == success)
        {
            cout << "|----------------------------------------|" << endl;
            cout << "|当前状态为：" << state[currentState] << "--------------------------|" << endl;
            cout << "|-----------------------------------------|" << endl;
            cout << endl << endl << endl << endl;
        }
    }
    cout << "解向量为：";
    for (int i = 0; i < num0; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}

