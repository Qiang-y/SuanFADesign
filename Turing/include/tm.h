#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

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
    std::vector<int> input_tape;    //图灵机读取的纸带
    std::vector<int> work_tape;         //图灵机工作的纸带
    std::vector<int> output_tape;       //图灵机输出的纸带
    int input_ptr;  //input_tape的读写头
    int work_ptr; //work_tape的读写头
    int read_data;
    int steps;    //图灵机状态转换的次数
};
