// Applying destructor basics and proper usage

#include <iostream>
#include <cstring> // for demonstration

class University
{
private:
    char *name;
    int numStudents;

public:
    // member function prototypes
    University(); // default constructor
    University(const char *, int);
    University(const University &); // copy constructor
    ~University();                  // destructor prototype
    void Print();
};

University::University() // default constructor
{
    name = nullptr;
    numStudents = 0;
}

University::University(const char *n, int num)
{
    name = new char[strlen(n) + 1];
    strcpy(name, n);
    numStudents = num;
}

University::University(const University &u) // copy const
{
    name = new char[strlen(u.name) + 1];
    strcpy(name, u.name);
    numStudents = u.numStudents;
}

University::~University() // destructor definition
{
    delete[] name;
    std::cout << "Destructor called " << this << std::endl;
}

void University::Print()
{
    std::cout << "University: " << name << " Enrollment: " << numStudents << std::endl;
}

int main()
{
    University u1("Temple University", 39500);
    University *u2 = new University("Boston U", 32500);
    u1.Print();
    u2->Print();
    delete u2; // destructor will be called before delete() and destructor for u1 will be called
               // before program completes
    return 0;
}