// Eliminating excessive overloading with standard type conversion

#include <iostream>

// function prototype
int Maximum(double, double);

int main()
{
    int result = 0;
    int m = 6, n = 10;
    float x = 5.7, y = 9.98;

    result = Maximum(x, y);
    std::cout << "Result is: " << result << std::endl;
    std::cout << "The maximum is: " << Maximum(m, n) << std::endl;

    return 0;
}

// function definition
int Maximum(double a, double b)
{
    return (a > b) ? a : b;
}