// Dynamically allocating 2-D arrays – an array of pointers

#include <iostream>

constexpr int NUMROWS = 5;

int main()
{
    float *TwoDimArray[NUMROWS] = {}; // initialize to nullpers
    int numColumns = 0;

    std::cout << "Enter number of columns: ";
    std::cin >> numColumns;

    for (int i = 0; i < NUMROWS; i++)
    {
        // allocate column quantity for each row
        TwoDimArray[i] = new float[numColumns];

        // load each column entry with data
        for (int j = 0; j < numColumns; j++)
        {
            TwoDimArray[i][j] = i + j + 0.05;
            std::cout << TwoDimArray[i][j] << " ";
        }
        std::cout << std::endl; // print new line between rows
    }
    for (int i = 0; i < NUMROWS; i++)
    {
        delete[] TwoDimArray[i]; // delete column for each row
    }
    return 0;
}