// Using pointers to constant objects as function arguments and as return types from functions

#include <iostream>

struct collection
{
    int x;
    int y;
};

// function prototypes
void Update(collection &);
void Print(const collection &);

int main()
{
    collection collect1, *collect2 = nullptr;
    collect2 = new collection; // allocate memory from heap
    Update(collect1);          // a reference to an object is passed
    Update(*collect2);         // dereference of pointer == object is passed.
    Print(collect1);
    Print(*collect2);
    delete collect2;
    return 0;
}

void Update(collection &c)
{
    std::cout << "Enter <int> and <float> members: ";
    std::cin >> c.x >> c.y;
}

void Print(const collection &c)
{
    std::cout << "x member is: " << c.x;
    std::cout << "    y member is: " << c.y << std::endl;
}