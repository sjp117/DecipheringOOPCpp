// Usage of member initialization list to select a base class constructor

#include <iostream>
#include <iomanip>

class Person
{
private:
    // data members
    std::string firstName;
    std::string lastName;
    char middleInitial = '\0'; // in-class initialization
    std::string title;         // Mr., Ms., Mrs., Miss., Dr., etc...

protected: // make available to derived classes in their scope
    void ModifyTitle(const std::string &);

public:
    Person() = default; // default constructor
    Person(const std::string &, const std::string &, char, const std::string &);
    // copy constructors and destructors are provided by default (automatically); so omitted

    // inline function definitions
    const std::string &GetFirstName() const { return firstName; }
    const std::string &GetLastName() const { return lastName; }
    const std::string &GetTitle() const { return title; }
    char GetMiddleInitial() const { return middleInitial; }
};

// non-line member function definitions for Person

// alternate constructor
Person::Person(const std::string &fn, const std::string &ln, char mi,
               const std::string &t) : firstName(fn), lastName(ln), middleInitial(mi), title(t)
{ // dynamically allocate memory as needed (not in this case)
}

// hypothetical copy constructor if we were to write it instead of using default
// Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName),
//                                   middleInitial(p.middleInitial), title(p.title)
// { // deep-copy any pointer data members as needed
// }

void Person::ModifyTitle(const std::string &newTitle)
{
    title = newTitle;
}

class Student : public Person
{
private:
    // data members
    float gpa = 0.0; // in-class initialization
    std::string currentCourse;
    const std::string studentID; // student ID is not modifiable (after initial assignment?)
    static int numStudents;      // static data member occurs outside of the class definition
public:
    // member function prototypes
    Student(); // we will provide default constructor
    Student(const std::string &, const std::string &, char, const std::string &, float,
            const std::string &, const std::string &);
    Student(const Student &); // copy constructor
    ~Student();               // we will provide destructor
    void Print() const;
    void EarnedPhD(); // public interface to inherited protected member

    // inline function definitions
    float GetGpa() const { return gpa; }
    const std::string &GetCurrentCourse() const { return currentCourse; }
    const std::string &GetStudentID() const { return studentID; }

    // prototypes
    void SetCurrentCourse(const std::string &);
    static int GetNumberStudents(); // static member function
};

// definitions for static data members
int Student::numStudents = 0;

inline void Student::SetCurrentCourse(const std::string &c)
{
    currentCourse = c;
}

// definition for static number function (also inline)
inline int Student::GetNumberStudents()
{
    return numStudents;
}

// default constructor uses in-class initial for gpa, while current course is default constructed
Student::Student() : studentID(std::to_string(numStudents + 100) + "ID")
{
    // dynamically allocate memory for pointer members if present (not in this case)
    numStudents++; // increment static counter
}

// alternate constructor
Student::Student(const std::string &fn, const std::string &ln, char mi,
                 const std::string &t, float avg, const std::string &course,
                 const std::string &id) : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentID(id)
{
    // dynamically allocate memory for pointer members if present (not in this case)
    numStudents++; // increment static counter
}

// copy constructor
Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentID(s.studentID)
{
    // dynamically allocate memory for pointer members if present (not in this case)
    numStudents++; // increment static counter
}

// destructor definition
Student::~Student()
{
    // deallocate memory for pointer members when present
    numStudents--; // decrement static counter
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
    Student s1("Jo", "Li", 'U', "Ms.", 3.8, "C++", "178PSU");
    // public members of Person and Student are accessible outside of their respective classes
    s1.Print();
    s1.SetCurrentCourse("Doctoral Thesis");
    s1.EarnedPhD();
    s1.Print();
    std::cout << "Total number of students: " << Student::GetNumberStudents() << std::endl;
    return 0;
}