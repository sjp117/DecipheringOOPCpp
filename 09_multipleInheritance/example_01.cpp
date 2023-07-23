// Understanding multiple inheritance mechanics

#include <iostream>

class Person
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial;
    std::string title;

protected:
    void ModifyTitle(const std::string &);

public:
    Person() = default;
    Person(const std::string &, const std::string &, char, const std::string &);
    Person(const Person &) = delete; // prohibit copies
    virtual ~Person();
    const std::string &GetFirstName() const { return firstName; }
    const std::string &GetLastName() const { return lastName; }
    const char &GetMiddleInitial() const { return middleInitial; }
    const std::string &GetTitle() const { return title; }
};

Person::Person(const std::string &fn, const std::string &ln, char mi, const std::string &t)
    : firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

Person::~Person()
{
    std::cout << "Person destructor <" << firstName << " " << lastName << ">" << std::endl;
}

void Person::ModifyTitle(const std::string &newTitle)
{
    title = newTitle;
}

class BillableEntity
{
private:
    float invoiceAmt = 0.0;

public:
    BillableEntity() = default;
    BillableEntity(float amt) : invoiceAmt(amt) {}
    BillableEntity(const BillableEntity &) = delete;
    virtual ~BillableEntity();
    void Pay(float amt) { invoiceAmt -= amt; }
    float GetBalance() const { return invoiceAmt; }
    void Balance() const;
};

BillableEntity::~BillableEntity()
{
    std::cout << "BillableEntity destructor" << std::endl;
}

void BillableEntity::Balance() const
{
    if (invoiceAmt)
    {
        std::cout << "Owned amount: $" << invoiceAmt << std::endl;
    }
    else
    {
        std::cout << "Credit: $" << 0.0 - invoiceAmt << std::endl;
    }
}

class Student : public Person, public BillableEntity
{
private:
    float gpa = 0.0;
    std::string currentCourse;
    const std::string studentID;
    static int numStudents;

public:
    Student();
    Student(const std::string &, const std::string &, char, const std::string &, float,
            float, const std::string &, const std::string &);
    Student(const Student &) = delete;
    ~Student() override;
    void Print() const;
    void EarnPhD();
    float GetGpa() const { return gpa; }
    const std::string &GetCurrentCourse() const { return currentCourse; }
    const std::string &GetStudentID() const { return studentID; }
    void SetCurrentCourse(const std::string &c) { currentCourse = c; }
    static int GetNumberStudents() { return numStudents; }
};

// definition for static member
int Student::numStudents = 0;

Student::Student() : studentID(std::to_string(numStudents + 100) + "Id")
{
    numStudents++;
}

Student::Student(const std::string &fn, const std::string &ln, char mi, const std::string &t, float amt,
                 float avg, const std::string &course, const std::string &id)
    : Person(fn, ln, mi, t), BillableEntity(amt), gpa(avg), currentCourse(course), studentID(id)
{
    numStudents++;
}

Student::~Student()
{
    numStudents--;
    std::cout << "Student destructor <" << GetFirstName() << " " << GetLastName() << ">" << std::endl;
}

void Student::Print() const
{
    std::cout << GetTitle() << " " << GetFirstName() << " " << GetMiddleInitial() << ". " << GetLastName()
              << " with id: " << studentID << " has a gpa of: " << gpa << " and course: " << currentCourse
              << " with balance: $" << GetBalance() << std::endl;
}

void Student::EarnPhD()
{
    ModifyTitle("Dr.");
}

int main()
{
    float tuition1 = 1000.00, tuition2 = 2000.00;
    Student s1("Gabby", "Doone", 'A', "Ms.", tuition1, 3.9, "C++", "178GWU");
    Student s2("Zack", "Moon", 'R', "Dr.", tuition2, 3.9, "C++", "272MIT");

    // public members of Person, BillableEntity, and Student are accessible from any scope
    s1.Print();
    s2.Print();
    std::cout << s1.GetFirstName() << " paid $500.00" << std::endl;
    s1.Pay(500.00);
    std::cout << s2.GetFirstName() << " paid $750.00" << std::endl;
    s2.Pay(750.00);
    std::cout << s1.GetFirstName() << ": " << std::flush;
    s1.Balance();
    std::cout << s2.GetFirstName() << ": " << std::flush;
    s2.Balance();
    return 0;
}