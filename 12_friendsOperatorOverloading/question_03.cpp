/*
    1. Overload operator[] to return an element if it exists in the array,
       or throw an exception if it is OutOfBounds.

    2. Add other methods to ArrayInt, such as Resize(), RemoveElement().

    3. Model the data comprising the array using a dynamically allocated array
       (that is, using int *contents) so that you can easily handle resizing.
*/

#include <iostream>

class ArrayInt
{
private:
    int numElements = 0;
    int *contents = nullptr;

public:
    ArrayInt(int); // set numElements and allocate contents
    ~ArrayInt();

    // return a referenceable memory location or throw an exception
    int &operator[](int);
    std::ostream &operator<<(std::ostream &);

    void Resize(int);
    void RemoveElement(int);
    void AddElement(int, int);
    const int &GetNumElements() const { return numElements; }
};

ArrayInt::ArrayInt(int size)
{
    numElements = size;
    contents = new int[numElements];
    for (int i = 0; i < numElements; i++)
    {
        contents[i] = 0;
    }
}

ArrayInt::~ArrayInt()
{
    delete[] contents;
    std::cout << "ArrayInt destroyed" << std::endl;
}

int &ArrayInt::operator[](int index)
{
    if (index < numElements)
        return contents[index];
    else
        throw std::out_of_range(std::to_string(index));
}

std::ostream &ArrayInt::operator<<(std::ostream &out)
{
    for (int i = 0; i < this->GetNumElements(); i++)
    {
        out << this->contents[i] << "  ";
    }

    return out;
}

void ArrayInt::Resize(int size)
{
    int *temp = nullptr;
    temp = new int[size];
    memcpy(temp, contents, size * sizeof(int));
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

void ArrayInt::RemoveElement(int index)
{
    int tempSize = numElements - 1;
    int *temp = nullptr;
    temp = new int[tempSize];
    std::copy(contents, contents + index, temp);
    std::copy(contents + index + 1, contents + numElements, temp + index);
    delete[] contents;
    numElements = tempSize;
    contents = temp;
}

void ArrayInt::AddElement(int value, int index)
{
    int tempSize = numElements + 1;
    int *temp = nullptr;
    temp = new int[tempSize];
    std::copy(contents, contents + index, temp);
    std::copy(contents + index, contents + numElements, temp + index + 1);
    temp[index] = value;
    delete[] contents;
    numElements = tempSize;
    contents = temp;
}

int main()
{
    ArrayInt a1(5); // create ArrayInt of 5 elements
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

    return 0;
}