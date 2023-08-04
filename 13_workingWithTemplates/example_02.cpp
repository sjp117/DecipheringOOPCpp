// Creating and using template classes

#include <iostream>
#include <stdexcept>

template <class Type> // template class preamble
class Array
{
private:
    int numElements = 0;      // in-class initialization
    Type *contents = nullptr; // dynamically allocated array

public:
    Array(int size) : numElements(size), contents(new Type[size]){};
    ~Array() { delete[] contents; }
    void Print() const;
    Type &operator[](int index)
    {
        if (index < numElements)
            return contents[index];
        else
            throw std::out_of_range(std::to_string(index));
    }
    void operator+(Type); // prototype only
};

template <class Type>
void Array<Type>::operator+(Type item)
{
}

template <class Type>
void Array<Type>::Print() const
{
    for (int i = 0; i < numElements; i++)
        std::cout << contents[i] << " ";
    std::cout << std::endl;
}

int main()
{
    // creation of int array will trigger template expansion by preprocessor
    Array<int> a1(3); // Create int array with 3 elements
    try
    {
        a1[2] = 12;
        a1[1] = 70;
        a1[0] = 2;
        a1[100] = 10; // this argument throws an exception
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Out of range: index " << e.what() << std::endl;
    }
    a1.Print();

    return 0;
}