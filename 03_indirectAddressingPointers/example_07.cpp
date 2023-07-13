// Using pointers as return values from functions

#include <iostream>
#include <iomanip>

constexpr int MAX = 20;
[[nodiscard]] char *createName(); // function prototype

int main()
{
    char *name = nullptr; // pointer declaration and init
    name = createName();  // function will allocate memory
    std::cout << "Name: " << name << std::endl;

    delete[] name; // deallocate memory in a different scope, this can be error prone!
    return 0;
}

// function definition
[[nodiscard]] char *createName()
{
    char *temp = new char[MAX];
    std::cout << "Enter name: " << std::flush;
    std::cin >> std::setw(MAX) >> temp; // ensure no overflow of temp with setw()
    return temp;
}