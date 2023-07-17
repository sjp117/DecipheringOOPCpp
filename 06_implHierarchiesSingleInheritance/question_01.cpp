// Using your Chapter 5, Exploring Classes in Detail, solution, create a C++ program to build an
// inheritance hierarchy, generalizing Person as a base class from the derived class of Student.

#include <iostream>
#include <cstring>

class Person
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial = '\0';
    std::string dob = "00/00/0000";

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

// Person::Person() : middleInitial(), dob()
// {
// }

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

class Student : public Person
{
private:
    float gpa = 0.0;
    std::string currentCourse = "NA";
    const char *studentID;  // constant data member
    static int numStudents; // status data member

public: // public members are accessible from any scope
    // member function prototypes
    Student(); // default constructor
    Student(const std::string &, const std::string &, char, const std::string &, float, const std::string &, const char *);
    Student(const Student &);
    Student(const Person &, const char *); // copy constructor prototype
    ~Student();                            // destructor
    void Print() const;

    // inline function definitions
    // const std::string &GetFirstName() const { return firstName; }
    // const std::string &GetLastName() const { return lastName; }
    // char GetMiddleInitial() const { return middleInitial; }
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
Student::Student() : studentID(nullptr)
{
    numStudents++;
}

Student::Student(const std::string &fn, const std::string &ln, char mi, const std::string &dob, float avg, const std::string &course, const char *id) : gpa(avg), currentCourse(course)
{
    char *temp = new char[strlen(id) + 1];
    // strcpy(studentID, id); // studentID cannot be an l-value
    studentID = temp; // but temp can be an l-value
    numStudents++;
}

Student::Student(const Student &s) : gpa(s.gpa), currentCourse(s.currentCourse)
{
    char *temp = new char[strlen(s.studentID) + 1];
    // strcpy(studentID, id); // studentID cannot be an l-value
    studentID = temp; // but temp can be an l-value
    numStudents++;
}

Student::Student(const Person &p, const char *id)
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
    std::cout << GetLastName() << " with id: " << GetStudentID();     // <- this leads to a bug were id is not printed legibly
    std::cout << " and gpa: " << GetGpa() << " and is enrolled in: "; //    no solution is presented in the text, but I leave it
    std::cout << GetCurrentCourse() << std::endl;                     //    as an exercise for pointer destruction
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

    s3.SetCurrentCourse("C++");
    s3.Print();

    std::cout << "There are " << Student::GetNumberStudents() << " students" << std::endl;

    delete s1;

    std::cout << "There are " << Student::GetNumberStudents() << " students" << std::endl;

    return 0;
}