// I cant figure out how to fix the one bug here. fails to compile

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
    virtual std::string IsA() const { return "Shape"; };
    virtual float Area() const = 0;
    // virtual void operator=(const Shape &);
    virtual std::ostream &operator<<(std::ostream &) const;
};

class Circle : public Shape
{
private:
    float radian;

public:
    Circle() = default;
    Circle(float r) : radian(r) {}
    Circle(const Circle &cir) : radian(cir.radian) {}
    ~Circle() override = default;
    std::string IsA() const override final { return "Shape"; }
    float GetRadian() const { return radian; }
    float Area() const override final { return M_PI * pow(radian, cirConst); }
    void operator=(const Circle &) { std::cout << IsA() << std::endl; }
    std::ostream &operator<<(std::ostream &) const override;
};

std::ostream &Circle::operator<<(std::ostream &out) const
{
    out << "This is a: " << Circle::IsA() << " and has a radian of: " << Circle::GetRadian();
    return out;
}

class Triangle : public Shape
{
private:
    float height;
    float width;

public:
    Triangle() = default;
    Triangle(float h, float w) : height(h), width(w) {}
    Triangle(const Triangle &tri) : height(tri.height), width(tri.width) {}
    ~Triangle() override = default;
    std::string IsA() const override final { return "Triangle"; }
    float GetHeight() const { return height; }
    float GetWidth() const { return width; }
    float Area() const override final { return (height * width) / triDiv; };
    std::ostream &operator<<(std::ostream &) const override;
};

std::ostream &Triangle::operator<<(std::ostream &out) const
{
    out << "This is a: " << Triangle::IsA() << ". It has a height of: " << Triangle::GetHeight()
        << ", a width of: " << Triangle::GetWidth() << ", and an area of: " << Triangle::Area();
    return out;
}

class Rectangle : public Shape
{
private:
    float height;
    float width;

public:
    Rectangle() = default;
    Rectangle(float h, float w) : height(h), width(w) {}
    Rectangle(const Rectangle &rect) : height(rect.height), width(rect.width) {}
    virtual ~Rectangle() override = default;
    std::string IsA() const override { return "Rectangle"; }
    float GetHeight() const { return height; }
    float GetWidth() const { return width; }
    float Area() const override { return height * width; };
    virtual std::ostream &operator<<(std::ostream &) const override;
};

std::ostream &Rectangle::operator<<(std::ostream &out) const
{
    out << "This is a: " << Rectangle::IsA() << ". It has a height of: " << Rectangle::GetHeight()
        << ", a width of: " << Rectangle::GetWidth() << ", and an area of: " << Rectangle::Area();
    return out;
}

class Square : public Rectangle
{
private:
    float length;

public:
    Square() = default;
    Square(float l) : Rectangle(l, l), length(l) {}
    Square(const Square &sq) : Rectangle(sq.length, sq.length) {}
    ~Square() override = default;
    std::string IsA() const override final { return "Square"; }
    float GetLength() const { return length; }
    float Area() const override { return Rectangle::Area(); }
    std::ostream &operator<<(std::ostream &) const override final;
};

std::ostream &Square::operator<<(std::ostream &out) const
{
    out << "This is a: " << Square::IsA() << ". It has length of: " << length
        << ", and an area of: " << Square::Area();
    return out;
}

int main()
{
    Circle c1(5.0f);
    // Triangle t1(6.0f, 3.0f);
    // Rectangle r1(3.0f, 6.0f);
    // Square s1(5.0f);

    c1 << std::cout << std::endl;

    return 0;
}