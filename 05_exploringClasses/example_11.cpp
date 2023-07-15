// Utilizing static data members and static member functions

#include <iostream>
#include <cstring>

class Student
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial;
    float gpa;
    std::string currentCourse;
    const char *studentID;  // constant data member
    static int numStudents; // status data member

public: // public members are accessible from any scope
    // member function prototypes
    Student(); // default constructor
    Student(const std::string &, const std::string &, char, float, const std::string &, const char *);
    Student(const Student &); // copy constructor prototype
    ~Student();               // destructor; I dont think this is needed because the default is adequate
    void Print() const;

    // inline function definitions
    const std::string &GetFirstName() const { return firstName; }
    const std::string &GetLastName() const { return lastName; }
    char GetMiddleInitial() const { return middleInitial; }
    float GetGpa() const { return gpa; } // access function for private data mbr
    const std::string &GetCurrentCourse() const { return currentCourse; }
    const char *GetStudentID() const { return studentID; }
    void SetCurrentCourse(const std::string &);
    static int GetNumberStudents(); // static member function
};

// definition for static data member
int Student::numStudents = 0; // initial value of 0 which is default for integral values

// definition for static member function
inline int Student::GetNumberStudents()
{
    return numStudents;
}

inline void Student::SetCurrentCourse(const std::string &c)
{
    currentCourse = c;
}

// constructor with member initialization list to set data members
Student::Student() : middleInitial('\0'), gpa(0.0), studentID(nullptr)
{
    numStudents++;
}

Student::Student(const std::string &fn, const std::string &ln, char mi, float avg, const std::string &course, const char *id) : firstName(fn), lastName(ln), middleInitial(mi), gpa(avg), currentCourse(course)
{
    char *temp = new char[strlen(id) + 1];
    // strcpy(studentID, id); // studentID cannot be an l-value
    studentID = temp; // but temp can be an l-value
    numStudents++;
}

Student::Student(const Student &s) : firstName(s.firstName), lastName(s.lastName), middleInitial(s.middleInitial), gpa(s.gpa), currentCourse(s.currentCourse)
{
    char *temp = new char[strlen(s.studentID) + 1];
    // strcpy(studentID, id); // studentID cannot be an l-value
    studentID = temp; // but temp can be an l-value
    numStudents++;
}

Student::~Student() // destructor denfinition
{
    delete[] studentID;
    numStudents--; // decrement static counter
}

void Student::Print() const
{
    std::cout << firstName << " " << middleInitial << ". ";
    std::cout << lastName << " with id: " << studentID;
    std::cout << " and gpa: " << gpa << " and is enrolled in: ";
    std::cout << currentCourse << std::endl;
}

int main()
{
    Student s1("Nick", "Cole", 'S', 3.65, "C++", "112HAV");
    Student s2("Alex", "Tost", 'A', 3.78, "C++", "674HOP");

    std::cout << s1.GetFirstName() << " " << s1.GetLastName() << " Enrolled in ";
    std::cout << s1.GetCurrentCourse() << std::endl;
    std::cout << s2.GetFirstName() << " " << s2.GetLastName() << " Enrolled in ";
    std::cout << s2.GetCurrentCourse() << std::endl;

    // call a static member function in the preferred manner
    std::cout << "There are " << Student::GetNumberStudents() << " students" << std::endl;

    // though not preferred, we could also use:
    // std::cout << "There are " << s1.GetNumberStudents() << " students" << std::endl;

    return 0;
}