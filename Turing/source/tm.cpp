#include "../include/tm.h"

TuringMachine :: TuringMachine(std::vector<int> input){
    this->input_tape = std::move(input);
    input_ptr = 0;
    work_ptr = 0;
    read_data = -1;
    steps = 1;
    display();
    initLow();
}

void TuringMachine::display(){
    system("clear");
    std::cout << "steps: " << steps++ << std::endl;
    std::cout << "grids: " << work_tape.size() << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "cur state: " << cur_state << std::endl;
    std::cout << "next state: " << next_state << std::endl;
    std::cout << "read_data: " << read_data << std::endl;
    std::cout << "input tape: " << std::endl;
    display_tape(input_tape, input_ptr); 
    std::cout << "work tape: " << std::endl;
    display_tape(work_tape, work_ptr);
    std::cout << "output tape: " << std::endl;
    display_tape(output_tape, 0);
    std::cout << std::endl <<std::endl;
    usleep(300000);
    std::cin.get();
}

void TuringMachine::display_tape(const std::vector<int> &tape, int tape_ptr){
    int n = tape.size();
    if(n == 0) {
        std::cout << std::endl;
        return;
    }
    if(tape_ptr < 0) tape_ptr = 0;
    else if (tape_ptr >= n && n != 0) tape_ptr = n-1; 
    for(int i = 0; i < tape_ptr; ++i){
        std::cout << tape[i] << " ";
    }
    std::cout <<  "[" << tape[tape_ptr] << "]" << " ";
    for(int i = tape_ptr + 1; i < n; ++i){
        std::cout << tape[i] << " ";
    }
    std::cout << std::endl;
}

void TuringMachine::initLow(){
    this->cur_state = "initLow";
    this->next_state = "writeLow";
    read_data = input_tape[input_ptr++];    //读取low，然后右移一格
    display();
    writeLow();
    return;
}

void TuringMachine::writeLow(){
    this->cur_state = "writeLow";
    this->next_state = "initHigh";
    ++work_ptr; //右移一格
    work_tape.push_back(read_data);     //写入low
    display();
    initHigh();
    return;
}

void TuringMachine::initHigh(){
    this->cur_state = "initHigh";
    this->next_state = "writeHigh";
    read_data = input_tape[input_ptr++];    //读取high，然后右移一格
    display();
    writeHigh();
    return;
}

void TuringMachine::writeHigh(){
    this->cur_state = "writeHigh";
    this->next_state = "compareLow";
    --work_ptr; //左移一格
    work_tape.push_back(read_data);     //写入high
    display();
    compareLow();
    return;
}

void TuringMachine::compareLow(){
    this->cur_state = "compareLow";
    if(work_tape[0] > work_tape[1]){    //low > high
        next_state = "stop";
        output_tape.push_back(-1);
        display();
        stop();
    }
    else{
        next_state = "callMid";
        work_ptr += 2;  //右移两格
        display();
        callMid();
    }
    return;
}

void TuringMachine::compareHigh(){
    this->cur_state = "compareHigh";
    if(work_tape[0] <= work_tape[1]){
        this->next_state = "callMid";
        display();
        callMid();
    }
    else{
        this->next_state ="stop";
        display();
        stop();
    }
    return;
}

void TuringMachine::stop(){
    this->cur_state = "stop";
    this->next_state = "";
    display();
    return;
}

void TuringMachine::callMid(){
    this->cur_state = "callMid";
    this->next_state = "readMid";
    int mid = (work_tape[0] + work_tape[1]) / 2;
    if(work_tape.size() == 3) work_tape[2] = mid;
    else work_tape.push_back(mid);
    display();
    readMid();
}

void TuringMachine::readMid(){
    this->cur_state = "readMid";
    this->next_state = "compareMid";
    input_ptr = work_tape[2] + 3;  //移至input_tape[mid]
    read_data = input_tape[input_ptr];
    display();
    compareMid();
    return;
}

void TuringMachine::compareMid(){
    this->cur_state = "compareMid";
    input_ptr = 2;  //左移至位置3 
    if(input_tape[work_tape[2] + 3] == input_tape[input_ptr]){
        this->next_state = "success";
        display();
        success();
    }
    else if(input_tape[work_tape[2] + 3] < input_tape[input_ptr]){
        this->next_state = "updateLow";
        display();
        work_ptr = 0;
        updateLow();
    }
    else if(input_tape[work_tape[2] + 3] > input_tape[input_ptr]){
        this->next_state = "updateHigh";
        work_ptr = 1;
        display();
        updateHigh();
    }
    return;
}

void TuringMachine::success(){
    this->cur_state = "success";
    output_tape.push_back(work_tape[2]);
    display();
    return;
}

void TuringMachine::updateLow(){
    this->cur_state = "updateLow";
    this->next_state = "compareHigh"; 
    work_tape[work_ptr++] = work_tape[2] + 1; //更新low,并右移一格
    display();
    compareHigh();
    return;
}

void TuringMachine::updateHigh(){
    this->cur_state = "updateHigh";
    this->next_state = "compareLow"; 
    work_tape[work_ptr--] = work_tape[2] - 1; //更新high,并左移一格
    display();
    compareLow();
    return;
}