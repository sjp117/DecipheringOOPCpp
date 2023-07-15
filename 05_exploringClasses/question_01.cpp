// Create a C++ program to encapsulate a Student

#include <iostream>
#include <iomanip>
#include <cstring>

class Person
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial;
    std::string dob;

public:
    Person();
    Person(const std::string &, const std::string &, char mi, const std::string &);
    Person(const Person &);
    const std::string &GetFirstName() const { return firstName; }
    const std::string &GetLastName() const { return lastName; }
    char GetMiddleInitial() const { return middleInitial; }
    const std::string &GetDateOfBirth() const { return dob; }
    void Print() const;
};

Person::Person() : middleInitial('\0'), dob("00/00/0000")
{
}

Person::Person(const std::string &fn, const std::string &ln, char mi, const std::string &bday) : firstName(fn), lastName(ln), middleInitial(mi), dob(bday)
{
}

Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial), dob(p.dob)
{
}

void Person::Print() const
{
    std::cout << GetFirstName() << " " << GetMiddleInitial() << ". " << GetLastName() << " was born in " << GetDateOfBirth() << std::endl;
}

class Student
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial;
    std::string dob;
    float gpa;
    std::string currentCourse;
    const char *studentID;  // constant data member
    static int numStudents; // status data member

public: // public members are accessible from any scope
    // member function prototypes
    Student(); // default constructor
    Student(const std::string &, const std::string &, char, const std::string &, float, const std::string &, const char *);
    Student(const Student &);
    Student(const Person &, const char *); // copy constructor prototype
    ~Student();                            // destructor; I dont think this is needed because the default is adequate
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
Student::Student() : middleInitial('\0'), dob("00/00/0000"), gpa(0.0), studentID(nullptr)
{
    numStudents++;
}

Student::Student(const std::string &fn, const std::string &ln, char mi, const std::string &dob, float avg, const std::string &course, const char *id) : firstName(fn), lastName(ln), middleInitial(mi), gpa(avg), currentCourse(course)
{
    char *temp = new char[strlen(id) + 1];
    // strcpy(studentID, id); // studentID cannot be an l-value
    studentID = temp; // but temp can be an l-value
    numStudents++;
}

Student::Student(const Student &s) : firstName(s.firstName), lastName(s.lastName), middleInitial(s.middleInitial), dob(s.dob), gpa(s.gpa), currentCourse(s.currentCourse)
{
    char *temp = new char[strlen(s.studentID) + 1];
    // strcpy(studentID, id); // studentID cannot be an l-value
    studentID = temp; // but temp can be an l-value
    numStudents++;
}

Student::Student(const Person &p, const char *id) : firstName(p.GetFirstName()), lastName(p.GetLastName()), middleInitial(p.GetMiddleInitial()), dob(p.GetDateOfBirth()), gpa(0.0), currentCourse("C++")
{
    char *temp = new char[strlen(id) + 1];
    // strcpy(studentID, id); // studentID cannot be an l-value
    studentID = temp; // but temp can be an l-value

    numStudents++;
}

Student::~Student() // destructor definition
{
    delete[] studentID;
    numStudents--; // decrement static counter
    std::cout << "Destructor called " << this << std::endl;
}

void Student::Print() const
{
    std::cout << GetFirstName() << " " << GetMiddleInitial() << ". ";
    std::cout << GetLastName() << " with id: " << GetStudentID();     // this leads to a big were id is not printed legibly
    std::cout << " and gpa: " << GetGpa() << " and is enrolled in: "; // no solution is presented in the text
    std::cout << GetCurrentCourse() << std::endl;
}

int main()
{
    Person p1("Bob", "Joe", 'J', "29/08/2002");

    Student *s1 = nullptr;
    s1 = new Student("Nick", "Cole", 'S', "12/04/2001", 3.65, "C++", "112HAV");
    Student s2("Alex", "Tost", 'A', "03/22/2003", 3.78, "C++", "674HOP");
    Student s3(p1, "721FOE");

    p1.Print();
    s1->Print();
    s2.Print();
    s3.Print();

    std::cout << "There are " << Student::GetNumberStudents() << " students" << std::endl;

    delete s1;

    std::cout << "There are " << Student::GetNumberStudents() << " students" << std::endl;

    return 0;
}