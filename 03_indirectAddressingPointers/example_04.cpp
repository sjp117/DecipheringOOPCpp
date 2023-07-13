// Dynamically allocating 2-D arrays – pointers to pointers

#include <iostream>

int main()
{
    int numRows = 0, numColumns = 0;
    float **TwoDimArray = nullptr; // pointer to a pointer

    std::cout << "Enter number of rows: " << std::flush;
    std::cin >> numRows;
    TwoDimArray = new float *[numRows]; // allocate row pointers

    std::cout << "Enter number of columns: " << std::flush;
    std::cin >> numColumns;

    for (int i = 0; i < numRows; i++)
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

    for (int i = 0; i < numRows; i++)
    {
        // delete column for each row
        delete[] TwoDimArray[i];
    }
    // delete allocated rows
    delete[] TwoDimArray;

    return 0;
}