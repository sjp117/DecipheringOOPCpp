// Understanding class and member function basics

#include <iostream>
#include <iomanip>

struct student
{
    std::string name;
    float gpa;

    // function prototypes
    void Initialize(std::string, float);
    void Print();
};

class University
{
public:
    std::string name;
    int numStudents;

    // function prototypes
    void Initialize(std::string, int);
    void Print();
};

// member function declarations
void student::Initialize(std::string n, float avg)
{
    name = n; // simple asignment
    gpa = avg;
}

void student::Print()
{
    std::cout << name << " GPA: " << std::fixed << std::setprecision(1) << gpa << std::endl;
}

void University::Initialize(std::string n, int num)
{
    name = n;
    numStudents = num;
}

void University::Print()
{
    std::cout << name << " Enrollment: " << numStudents << std::endl;
}

int main()
{
    student s1; // initialize student struct instance
    s1.Initialize("Gabby Doone", 4.0);
    s1.Print();

    University u1; // instantiate a University class
    u1.Initialize("GWU", 25600);
    u1.Print();

    University *u2;        // pointer declaration
    u2 = new University(); // instantiate with new()
    u2->Initialize("UMD", 40500);
    u2->Print();
    delete u2;

    return 0;
}