// Using references as return values from functions

#include <iostream>

// function prototype
int &CreateID();

int main()
{
    int &id1 = CreateID(); // reference established
    int &id2 = CreateID();
    std::cout << "Id1: " << id1 << " Id2: " << id2 << std::endl;

    delete &id1, &id2; // here & is address-of not reference-to
    return 0;
}

// function returns a reference to an int
int &CreateID()
{
    static int count = 100; // initialize with first id
    int *memory = new int;
    *memory = count++; // use cout as id, then increment
    return *memory;
}