// Creating and using template functions

#include <iostream>

// template function prototype
template <class Type1, class Type2> // template preamble
Type2 ChooseFirst(Type1, Type2);

// template function definition
template <class Type1, class Type2> // template preamble
Type2 ChooseFirst(Type1 x, Type2 y)
{
    if (x < y)
        return static_cast<Type2>(x);
    else
        return y;
}

int main()
{
    int value1 = 4, value2 = 7;
    float value3 = 5.67f;
    std::cout << "First: " << ChooseFirst(value1, value3) << std::endl;
    std::cout << "First: " << ChooseFirst(value2, value1) << std::endl;
    return 0;
}