// Naming arguments in function prototypes
// Identical to example_02 other than the argument names in the function prototype.

#include <iostream>

[[nodiscard]] int Minimum(int arg1, int arg2);

int main()
{
    int x = 5, y = 89;
    // function call with actual parameters
    std::cout << Minimum(x, y) << std::endl;
    return 0;
}

[[nodiscard]] int Minimum(int a, int b) // function definition with formal parameters
{
    return (a < b) ? a : b;
}