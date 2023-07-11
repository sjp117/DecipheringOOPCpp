// Adding default values to function prototype

#include <iostream>

[[nodiscard]] int Minimum(int arg1, int arg2 = 100000);

int main()
{
    int x = 5, y = 89;
    // function call with actual parameters
    std::cout << Minimum(x) << std::endl;    // function call with only one argument
    std::cout << Minimum(x, y) << std::endl; // function call with no default value used
    return 0;
}

[[nodiscard]] int Minimum(int a, int b) // function definition with formal parameters
{
    return (a < b) ? a : b;
}