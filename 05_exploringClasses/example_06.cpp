// Creating conversion constructors

#include <iostream>
#include <cstring> // for demonstration

class Student; // forward declaration of Student class

class Employee
{
private:
    std::string firstName;
    std::string lastName;
    float salary;

public:
    Employee();
    Employee(const std::string &, const std::string &, float);
    explicit Employee(Student &); // conversion constructor
    void Print();
};

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
    float GetGpa(); // access function for private data mbr
    const std::string &GetFirstName();
    const std::string &GetLastName();
};

Employee::Employee() // default constructor
{
    salary = 0.0;
}

// alternate constructor
Employee::Employee(const std::string &fn, const std::string &ln, float money)
{
    firstName = fn;
    lastName = ln;
    salary = money;
}

// conversion constructor definition
Employee::Employee(Student &s)
{
    firstName = s.GetFirstName();
    lastName = s.GetLastName();
    if (s.GetGpa() >= 4.0)
        salary = 75000;
    else if (s.GetGpa() >= 3.0)
        salary = 60000;
    else
        salary = 50000;
}

void Employee::Print()
{
    std::cout << firstName << " " << lastName << " " << salary << std::endl;
}

// definitions for student class

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

float Student::GetGpa()
{
    return gpa;
}

const std::string &Student::GetFirstName()
{
    return firstName;
}

const std::string &Student::GetLastName()
{
    return lastName;
}

int main()
{
    Student s1("Giselle", "LeBrun", 'A', 3.5, "C++");
    Employee e1(s1); // conversion constructor
    e1.Print();
    s1.CleanUp(); // this will delete s1's dynamically allocated members
    return 0;
}