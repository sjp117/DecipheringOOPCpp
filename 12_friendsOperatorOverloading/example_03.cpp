// error with the use of strcpy()

#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

class Person
{
private:
    std::string firstName, lastName;
    char middleInitial = '\0';
    char *title = nullptr; // using pointer to demonstrate deep assigment

protected:
    void ModifyTitle(const std::string &); // converts to char *

public:
    Person() = default;
    Person(const std::string &, const std::string &, char, const char *);
    Person(const Person &);
    virtual ~Person();
    const std::string &GetFirstName() const { return firstName; }
    const std::string &GetLastName() const { return lastName; }
    char GetMiddleInitial() const { return middleInitial; }
    const char *GetTitle() const { return title; }
    virtual void Print() const;
    virtual void IsA() const;

    // overload operator functions
    Person &operator=(const Person &);      // overload assign
    bool operator==(const Person &);        // overloaded comparison
    Person &operator+(const std::string &); // overloaded plus
    friend Person &operator+(const std::string &, Person &);
};

// overload assignment operator
Person &Person::operator=(const Person &p)
{
    if (this != &p) // make sure not assigning to itself
    {
        // delete any previously dynamically allocated data from the destination object
        delete[] title;

        // Also, remember to reallocate memory for any data members that are pointers

        // Then, copy from source to destination object for each data member
        firstName = p.firstName;
        lastName = p.lastName;
        middleInitial = p.middleInitial;

        // Note: a pointer is used for title to demo the necessary steps to implement a deep assignment.
        // Otherwise, we would implement title with string.
        title = new char[std::strlen(p.title) + 1];
        std::strcpy(title, p.title);
    }
    return *this; // allow for cascaded assignments
}

// overload comparison operator
bool Person::operator==(const Person &p)
{
    // if the objects are the same, or if the contents are equal, return true, else, false.
    if (this == &p)
    {
        return true;
    }
    else if ((!firstName.compare(p.firstName)) &&
             (!lastName.compare(p.lastName)) &&
             (!strcmp(title, p.title)) &&
             (middleInitial == p.middleInitial))
        return true;
    else
        return false;
}

// overload operator + (member function)
Person &Person::operator+(const std::string &t)
{
    ModifyTitle(t);
    return *this;
}

// overload + operator (not a member function)
Person &operator+(const std::string &t, Person &p)
{
    p.ModifyTitle(t);
    return p;
}

int main()
{
    Person p1;
    Person p2("Gabby", "Doone", 'A', "Miss");
    Person p3("Renee", "Alexander", 'Z', "Dr.");

    p1.Print();
    p2.Print();
    p3.Print();

    p1 = p2; // invoke overloaded assignment operator
    p1.Print();
    p2 = "Ms." + p2; // invoke overloaded + operator, then invoke overloaded = operator
    p2.Print();
    p1 = p2 = p3; // overloaded = can handle cascade =
    p2.Print();
    p1.Print();

    if (p2 == p2)
        std::cout << "Same people" << std::endl;
    if (p1 == p3)
        std::cout << "Same people" << std::endl;

    return 0;
}