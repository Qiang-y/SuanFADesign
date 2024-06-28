#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#define L 0
#define R 1

class TuringMachine{
public:
    //TuringMachine() = default;
    TuringMachine(std::vector<int> input);
    void display();    //打印纸带
    void display_tape(const std::vector<int> &tape, int tape_ptr);
    void initLow();
    void writeLow();
    void initHigh();
    void writeHigh();
    void compareLow();
    void compareHigh();
    void stop();
    void callMid();
    void readMid();
    void compareMid();
    void success();
    void updateLow();
    void updateHigh();
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
};
