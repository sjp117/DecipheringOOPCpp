// Using access labels and access regions

#include <iostream>
#include <cstring> // for demonstration

class Student
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial;
    float gpa;
    char *currentCourse;

public: // public members are accessible from any scope
    // member function prototypes
    void Initialize();
    void Initialize(std::string, std::string, char, float, const char *);
    void CleanUp();
    void Print();
};

void Student::Initialize()
{
    // even though string data members are empty at first initialization
    // we show how to clean them should we initialize more than once.
    firstName.clear();
    lastName.clear();
    middleInitial = '\0';
    gpa = 0.0;
    currentCourse = nullptr;
}

// overload member initialization function
void Student::Initialize(std::string fn, std::string ln, char mi, float avg, const char *course)
{
    firstName = fn;
    lastName = ln;
    middleInitial = mi;
    gpa = avg;
    // dynamically allocate memory for pointer data member
    currentCourse = new char[strlen(course) + 1];
    strcpy(currentCourse, course);
}

void Student::CleanUp()
{
    // deallocate previously allocated memory
    delete[] currentCourse;
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

    // Initialize, Print, CleanUp are public and accessible from any scope
    s1.Initialize("Ming", "Li", 'I', 3.9, "C++");

    s1.Print();

    // Error! private firstName is not accessible in main()
    // std::cout << s1.firstName << std::endl;

    s1.CleanUp();
    return 0;
}