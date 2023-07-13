#include <iostream>

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
[[nodiscard]] Student *ReadData();
void printD(Student *student);

// Function definitions
[[nodiscard]] Student *ReadData()
{
    Student *tempS = new Student;

    std::cout << "Enter the student's first name: " << std::flush;
    std::cin >> (tempS->firstName);

    std::cout << "Enter the student's last name: " << std::flush;
    std::cin >> (tempS->lastName);

    std::cout << "Enter the student's current course: " << std::flush;
    std::cin >> (tempS->currentCourse);

    std::cout << "Enter the student's GPA: " << std::flush;
    std::cin >> (tempS->gpa);

    return tempS;
}

void printD(Student *student)
{
    std::cout << "The student's name is: " << (student->firstName) << " " << (student->lastName) << ".\n";
    std::cout << "Their current course is: " << (student->currentCourse) << ".\n";
    std::cout << "They have a GPA of: " << (student->gpa) << "." << std::endl;
}

void printD(const Student *student)
{
    std::cout << "The student's name is: " << (student->firstName) << " " << (student->lastName) << ".\n";
    std::cout << "Their current course is: " << (student->currentCourse) << ".\n";
    std::cout << "They have a GPA of: " << (student->gpa) << "." << std::endl;
}

int main()
{
    int size = 0;

    // define student variables
    Student **students = nullptr;

    std::cout << "How many students? " << std::flush;
    std::cin >> size;
    std::cout << std::endl;
    size--;

    students = new Student *[size];
    for (int i = 0; i < size; i++)
    {
        students[i] = nullptr;
    }
    const Student *constS = nullptr;

    // call ReadData() to input data
    for (int i = 0; i < size; i++)
    {
        students[i] = ReadData();
    }
    constS = ReadData();

    // call print function using default
    for (int i = 0; i < size; i++)
    {
        printD(students[i]);
    }
    printD(constS);

    // deallocate student pointers
    for (int i = 0; i < size; i++)
    {
        delete[] students[i];
    }
    delete[] students;
    delete constS;

    return 0;
}
