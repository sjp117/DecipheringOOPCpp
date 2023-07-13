// Dynamically allocating single dimension arrays

#include <iostream>

struct collection
{
    int x;
    float y;
};

int main()
{
    int numElements = 0;
    int *intArray = nullptr; // pointer declaration to future arrays
    collection *collectionArray = nullptr;

    std::cout << "How many elements would you like? " << std::flush;
    std::cin >> numElements;

    intArray = new int[numElements]; // allocate array bodies
    collectionArray = new collection[numElements];

    // load array with values
    for (int i = 0; i < numElements; i++)
    {
        // load each array with values using array notation []
        intArray[i] = i;
        collectionArray[i].x = i;
        collectionArray[i].y = i + 0.5;

        // alternatively use ptr notation to print values
        std::cout << *(intArray + i) << " ";
        std::cout << (*(collectionArray + i)).y << std::endl;
    }

    // mark memory for deletion
    delete[] intArray;
    delete[] collectionArray;

    return 0;
}