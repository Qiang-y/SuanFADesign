#pragma once
#include<iostream>
#include<memory>

template <typename TYPE>
class myStack{
private:
    int typeLen;
    int LEN;
    int topPoint;
    // TYPE* stack;
    std::unique_ptr<TYPE[]> stack; 
public:
    myStack();
    myStack(std::initializer_list<TYPE>&& list);
    TYPE top();
    void push(TYPE t);
    void pop();
};

#include"myStack.tpp"