#include <iostream>

[[nodiscard]] int Minimum(int, int);

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