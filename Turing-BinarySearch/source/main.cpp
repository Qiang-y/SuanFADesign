#include "../include/tm.h"


int main()
{
    std::vector<int> input;
    std::cout << "lower bound and upper bound:";
    int a = 0, b = 0;
    std::cin >> a >> b;
    input.push_back(a);
    input.push_back(b);
    system("clear");
    std::cout << "key: ";
    std::cin >> a;
    system("clear");
    input.push_back(a);
    std::cout << "Array: ";
    for(int i = 0; i < input[1] + 1; ++i){
        std::cin >> a;
        input.push_back(a);
    }
    system("clear");
    TuringMachine tm{input};

    return 0;

    
}






