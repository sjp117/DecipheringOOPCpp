#include <iostream>

struct collection
{
    int x;
    float y;
};

int main()
{
    collection *item = nullptr; // pointer declaration
    item = new collection;      // memory allocation
    item->x = 9;                // use -> to access data member x
    (*item).y = 120.77;         // alt. notation to access member y

    std::cout << (*item).x << " " << item->y << std::endl;

    delete item; // relinquish memory

    return 0;
}