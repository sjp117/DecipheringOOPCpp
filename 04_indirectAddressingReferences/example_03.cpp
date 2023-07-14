// Passing references as arguments to functions

#include <iostream>

void AddOne(int &arg)
{
    arg++;
}

void AddOne(int *arg)
{
    (*arg)++;
}

void Display(int &arg)
{
    std::cout << arg << " " << std::flush;
}

// function prototypes
void AddOne(int &);
void AddOne(int *);
void Display(int &);

int main()
{
    int x = 10, *y = nullptr;
    y = new int;
    *y = 15;
    Display(x);
    Display(*y);

    AddOne(x);  // calls reference version (with an object)
    AddOne(*y); // also calls reference version
    Display(x);
    Display(*y);

    AddOne(&x); // calls pointer version
    AddOne(y);  // also calls pointer version
    Display(x);
    Display(*y);

    delete y;
    return 0;
}