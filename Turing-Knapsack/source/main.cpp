#include "../include/tm.h"

int main()
{
    std::vector<int> input;
    int a = 0, b = 0;
    std::cout << "Num and Capcity: " << std::endl;
    std::cin >> a >> b;
    input.push_back(a);
    input.push_back(b);
    system("clear");
    std::cout << "Weight and Value: " << std::endl;
    for(int i = 0; i < input[0]; ++i){
        std::cin >> a >> b;
        input.push_back(a);
        input.push_back(b);
    }
    system("clear");
    TuringMachine tm{input};

    return 0;

     
}






