// Using references to constant objects

#include <iostream>

int main()
{
    int x = 5;
    const int &refInt = x;
    std::cout << x << " " << refInt << std::endl;

    // refInt = 6; // illegal -- refInt is const

    x = 7; // we can indirectly change refInt
    std::cout << x << " " << refInt << std::endl;
    return 0;
}