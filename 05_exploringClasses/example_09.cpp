// Adding const data members and the member initialization list

#include <iostream>

class Student
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial;
    float gpa;
    std::string currentCourse;
    const int studentID; // added constant data member

public: // public members are accessible from any scope
    // member function prototypes
    Student(); // default constructor
    Student(const std::string &, const std::string &, char, float, const std::string &, int);
    Student(const Student &); // copy constructor prototype
    // ~Student();             // destructor; I dont think this is needed because the default is adequate
    void Print();

    // inline function definitions
    const std::string &GetFirstName() { return firstName; }
    const std::string &GetLastName() { return lastName; }
    char GetMiddleInitial() { return middleInitial; }
    float GetGpa() { return gpa; } // access function for private data mbr
    const std::string &GetCurrentCourse() { return currentCourse; }
    void SetCurrentCourse(const std::string &); // prototype
};

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
    Student s1("Renee", "Alexander", 'Z', 3.7, "C++", 1290);
    std::cout << s1.GetFirstName() << " " << s1.GetLastName();
    std::cout << " has gpa of: " << s1.GetGpa() << std::endl;
    return 0;
}