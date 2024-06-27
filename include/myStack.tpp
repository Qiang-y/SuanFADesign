#include"myStack.h"

template <typename TYPE>
myStack<TYPE>::myStack(){
    typeLen = sizeof(TYPE);
    LEN = 64;
    stack.reset(new TYPE[std::move(LEN)]);
    topPoint = -1;
}

template <typename TYPE>
myStack<TYPE>::myStack(std::initializer_list<TYPE>&& list){
    typeLen = sizeof(TYPE);
    int tempsize = list.size() / 64;
    tempsize += 1;
    LEN = 64 * tempsize;
    stack.reset(new TYPE[std::move(LEN)]);
    topPoint = -1;
    for(auto l : list){
        stack[++topPoint] = l;
    }
}

template <typename TYPE>
TYPE myStack<TYPE>::top(){
    if(topPoint == -1){
        return TYPE(-1);
    }
    return stack[topPoint];
}

template <typename TYPE>
void myStack<TYPE>::push(TYPE t){
    if(topPoint == LEN - 1){
        int nextLEN = LEN * 2;
        std::unique_ptr<TYPE[]> temp(move(stack));
        stack.reset(new TYPE[nextLEN]);
        for(int i = 0; i < LEN; ++i)
            stack[i] = temp[i];
        LEN = nextLEN;
    }
    stack[++topPoint] = t;
}

template <typename TYPE>
void myStack<TYPE>::pop(){
    if(topPoint == -1){
        return;
    }
    topPoint--;
}