#include <iostream>
#include <iomanip>
#include <cstring>

// simple const varaible declaration and initialization
// Conventional for constants known in compile time to be in allcaps.
const int MAX = 50;

// simple constexpr variable declaration and initialization (preferred)
constexpr int LARGEST = 50;

constexpr int Minimum(int a, int b)
{
    return (a < b) ? a : b; // conditional operator "?:" (if (something) a else b)
}

int main()
{
    int x = 0, y = 0;
    constexpr int a = 10, b = 15;

    std::cout << "Enter two <int> values: ";
    std::cin >> x >> y;

    const int min = Minimum(x, y);
    std::cout << "Minimum is: " << min << std::endl;

    constexpr int smallest = Minimum(a, b);
    std::cout << "Smallest of " << a << " " << b << " is " << smallest << std::endl;

    char bigName[MAX] = {""};         // const used for size of array
    char largestName[LARGEST] = {""}; // same with constexpr

    std::cout << "Enter two names: ";
    std::cin >> std::setw(MAX) >> bigName >> std::setw(LARGEST) >> largestName;

    const int namelen = strlen(bigName);
    std::cout << "Length of name 1: " << namelen << std::endl;
    std::cout << "Length of name 2: " << strlen(largestName) << std::endl;

    return 0;
}