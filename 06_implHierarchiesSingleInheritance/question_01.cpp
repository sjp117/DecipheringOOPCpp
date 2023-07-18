// Using your Chapter 5, Exploring Classes in Detail, solution, create a C++ program to build an
// inheritance hierarchy, generalizing Person as a base class from the derived class of Student.

#include <iostream>
#include <iomanip>
#include <string>

class Person
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial = '\0';
    std::string title; // Mr., Ms., Mrs., Miss., Dr., etc...
    std::string dob;

protected: // make available to derived classes in their scope
    void ModifyTitle(const std::string &);

public:
    Person();
    Person(const std::string &, const std::string &, char, const std::string &, const std::string &);
    Person(const Person &);
    const std::string &GetFirstName() const { return firstName; }
    const std::string &GetLastName() const { return lastName; }
    char GetMiddleInitial() const { return middleInitial; }
    const std::string &GetDateOfBirth() const { return dob; }
    const std::string &GetTitle() const { return title; };
    void Print() const;
};

void Person::ModifyTitle(const std::string &newTitle)
{
    title = newTitle;
}

Person::Person() : middleInitial('\0'), dob("00/00/0000")
{
}

Person::Person(const std::string &fn, const std::string &ln, char mi, const std::string &t, const std::string &bday) : firstName(fn), lastName(ln), middleInitial(mi), dob(bday), title(t)
{
}

Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial), title(p.title), dob(p.dob)
{
}

void Person::Print() const
{
    std::cout << GetTitle() << " " << GetFirstName() << " " << GetMiddleInitial() << ". " << GetLastName() << " was born in " << GetDateOfBirth() << std::endl;
}

class Student : public Person
{
private:
    float gpa = 0.0;
    std::string currentCourse = "NA";
    const std::string studentID; // constant data member
    static int numStudents;      // status data member

public: // public members are accessible from any scope
    // member function prototypes
    Student(); // default constructor
    Student(const std::string &, const std::string &, char, const std::string &, const std::string &, float, const std::string &, const std::string &);
    Student(const Student &);
    ~Student(); // destructor
    void Print() const;
    void EarnedPhD(); // public interface to inherited protected member

    // inline function definitions
    float GetGpa() const { return gpa; } // access function for private data mbr
    const std::string &GetCurrentCourse() const { return currentCourse; }
    const std::string &GetStudentID() const { return studentID; }
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

// default constructor uses in-class initial for gpa, while current course is default constructed
Student::Student() : studentID(std::to_string(numStudents + 100) + "ID")
{
    // dynamically allocate memory for pointer members if present (not in this case)
    numStudents++; // increment static counter
}

Student::Student(const std::string &fn, const std::string &ln, char mi, const std::string &t,
                 const std::string &bday, float avg, const std::string &course, const std::string &id)
    : Person(fn, ln, mi, t, bday), gpa(avg), currentCourse(course), studentID(id)
{
    numStudents++;
}

Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentID(s.studentID)
{
    numStudents++;
}

Student::~Student() // destructor definition
{
    numStudents--; // decrement static counter
    std::cout << "Destructor called " << this << std::endl;
}

void Student::Print() const
{
    // private members of person are not accessible within the scope of Student, so we use access functions
    std::cout << GetTitle() << " " << GetFirstName() << " " << GetMiddleInitial() << ". ";
    std::cout << GetLastName() << " with id: " << studentID << " gpa: " << std::setprecision(2) << gpa;
    std::cout << " course: " << currentCourse << std::endl;
}

void Student::EarnedPhD()
{
    // protected members defined by the base class are accessible within the scope of the derived class.
    // EarnedPhD() provides a public interface to this functionality for derived class instances.
    ModifyTitle("Dr.");
}

int main()
{
    Person p1("Jo", "Li", 'U', "Ms.", "03/23/1998");
    Student s1("Nick", "Cole", 'S', "Mr.", "12/04/2001", 3.65, "C++", "112HAV");

    Student *s2 = nullptr;
    s2 = new Student("Alex", "Tost", 'A', "Ms.", "03/22/2003", 3.78, "NA", "674HOP");

    p1.Print();
    s1.Print();
    s2->Print();

    std::cout << "There are " << Student::GetNumberStudents() << " students" << std::endl;

    s2->SetCurrentCourse("C++");
    s2->Print();

    s1.EarnedPhD();
    s1.Print();

    delete s2;

    std::cout << "There are " << Student::GetNumberStudents() << " students" << std::endl;

    return 0;
}