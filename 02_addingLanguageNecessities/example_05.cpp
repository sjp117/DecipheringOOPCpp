// Prototyping with different default values in different scopes

#include <iostream>

[[nodiscard]] int Minimum(int, int);

void Function1(int x)
{
    // local prototype with default value
    [[nodiscard]] int Minimum(int arg1, int arg2 = 500);
    std::cout << Minimum(x) << std::endl;
}

void Function2(int x)
{
    // local prototype with default value
    [[nodiscard]] int Minimum(int arg1, int arg2 = 90);
    std::cout << Minimum(x) << std::endl;
}

[[nodiscard]] int Minimum(int a, int b) // function definition with formal parameters
{
    return (a < b) ? a : b;
}

int main()
{
    Function1(30);
    Function2(450);
    return 0;
}
