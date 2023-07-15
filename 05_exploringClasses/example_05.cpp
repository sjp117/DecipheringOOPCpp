// Creating copy constructors

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
    Student(); // default constructor
    Student(const std::string &, const std::string &, char, float, const char *);
    Student(const Student &); // copy constructor prototype
    void CleanUp();
    void Print();
    void SetFirstName(const std::string &);
};

// default constructor
Student::Student()
{
    // type strings are empty by defualt and already initialized
    middleInitial = '\0';
    gpa = 0.0;
    currentCourse = 0;
}

// alternate constructor
Student::Student(const std::string &fn, const std::string &ln, char mi, float avg, const char *course)
{
    firstName = fn;
    lastName = ln;
    middleInitial = mi;
    gpa = avg;
    // dynamically allocate memory for pointer
    currentCourse = new char[strlen(course) + 1];
    strcpy(currentCourse, course);
}

// copy constructor definition - deep copy
Student::Student(const Student &s)
{
    // assignment between strings will do a deep copy
    firstName = s.firstName;
    lastName = s.lastName;
    middleInitial = s.middleInitial;
    gpa = s.gpa;
    // for pointers ensure a deep copy by allocating memory for destination
    currentCourse = new char[strlen(s.currentCourse) + 1];
    strcpy(currentCourse, s.currentCourse);
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

void Student::SetFirstName(const std::string &fn)
{
    firstName = fn;
}

int main()
{
    // instantiate two students
    Student s1("Zachary", "Moon", 'R', 3.7, "C++");
    Student s2("Gabrielle", "Doone", 'A', 3.7, "C++");

    // these inits implicitly invoke copy constructor
    Student s3(s1);
    Student s4 = s2;
    s3.SetFirstName("Zack"); // alter each object slightly
    s4.SetFirstName("Gabby");

    // This sequence does not invoke copy constructor
    // This is instead an assignment.
    // Student s5("Giselle", "LeBrun", 'A', 3.1, "C++);
    // Student s6;
    // s6 = s5;   // this is assignment, not initialization

    s1.Print();
    s3.Print();
    s2.Print();
    s4.Print();

    s1.CleanUp();
    s2.CleanUp();
    s3.CleanUp();
    s4.CleanUp();
    return 0;
}