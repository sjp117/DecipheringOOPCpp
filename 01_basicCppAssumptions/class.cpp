#include <iostream>

class Student // Typical for class name to be capitalized
{
public:
    std::string name;
    float semesterGrade[5];
    float gpa;
};

int main()
{
    Student s1;
    s1.name = "George Katz";
    s1.semesterGrade[0] = 3.0;
    s1.gpa = 3.5;

    std::cout << s1.name << " has GPA: " << s1.gpa << std::endl;
    return 0;
}