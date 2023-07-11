/*
Write a small C++ program to prompt a user to enter information regarding a Student, and
print out the data.

a.  Create a data type for Student using a class or struct. Student information
    should minimally include firstName, lastName, gpa, and the currentCourse
    in which the Student is registered.
b.  Create a function to print out all the data for the Student. Remember to prototype this function.
    Use a default value of 4.0 for gpa in the prototype of this function. Call this
    function two ways: once passing in each argument explicitly, and once using the default gpa.
c.  Overload the print function with one that either prints out selected data (for example,
    lastName and gpa) or with a version of this function that takes a Student as an
    argument (but not a pointer or reference to a Student – we’ll do that later). Remember
    to prototype this function.
d.  Use iostreams for I/O.
*/

#include <iostream>
#include <iomanip>
#include <cstring>

// Student type declarations
class Student
{
public:
    std::string firstName;
    std::string lastName;
    std::string currentCourse;
    float gpa;
};

// Function prototypes
void printStudentInfo(std::string fname, std::string lname, std::string currCourse, float gpa);
void printStudentInfo(Student student);

// Function definitions
void printStudentInfo(std::string fname, std::string lname, std::string currCourse, float gpa = 4.0)
{
    std::cout << "The student's name is: " << fname << " " << lname << ".\n";
    std::cout << "Their current course is: " << currCourse << ".\n";
    std::cout << "They have a GPA of: " << gpa << "." << std::endl;
}

void printStudentInfo(Student student)
{
    std::cout << "The student's name is: " << student.firstName << " " << student.lastName << ".\n";
    std::cout << "Their current course is: " << student.currentCourse << ".\n";
    std::cout << "They have a GPA of: " << student.gpa << "." << std::endl;
}

int main()
{
    // define student variables and their array
    Student s1, s2, s3;

    // initialize student's data
    s1.firstName = "Bob";
    s1.lastName = "Doodle";
    s1.currentCourse = "English Literature";
    s1.gpa = 3.8;

    s2.firstName = "Izzy";
    s2.lastName = "Lee";
    s2.currentCourse = "Economics";
    s2.gpa = 3.9;

    s3.firstName = "Alex";
    s3.lastName = "Stan";
    s3.currentCourse = "Calculus";
    s3.gpa = 3.5;

    // call print function using default
    printStudentInfo(s2.firstName, s2.lastName, s2.currentCourse);

    // call print function without default
    printStudentInfo(s3.firstName, s3.lastName, s3.currentCourse, s3.gpa);

    // call print function using overload
    printStudentInfo(s1);

    return 0;
}
