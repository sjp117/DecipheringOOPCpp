// Passing pointers as arguments to functions

#include <iostream>

// function prototypes
void TryToAddOne(int);
void AddOne(int *);

int main()
{
    int x = 10, *y = nullptr;
    y = new int; // allocate y's memory
    *y = 15;     // deference y to assign a value
    std::cout << "x: " << x << " and *y: " << *y << std::endl;

    TryToAddOne(x);  // unsuccessful call by value
    TryToAddOne(*y); // still unsuccessful
    std::cout << "x: " << x << " and *y: " << *y << std::endl;

    AddOne(&x); // successful, passing an address
    AddOne(y);  // also successful
    std::cout << "x: " << x << " and *y: " << *y << std::endl;

    delete y; // release heap memory
    return 0;
}

void TryToAddOne(int arg)
{
    arg++;
}

void AddOne(int *arg)
{
    (*arg)++;
}