/*
    Reviewing user defined type basics:
    Review the basic mechanisms to bundle together only data in struct, class, and typedef.
    Also review enumerated types to represent lists of integers and more meaningfully.
*/

#include <iostream>

struct student      // Type names are typically lower case
{
    std::string name;
    float semesterGrades[5];
    float gpa;
};

int main()
{
    student s1;
    s1.name = "George Katz";
    s1.semesterGrades[0] = 3.0;
    s1.semesterGrades[1] = 4.0;
    s1.gpa = 3.5;

    std::cout << s1.name << " has GPA: " << s1.gpa << std::endl;
    return 0;
}