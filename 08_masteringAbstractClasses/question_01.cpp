#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

constexpr float triDiv = 2.0;
constexpr float cirConst = 2.0;

class Shape // abstract class
{
public:
    Shape() = default;
    virtual ~Shape() = default; // virtual destructor is required
    virtual std::string IsA() const { return "Shape"; }
    virtual float Area() const = 0;
};

class Circle: public Shape
{
private:
    float radian;

public:
    Circle() = default;
    Circle(float r) : radian(r) { }
    Circle(const Circle &cir) : radian(cir.radian) { }
    ~Circle() override = default;
    std::string IsA() const override final { return "Shape"; }
    float GetRadian() const { return radian; }
    float Area() const override final { return M_PI * pow(radian, cirConst); }
};

class Triangle: public Shape
{
private:
    float height;
    float width;

public:
    Triangle() = default;
    Triangle(float h, float w) : height(h), width(w) { }
    Triangle(const Triangle &tri) : height(tri.height), width(tri.width) { }
    ~Triangle() override = default;
    std::string IsA() const override final { return "Triangle"; }
    float GetHeight() const { return height; }
    float GetWidth() const { return width; }
    float Area() const override final { return (height * width) / triDiv; };
};

class Rectangle: public Shape
{
private:
    float height;
    float width;

public:
    Rectangle() = default;
    Rectangle(float h, float w) : height(h), width(w) { }
    Rectangle(const Rectangle &rect) : height(rect.height), width(rect.width) { }
    ~Rectangle() override = default;
    std::string IsA() const override { return "Rectangle"; }
    float GetHeight() const { return height; }
    float GetWidth() const { return width; }
    float Area() const override { return height * width; };
};

class Square: public Rectangle
{
private:
    float length;
public:
    Square() = default;
    Square(float l) : Rectangle(l, l) { }
    Square(const Square &sq) : length(sq.length) { }
    ~Square() override = default;
    std::string IsA() const override final { return "Square"; }
    float GetLength() const { return length; }
    float Area() const override {return Rectangle::Area(); }
};

int main()
{
    constexpr int MAX = 4;
    Shape *shapes[MAX] = { };
    shapes[0] = new Circle(4.0);
    shapes[1] = new Triangle(4.0, 3.0);
    shapes[2] = new Rectangle(5.0, 3.0);
    shapes[3] = new Square(4.0);

    for (Shape *item : shapes)
    {
        std::cout << item->IsA() << "    " << "Area: " << item->Area() << std::endl;
    }

    for (Shape *item : shapes)
    {
        delete item;
    }

    return 0;
}