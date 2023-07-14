// Declaring, initializing, and accessing references

#include <iostream>

int main()
{
    int x = 10;
    int *p = new int; // allocate memory for ptr variable
    *p = 20;          // deference and assign value

    int &refInt1 = x;  // reference to an integer
    int &refInt2 = *p; // also a reference to an integer

    std::cout << x << " " << *p << " " << refInt1 << " " << refInt2 << std::endl;

    x++;    // update x and refInt1
    (*p)++; // update *p and refInt2

    std::cout << x << " " << *p << " " << refInt1 << " " << refInt2 << std::endl;

    refInt1++; // update refInt1 and x
    refInt2++; // update refInt2 and *p

    std::cout << x << " " << *p << " " << refInt1 << " " << refInt2 << std::endl;

    delete p; // deallocate p's memory
    return 0;
}