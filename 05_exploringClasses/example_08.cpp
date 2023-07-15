// Adding inline functions for potential efficiency

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
    ~Student();               // destructor
    void Print();

    // inline function definitions
    const std::string &GetFirstName() { return firstName; }
    const std::string &GetLastName() { return lastName; }
    char GetMiddleInitial() { return middleInitial; }
    float GetGpa() { return gpa; } // access function for private data mbr
    const char *GetCurrentCourse() { return currentCourse; }
    void SetCurrentCourse(const char *); // prototype
};

inline void Student::SetCurrentCourse(const char *c)
{
    delete[] currentCourse;
    currentCourse = new char[strlen(c) + 1];
    strcpy(currentCourse, c);
}

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

// destructor definition
Student::~Student()
{
    delete[] currentCourse;
}

int main()
{
    Student s1("Jo", "Muritz", 'Z', 4.0, "C++");
    std::cout << s1.GetFirstName() << " " << s1.GetLastName() << " Enrolled in: " << s1.GetCurrentCourse() << std::endl;
    s1.SetCurrentCourse("Advanced C++ Programming");
    std::cout << s1.GetFirstName() << " " << s1.GetLastName() << " New course: " << s1.GetCurrentCourse() << std::endl;
    return 0;
}