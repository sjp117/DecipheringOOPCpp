#include <iostream>

int main()
{
    void *unspecified = nullptr; // may point to any data type
    int *x = nullptr;

    unspecified = new int; // void ptr now points to an int
    // void * must be cast to int * before dereferencing
    *(static_cast<int *>(unspecified)) = 89;

    // let x point to the memory that unspecified points to
    x = static_cast<int *>(unspecified);
    std::cout << *x << " " << *(static_cast<int *>(unspecified)) << std::endl;

    delete static_cast<int *>(unspecified);

    return 0;
}