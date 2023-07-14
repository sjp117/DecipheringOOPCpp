#include <iostream>

int main()
{
    int *ptr = new int;
    *ptr = 20;
    int *&refPtr = ptr; // establish a reference to a ptr
    std::cout << *ptr << " " << *refPtr << std::endl;
    delete ptr;
    return 0;
}