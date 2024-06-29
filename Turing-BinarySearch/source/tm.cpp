#include "../include/tm.h"

TuringMachine :: TuringMachine(std::vector<int> input){
    this->input_tape = std::move(input);
    input_ptr = 0;
    work_ptr = 0;
    shift_tape = "input tape";
    read_data = "";
    write_data = "";
    steps = 0;
    shifts = 0;
    display();
    initLow();
}

void TuringMachine::display(){
    system("clear");
    std::string direction = (dirc == 0) ? "L" : "R";
    std::cout << "steps: " << steps++ << std::endl;
    std::cout << "grids: " << work_tape.size() << std::endl;

    std::cout << "shifts: " ;
    if(dirc == 0 || dirc == 1) std::cout<< direction << " "; 
    std::cout<< shifts << std::endl;

    std::cout << "shift tape: " << shift_tape << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "cur state: " << cur_state << std::endl;
    std::cout << "next state: " << next_state << std::endl;
    std::cout << "read_data: " << read_data << std::endl;
    std::cout << "write_data: " << write_data << std::endl;
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
        std::cout << "[]" << std::endl;
        return;
    }
    if(tape_ptr < 0) tape_ptr = 0; 
    if(tape_ptr < n){
        for(int i = 0; i < tape_ptr; ++i){
            std::cout << tape[i] << " ";
        }
        std::cout <<  "[" << tape[tape_ptr] << "]" << " ";
        for(int i = tape_ptr + 1; i < n; ++i){
            std::cout << tape[i] << " ";
        }
    }
    else if(tape_ptr >= n){
        for(int i = 0; i < n; ++i){
            std::cout << tape[i] << " ";
        }
        std::cout << "[]";
    }
    std::cout << std::endl;
}

void TuringMachine::initLow(){
    this->cur_state = "initLow";
    this->next_state = "writeLow";
    shift_tape = "input tape";
    shifts = R;
    dirc =  1;
    read_data = std::to_string(input_tape[input_ptr]);
    write_data = read_data;
    display();
    ++input_ptr;    //读取low，然后右移一格
    writeLow();
    return;
}

void TuringMachine::writeLow(){
    this->cur_state = "writeLow";
    this->next_state = "initHigh";
    shift_tape = "work tape";
    shifts = 1;
    dirc = R;
    read_data = "";
    write_data = std::to_string(input_tape[0]);
    display();
    ++work_ptr; //右移一格
    work_tape.push_back(input_tape[0]);     //写入low
    initHigh();
    return;
}

void TuringMachine::initHigh(){
    this->cur_state = "initHigh";
    this->next_state = "writeHigh";
    shifts = 1;
    dirc = R;
    shift_tape = "input tape";
    read_data = std::to_string(input_tape[input_ptr]);
    write_data = read_data;
    display();
    ++input_ptr;    //读取high，然后右移一格
    writeHigh();
    return;
}

void TuringMachine::writeHigh(){
    this->cur_state = "writeHigh";
    this->next_state = "compareLow";
    shifts = 1;
    dirc = L;
    shift_tape = "work tape";
    read_data = "";
    write_data = std::to_string(input_tape[1]);
    display();
    --work_ptr; //左移一格
    work_tape.push_back(input_tape[1]);     //写入high
    compareLow();
    return;
}

void TuringMachine::compareLow(){
    this->cur_state = "compareLow";
    read_data = std::to_string(work_tape[work_ptr]);
    write_data = read_data;
    if(work_tape[0] > work_tape[1]){    //low > high
        next_state = "stop";
        shifts = 0;
        dirc = 2;
        shift_tape = "output tape";
        display();
        stop();
    }
    else{
        next_state = "callMid";
        shifts = 2;
        shift_tape = "work tape";
        dirc = R;
        display();
        work_ptr += 2;  //右移两格
        callMid();
    }
    return;
}

void TuringMachine::compareHigh(){
    this->cur_state = "compareHigh";
    read_data = std::to_string(work_tape[work_ptr]);
    write_data = read_data;
    if(work_tape[0] <= work_tape[1]){
        this->next_state = "callMid";
        shifts = 0;
        dirc = 2;
        display();
        callMid();
    }
    else{
        this->next_state ="stop";
        shifts = 0;
        dirc = 2;
        display();
        stop();
    }
    return;
}

void TuringMachine::stop(){
    this->cur_state = "stop";
    this->next_state = "";
    read_data = "";
    write_data = std::to_string(-1);
    display();
    output_tape.push_back(-1);
    display();
    return;
}

void TuringMachine::callMid(){
    this->cur_state = "callMid";
    this->next_state = "readMid";
    int mid = (work_tape[0] + work_tape[1]) / 2;
    if(work_tape.size() < 3) read_data = "";
    else read_data = std::to_string(work_tape[2]);
    write_data = std::to_string(mid);
    shifts = mid + 3 - input_ptr;
    shift_tape = "input tape";
    dirc = R;
    display();
    if(work_tape.size() == 3) work_tape[2] = mid;
    else work_tape.push_back(mid);
    input_ptr = mid + 3;
    readMid();
}

void TuringMachine::readMid(){
    this->cur_state = "readMid";
    this->next_state = "compareMid";
    shifts = work_tape[2] + 1;
    shift_tape = "input tape";
    dirc = L;
    read_data = std::to_string(input_tape[input_ptr]);  //读取input_tape[mid]
    write_data = read_data;
    display();
    input_ptr = work_tape[2] + 3;  //移至input_tape[mid]
    input_ptr = 2;
    compareMid();
    return;
}

void TuringMachine::compareMid(){
    this->cur_state = "compareMid";
    read_data = std::to_string(work_tape[2]);
    write_data = std::to_string(work_tape[2]);
    if(input_tape[work_tape[2] + 3] == input_tape[input_ptr]){
        this->next_state = "success";
        shifts = 0;
        dirc = 2;
        shift_tape = "output tape";
        display();
        success();
    }
    else if(input_tape[work_tape[2] + 3] < input_tape[input_ptr]){
        this->next_state = "updateLow";
        shifts = work_ptr;
        dirc = L;
        shift_tape = "work tape";
        display();
        work_ptr = 0;
        updateLow();
    }
    else if(input_tape[work_tape[2] + 3] > input_tape[input_ptr]){
        this->next_state = "updateHigh";
        shifts = work_ptr - 1;
        dirc = L;
        shift_tape = "work tape";
        display();
        work_ptr = 1;
        updateHigh();
    }
    return;
}

void TuringMachine::success(){
    this->cur_state = "success";
    this->next_state = "";
    shifts = 0;
    dirc = 2;
    read_data = "";
    write_data = std::to_string(work_tape[2]);
    display();
    output_tape.push_back(work_tape[2]);
    display();
    return;
}

void TuringMachine::updateLow(){
    this->cur_state = "updateLow";
    this->next_state = "compareHigh"; 
    shifts = R;
    dirc = 1;
    read_data = std::to_string(work_tape[0]);
    write_data = std::to_string(work_tape[2] + 1);
    display();
    work_tape[work_ptr++] = work_tape[2] + 1; //更新low,并右移一格
    compareHigh();
    return;
}

void TuringMachine::updateHigh(){
    this->cur_state = "updateHigh";
    this->next_state = "compareLow"; 
    shifts = 1;
    dirc = L;
    read_data = std::to_string(work_tape[1]);
    write_data = std::to_string(work_tape[2] - 1);
    display();
    work_tape[work_ptr--] = work_tape[2] - 1; //更新high,并左移一格
    compareLow();
    return;
}