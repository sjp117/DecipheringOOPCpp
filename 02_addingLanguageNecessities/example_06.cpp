// Learning the basics of function overloading

#include <iostream>
#include <cmath>

constexpr float PI = 3.14159;

// simple user defined type declarations
class Circle
{
public:
    float radius;
    float area;
};

class Rectangle
{
public:
    float length;
    float width;
    float area;
};

// overloaded function prototypes as they differ in signature
void Display(Circle);
void Display(Rectangle);

int main()
{
    Circle myCircle;
    Rectangle myRect;
    Rectangle mySquare;

    myCircle.radius = 5.0;
    myCircle.area = PI * pow(myCircle.radius, 2.0);

    myRect.length = 2.0;
    myRect.width = 4.0;
    myRect.area = myRect.length * myRect.width;

    mySquare.length = 4.0;
    mySquare.width = 4.0;
    mySquare.area = mySquare.length * mySquare.width;

    Display(myCircle); // invoke: void Display(Circle)
    Display(myRect);   // invoke: void Display(Rectangle)
    Display(mySquare); // invoke: void Display(Rectangle)

    return 0;
}

void Display(Circle c)
{
    std::cout << "Circle with radius " << c.radius;
    std::cout << " has an area of " << c.area << std::endl;
}

void Display(Rectangle r)
{
    std::cout << "Rectangle with length " << r.length;
    std::cout << " and width " << r.width;
    std::cout << " has an area of " << r.area << std::endl;
}