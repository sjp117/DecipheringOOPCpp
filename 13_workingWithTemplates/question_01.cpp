/*
    Convert your ArrayInt class from Chapter 12, Friends and Operator Overloading, to a
    template Array class to support a dynamically allocated array of any data type that can be
    easily resized and has built-in bounds checking
*/

#include <iostream>
#include <iomanip>

template <class Type>
class ArrayType
{
private:
    int numElements = 0;
    Type *contents = nullptr;

public:
    ArrayType(int); // set numElements and allocate contents
    ~ArrayType();

    // return a referenceable memory location or throw an exception
    Type &operator[](int);
    std::ostream &operator<<(std::ostream &);

    void Resize(int);
    void RemoveElement(int);
    void AddElement(Type, int);
    const int &GetNumElements() const { return numElements; }
};

template <class Type>
ArrayType<Type>::ArrayType(int size)
{
    numElements = size;
    contents = new Type[numElements]{};
}

template <class Type>
ArrayType<Type>::~ArrayType()
{
    delete[] contents;
    std::cout << "Array destroyed" << std::endl;
}

template <class Type>
Type &ArrayType<Type>::operator[](int index)
{
    if (index < numElements)
        return contents[index];
    else
        throw std::out_of_range(std::to_string(index));
}

template <class Type>
std::ostream &ArrayType<Type>::operator<<(std::ostream &out)
{
    for (int i = 0; i < this->GetNumElements(); i++)
    {
        out << this->contents[i] << "  ";
    }

    return out;
}

template <class Type>
void ArrayType<Type>::Resize(int size)
{
    Type *temp = nullptr;
    temp = new Type[size];
    memcpy(temp, contents, size * sizeof(Type));
    if (size > numElements)
    {
        for (int i = numElements; i < size; i++)
        {
            temp[i] = 0;
        }
    }
    delete[] contents;
    numElements = size;
    contents = temp;
}

template <class Type>
void ArrayType<Type>::RemoveElement(int index)
{
    int tempSize = numElements - 1;
    Type *temp = nullptr;
    temp = new Type[tempSize];
    std::copy(contents, contents + index, temp);
    std::copy(contents + index + 1, contents + numElements, temp + index);
    delete[] contents;
    numElements = tempSize;
    contents = temp;
}

template <class Type>
void ArrayType<Type>::AddElement(Type value, int index)
{
    int tempSize = numElements + 1;
    Type *temp = nullptr;
    temp = new Type[tempSize];
    std::copy(contents, contents + index, temp);
    std::copy(contents + index, contents + numElements, temp + index + 1);
    temp[index] = value;
    delete[] contents;
    numElements = tempSize;
    contents = temp;
}

int main()
{
    ArrayType<int> a1(5); // create ArrayInt of 5 elements
    try
    {
        for (int i = 0; i < a1.GetNumElements(); i++)
        {
            a1[i] = i;
        }
        a1 << std::cout << std::endl;
        a1.Resize(8);
        a1 << std::cout << std::endl;
        a1.RemoveElement(0);
        a1 << std::cout << std::endl;
        a1.AddElement(23, 2);
        a1 << std::cout << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Out of range: " << e.what() << std::endl;
    }

    ArrayType<char> c1(5); // create ArrayChar of 5 elements
    try
    {
        for (int i = 0; i < c1.GetNumElements(); i++)
        {
            c1[i] = static_cast<char>('a' + i);
        }
        c1 << std::cout << std::endl;
        c1.Resize(8);
        c1 << std::cout << std::endl;
        c1.RemoveElement(0);
        c1 << std::cout << std::endl;
        c1.AddElement('x', 2);
        c1 << std::cout << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Out of range: " << e.what() << std::endl;
    }

    ArrayType<float> f1(5); // create ArrayChar of 5 elements
    try
    {
        for (int i = 0; i < f1.GetNumElements(); i++)
        {
            f1[i] = static_cast<float>(i) + 0.1;
        }
        std::cout << std::setprecision(2);
        f1 << std::cout << std::endl;
        f1.Resize(8);
        f1 << std::cout << std::endl;
        f1.RemoveElement(0);
        f1 << std::cout << std::endl;
        f1.AddElement(2.3f, 2);
        f1 << std::cout << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Out of range: " << e.what() << std::endl;
    }

    return 0;
}