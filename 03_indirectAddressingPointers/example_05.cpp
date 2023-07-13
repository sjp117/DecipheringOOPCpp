// Dynamically allocating N-D arrays – pointers to pointers to pointers

#include <iostream>

int main()
{
    int dim1 = 0, dim2 = 0, dim3 = 3;
    int ***ThreeDimArray = nullptr; // 3D dynamic allocation array

    std::cout << "Enter dim 1, dim 2, dim 3: ";
    std::cin >> dim1 >> dim2 >> dim3;
    ThreeDimArray = new int **[dim1]; // allocate dim 1

    for (int i = 0; i < dim1; i++)
    {
        ThreeDimArray[i] = new int *[dim2]; // allocate dim 2
        for (int j = 0; j < dim2; j++)
        {
            // allocate dim 3
            ThreeDimArray[i][j] = new int[dim3]; // allocate dim 3
            for (int k = 0; k < dim3; k++)
            {
                ThreeDimArray[i][j][k] = i + j + k;
                std::cout << ThreeDimArray[i][j][k] << " ";
            }
            std::cout << std::endl; // print "\n" between dimensions
        }
        std::cout << std::endl; // print "\n" between dimensions
    }
    for (int i = 0; i < dim1; i++)
    {
        for (int j = 0; j < dim2; j++)
        {
            delete[] ThreeDimArray[i][j]; // release dim 3
        }
        delete[] ThreeDimArray[i]; // release dim 2
    }
    delete[] ThreeDimArray; // release dim 1

    return 0;
}