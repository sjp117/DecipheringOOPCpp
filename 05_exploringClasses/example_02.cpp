// Examining member function internals; the “this” pointer

#include <iostream>
#include <cstring> // demonstration purpose

class Student
{
public:
    std::string firstName;
    std::string lastName;
    char middleInitial;
    float gpa;
    char *currentCourse;

    // member function prototypes
    void Initialize(std::string, std::string, char, float, const char *);
    void Print();
};

// member function definitions
void Student::Initialize(std::string fn, std::string ln, char mi, float gpa, const char *course)
{
    firstName = fn;
    lastName = ln;
    this->middleInitial = mi; // optional use of 'this'
    this->gpa = gpa;          // required, explicit use of 'this' to disambiguate
    // remember to allocate memory for pointer data members
    currentCourse = new char[strlen(course) + 1];
    strcpy(currentCourse, course);
}

void Student::Print()
{
    std::cout << firstName << " ";
    std::cout << middleInitial << ". ";
    std::cout << lastName << " has a gpa of: ";
    std::cout << gpa << " and is enrolled in: ";
    std::cout << currentCourse << std::endl;
}

int main()
{
    Student s1;
    Student *s2 = new Student; // pointer to an instance
    s1.Initialize("Mary", "Jacobs", 'I', 3.9, "C++");
    s2->Initialize("Sam", "Nelson", 'B', 3.2, "C++");
    s1.Print();
    s2->Print(); // or use (*s2).Print();

    delete[] s1.currentCourse; // delete dynamically allocated data members
    delete[] s2->currentCourse;
    delete s2; // delete dynamically allocated instance
    return 0;
}