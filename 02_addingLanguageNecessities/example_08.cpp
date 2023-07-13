// Ambiguities arising from function overloading and type conversion

#include <iostream>

// overloaded function prototypes
int Maximum(int, int);
float Maximum(float, float);

int main()
{
    char a = 'A', b = 'B';
    float x = 5.7, y = 9.89;
    int m = 6, n = 10;

    std::cout << "The max is: " << Maximum(a, b) << std::endl;
    std::cout << "The max is: " << Maximum(x, y) << std::endl;
    std::cout << "The max is: " << Maximum(m, n) << std::endl;

    // The following (ambiguous) line generates a compiler error
    // std::cout << "The maximum is: " << Maximum(a, y) << std::endl;

    // We can force choice by using an explicit typecast
    std::cout << "The max is: " << Maximum(static_cast<float>(a), y) << std::endl;

    return 0;
}

// function definitions
int Maximum(int arg1, int arg2)
{
    return (arg1 > arg2) ? arg1 : arg2;
}

// overloaded function
float Maximum(float arg1, float arg2)
{
    return (arg1 > arg2) ? arg1 : arg2;
}
