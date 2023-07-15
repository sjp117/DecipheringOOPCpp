// Using access labels and access regions

#include <iostream>

class University
{
private:
    std::string name{"None"}; // in-class initialization when constructor gives no value
    int numStudents{0};

public:
    // member function prototypes
    University() = default; // default constructor
    University(const std::string &, int);
    void CleanUp();
    void Print();
};

University::University()
{
    // numStudents = 0;
}

// overload member initialization function
University::University(const std::string &n, int num)
{
    name = n;
    numStudents = num;
}

void University::Print()
{
    std::cout << "University: " << name;
    std::cout << " Enrollment: " << numStudents << std::endl;
}

void University::CleanUp()
{
    // deallocate previously allocated memory
}

int main()
{
    University u1; // implicit call to default constructor

    // alternate constructor instantiation
    University u2("University of Delaware", 23800);
    University u3("Temple University", 20500);
    u1.Print();
    u2.Print();
    u3.Print();
    u1.CleanUp();
    u2.CleanUp();
    u3.CleanUp();
    return 0;
}