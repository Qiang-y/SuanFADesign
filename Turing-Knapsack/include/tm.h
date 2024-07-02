#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <algorithm>
#include <queue>
#define L 0
#define R 1

class TuringMachine{
public:
    //TuringMachine() = default;
    TuringMachine(std::vector<int> input);
    void display();    //打印纸带
    void display_tape(const std::vector<int> &tape, int tape_ptr);
    void initNums();
    void writeNums();
    void initSpace();
    void writeSpace();
    void readWeight();
    void readValue();
    void preprocess();
    void initHeap();
    void AddliveNode();
    void deleteNode();
    void storeResult();
private:
    std::string cur_state, next_state;  //图灵机当前状态和下一状态
    std::string shift_tape; //当前移动的纸带
    std::vector<int> input_tape;    //图灵机读取的纸带
    std::vector<int> work_tape;         //图灵机工作的纸带
    std::vector<int> output_tape;       //图灵机输出的纸带
    int input_ptr;  //input_tape的读写头
    int work_ptr; //work_tape的读写头
    std::string read_data;
    std::string write_data;
    int steps;    //图灵机状态转换的次数
    int shifts;     //读写头左移/右移的方格数
    int dirc;   //纸带移动的方向(0 代表 L， 1 代表 R)
    int object_id;  //物品的编号
};

class Object
{
public:
    int id;
    int weight;
    int price;
    float d;
};

class MaxHeapQNode
{
public:
    MaxHeapQNode *parent;
    int lchild;
    int upprofit;
    int profit;
    int weight;
    int lev;
};

struct cmp
{
    bool operator()(MaxHeapQNode *&a, MaxHeapQNode *&b) const
    {
        return a->upprofit < b->upprofit;
    }
};