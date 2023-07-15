// Using const member functions

#include <iostream>

class Student
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial;
    float gpa;
    std::string currentCourse;
    const int studentID; // constant data member

public: // public members are accessible from any scope
    // member function prototypes
    Student(); // default constructor
    Student(const std::string &, const std::string &, char, float, const std::string &, int);
    Student(const Student &); // copy constructor prototype
    // ~Student();             // destructor; I dont think this is needed because the default is adequate
    void Print() const;

    // inline function definitions
    const std::string &GetFirstName() const { return firstName; }
    const std::string &GetLastName() const { return lastName; }
    char GetMiddleInitial() const { return middleInitial; }
    float GetGpa() const { return gpa; } // access function for private data mbr
    const std::string &GetCurrentCourse() const { return currentCourse; }
    void SetCurrentCourse(const std::string &); // prototype
};

// Student::Print() has been modified
void Student::Print() const
{
    std::cout << firstName << " " << middleInitial << ". ";
    std::cout << lastName << " with id: " << studentID;
    std::cout << " and gpa: " << gpa << " is enrolled in: ";
    std::cout << currentCourse << std::endl;
}

// constructor with member initialization list to set data members
Student::Student() : firstName(), lastName(), middleInitial('\0'),
                     gpa(0.0), currentCourse(), studentID()
{
    // further definitions are not needed since members have been initialized in the member list
}

Student::Student(const std::string &fn, const std::string &ln, char mi, float avg, const std::string &course, int id) : firstName(fn), lastName(ln), middleInitial(mi), gpa(avg), currentCourse(course), studentID(id)
{
    // further definitions are not needed since members have been initialized in the member list
}

Student::Student(const Student &s) : firstName(s.firstName), lastName(s.lastName), middleInitial(s.middleInitial), gpa(s.gpa), currentCourse(s.currentCourse), studentID(s.studentID)
{
    // further definitions are not needed since members have been initialized in the member list
}

inline void Student::SetCurrentCourse(const std::string &course)
{
    currentCourse = course;
}

int main()
{
    Student s1("Zack", "Moon", 'R', 3.75, "C++", 1378);
    std::cout << s1.GetFirstName() << " " << s1.GetLastName();
    std::cout << " Enrolled in " << s1.GetCurrentCourse();
    std::cout << std::endl;
    s1.SetCurrentCourse("Advanced C++ Programming");
    std::cout << s1.GetFirstName() << " " << s1.GetLastName();
    std::cout << " New course: " << s1.GetCurrentCourse();
    std::cout << std::endl;

    const Student s2("Gabby", "Doone", 'A', 4.0, "C++", 2239);
    s2.Print();
    // not allowed with s2 since it is const
    // s2.SetCurrentCourse("Advanced C++ Programming");
    return 0;
}