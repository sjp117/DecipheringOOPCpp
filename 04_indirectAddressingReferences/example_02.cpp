// Referencing existing objects of user defined types

#include <iostream>

class Student
{
public:
    std::string name;
    float gpa;
};

int main()
{
    Student s1;
    Student &sRef = s1; // establish a reference to s1
    s1.name = "Katje Katz";
    s1.gpa = 3.75;

    std::cout << s1.name << " has GPA: " << s1.gpa << std::endl;
    std::cout << sRef.name << " has GPA: " << sRef.gpa << std::endl;

    sRef.name = "George Katz"; // change the data
    sRef.gpa = 3.25;

    std::cout << s1.name << " has GPA: " << s1.gpa << std::endl;
    std::cout << sRef.name << " has GPA: " << sRef.gpa << std::endl;

    return 0;
}