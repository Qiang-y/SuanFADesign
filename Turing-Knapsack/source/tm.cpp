#include "../include/tm.h"

int n;  //物品个数
int c;  //背包容量
int cw; //已经使用的背包容量
int cp; //已经获得的价值
int bestp;  //当前获得的最大价值
Object obj[100];
int bestx[100];
std::priority_queue<MaxHeapQNode *, std::vector<MaxHeapQNode *>, cmp > q; // 大顶堆
MaxHeapQNode *E;
int i;
int up; //



bool compare(const Object &a, const Object &b)
{
    return a.d >= b.d;
}

int Bound(int i)
{
    int tmp_cleft = c - cw;
    int tmp_cp = cp;
    while(tmp_cleft >= obj[i].weight && i <= n)
    {
        tmp_cleft -= obj[i].weight;
        tmp_cp += obj[i].price;
        i++;
    }
    if(i <= n)
    {
        tmp_cp += tmp_cleft * obj[i].d;
    }
    return tmp_cp;
}

void AddAliveNode(std::priority_queue<MaxHeapQNode *, std::vector<MaxHeapQNode *>, cmp> &q, MaxHeapQNode *E, int up, int wt, int curp, int i, int ch)
{
    MaxHeapQNode *p = new MaxHeapQNode;
    p->parent = E;
    p->lchild = ch;
    p->weight = wt;
    p->upprofit = up;
    p->profit = curp;
    p->lev = i + 1;
    q.push(p);
//    cout << "加入点的信息为 " << endl;
//    cout << "p->lev = " << p->lev << " p->upprofit = " << p->upprofit << " p->weight =  " << p->weight << " p->profit =  " << p->profit << endl;
}


void convert(std::priority_queue<MaxHeapQNode *, std::vector<MaxHeapQNode *>, cmp> q, std::vector<int> & tape){
    while(!q.empty()){
        tape.push_back(q.top()->upprofit);
        q.pop();
    }
    return;
}

TuringMachine :: TuringMachine(std::vector<int> input){
    this->input_tape = std::move(input);
    input_ptr = 0;
    work_ptr = 0;
    shift_tape = "input tape";
    read_data = "";
    write_data = "";
    steps = 0;
    shifts = 0;
    object_id = 1;
    display();
    initNums();
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

void TuringMachine::initNums(){ //
    cur_state = "initNums";
    next_state = "writeNums";
    read_data = std::to_string(input_tape[input_ptr]);
    write_data = read_data;
    shifts = 1;
    shift_tape = "input_tape";
    dirc  = R;
    n = input_tape[0];
    display();
    ++input_ptr;
    writeNums();
    return;
}

void TuringMachine::writeNums(){
    cur_state = "writeNums";
    next_state = "initSpace";
    write_data = read_data;
    read_data = "";
    shifts = 1;
    shift_tape = "work_tape";
    dirc = R;
    display();
    ++work_ptr;
    work_tape.push_back(input_tape[0]);
    initSpace();
    return;
}

void TuringMachine::initSpace(){
    cur_state = "initSpace";
    next_state = "writeSpace";
    read_data = std::to_string(input_tape[input_ptr]);
    write_data = read_data;
    shifts = 1;
    shift_tape = "input_tape";
    dirc = R;
    c = input_tape[1];
    display();
    ++input_ptr;
    writeSpace();
    return;
}

void TuringMachine::writeSpace(){
    cur_state = "writeSpace";
    next_state = "readWeight";
    write_data = read_data;
    read_data = "";
    shifts = 1;
    shift_tape = "work_tape";
    dirc = R;
    display();
    ++work_ptr;
    work_tape.push_back(input_tape[1]);
    readWeight();
    return;
}

void TuringMachine::readWeight(){
    cur_state = "readWeight";
    next_state = "readValue";
    read_data = std::to_string(input_tape[input_ptr]);
    write_data = read_data;
    shifts = 1;
    shift_tape = "input_tape";
    dirc = R;
    obj[object_id].id = object_id;
    obj[object_id].weight = input_tape[input_ptr];
    display();
    ++input_ptr;
    readValue();
    return ;
}

void TuringMachine::readValue(){
    cur_state = "readValue";
    read_data = std::to_string(input_tape[input_ptr]);
    write_data = read_data;
    obj[object_id].price = input_tape[input_ptr];
    obj[object_id].d = obj[object_id].price/obj[object_id].weight;
    if(input_ptr == input_tape.size() - 1){
        next_state = "preprocess";
        shifts = 0;
        dirc = 2;
        display();
        preprocess();
    }
    else{
        next_state = "readWeight";
        shifts = 1;
        shift_tape = "input_tape";
        dirc = R;
        display();
        ++input_ptr;
        ++object_id;
        readWeight();
    }
    return ;
}

void TuringMachine::preprocess(){
    cur_state = "preprocess";
    next_state = "initHeap";
    read_data = "";
    write_data = "";
    shifts = 0;
    std::sort(obj + 1, obj + n + 1, compare);
    display();
    initHeap();
}

void TuringMachine::initHeap(){
    cur_state = "initHeap";
    next_state = "AddAliveNode";
    display();
    cw = 0;
    cp = 0;
    bestp = 0;
    i = 1;
    E = NULL;
    up = Bound(1);
    work_ptr = 0;
    AddliveNode();
    return;
}

void TuringMachine::AddliveNode(){
    cur_state = "AddliveNode";
    if(i != n+1){
        next_state = "deleteNode";
        display();
        std::vector<int>().swap(work_tape); //清空work_tape中的内容
        int wt = cw + obj[i].weight;
        if(wt <= c){
            if(bestp <= cp + obj[i].price) bestp = cp + obj[i].price;
             AddAliveNode(q, E, up, cw + obj[i].weight, cp + obj[i].price, i, 1);
        }
         up = Bound(i + 1); //注意这里 up != up - obj[i].price而且 up >= up - obj[i].price
        if(up >= bestp) //注意这里必须是大于等于
        {
            AddAliveNode(q, E, up, cw, cp, i, 0);
        }
        convert(q, work_tape);
       deleteNode();
    }
    else{
        next_state = "storeResult";
        for(int j = n; j > 0; --j){
            bestx[obj[E->lev - 1].id] = E->lchild;
            E = E->parent;
        }
        display();
        storeResult();
    }
    return;
}

void TuringMachine::deleteNode(){
    cur_state = "deleteNode";
    next_state = "AddliveNode";
    display();
    std::vector<int>().swap(work_tape); //清空work_tape中的内容
    E = q.top();
    q.pop();
    convert(q, work_tape);
    cw = E->weight;
    cp = E->profit;
    up = E->upprofit;
    i = E->lev;
    AddliveNode();
}

void TuringMachine::storeResult(){
    cur_state = "storeResult";
    next_state = "";
    output_tape.push_back(bestp);
    for(int i = 1; i <= n; ++i) output_tape.push_back(bestx[i]);
    display();
    return;
}
