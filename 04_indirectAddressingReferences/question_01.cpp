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
void ReadData(Student &);
// void Print(const Student *);
void Print(const Student &);

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

// overload
void ReadData(Student &student)
{
    std::cout << "Enter the student's first name: " << std::flush;
    std::cin >> student.firstName;

    std::cout << "Enter the student's last name: " << std::flush;
    std::cin >> student.lastName;

    std::cout << "Enter the student's current course: " << std::flush;
    std::cin >> student.currentCourse;

    std::cout << "Enter the student's GPA: " << std::flush;
    std::cin >> student.gpa;
}

void Print(const Student *student)
{
    std::cout << "The student's name is: " << (student->firstName) << " " << (student->lastName) << ".\n";
    std::cout << "Their current course is: " << (student->currentCourse) << ".\n";
    std::cout << "They have a GPA of: " << (student->gpa) << "." << std::endl;
}

void Print(const Student &student)
{
    std::cout << "The student's name is: " << student.firstName << " " << student.lastName << ".\n";
    std::cout << "Their current course is: " << student.currentCourse << ".\n";
    std::cout << "They have a GPA of: " << student.gpa << "." << std::endl;
}

int main()
{
    int size = 0;

    // define student variables
    const Student **pstudents = nullptr;

    std::cout << "How many students? ";
    std::cin >> size;
    std::cout << std::endl;

    Student students[size];

    pstudents = new const Student *[size];
    for (int i = 0; i < size; i++)
    {
        pstudents[i] = nullptr;
    }

    // call ReadData() to input data
    for (int i = 0; i < size; i++)
    {
        ReadData(students[i]);
        pstudents[i] = ReadData();
    }

    // call print function using default
    for (int i = 0; i < size; i++)
    {
        Print(students[i]);
        Print(pstudents[i]);
    }

    // deallocate student pointers
    for (int i = 0; i < size; i++)
    {
        delete[] pstudents[i];
    }
    delete[] pstudents;

    return 0;
}
