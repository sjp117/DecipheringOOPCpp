// Implementing association

#include <iostream>
#include <iomanip>
#include <string>

class Student; // forward declaration

class University
{
private:
    std::string name;
    static constexpr int MAX = 25;
    Student *studentBody[MAX] = {}; // allocate memory to the MAX amount of students
    int currentNumStudents = 0;     // in-class initialization

public:
    University() = default;
    University(const std::string &);
    University(const University &) = delete; // no copies
    ~University();
    void EnrollStudent(Student *);
    const std::string &GetName() const { return name; }
    void PrintStudents() const;
};

// instead of allocating memory in-class, we could get the constructor to allocate instead (option)

University::University(const std::string &n) : name(n)
{
}

University::~University()
{
    // destructor does not automatically delete the student allocated memory
    // deallocation must be done manually
    for (int i = 0; i < MAX; i++)
    {
        studentBody[i] = nullptr;
    }
}

void University::EnrollStudent(Student *s)
{
    studentBody[currentNumStudents++] = s;
}

class ID final // contained 'part'
{
private:
    std::string idNumber;

public:
    ID() = default;
    ID(const std::string &id) : idNumber(id) {}
    const std::string &GetID() const { return idNumber; }
};

class Person
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial = '\0';
    std::string title;

protected:
    void ModifyTitle(const std::string &);

public:
    Person() = default;
    Person(const std::string &, const std::string &, char, const std::string &);
    virtual ~Person() = default;
    // Getter functions
    const std::string &GetFirstName() const { return firstName; }
    const std::string &GetLastName() const { return lastName; }
    char GetMiddleInitial() const { return middleInitial; }
    const std::string &GetTitle() const { return title; }
    // virtual functions
    virtual void Print() const;
    virtual void IsA() const;
    virtual void Greeting(const std::string &) const;
};

Person::Person(const std::string &fn, const std::string &ln, char mi, const std::string &t)
    : firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

void Person::ModifyTitle(const std::string &newTitle)
{
    title = newTitle;
}

void Person::Print() const
{
    std::cout << title << " " << firstName << " ";
    std::cout << middleInitial << ". " << lastName << std::endl;
}

void Person::IsA() const
{
    std::cout << "Person" << std::endl;
}

void Person::Greeting(const std::string &msg) const
{
    std::cout << msg << std::endl;
}

class Student : public Person
{
private:
    float gpa = 0.0;
    std::string currentCourse;
    ID studentID; // is composed of a 'part'
    static int numStudents;
    University *univ = nullptr; // associate with univ object

public:
    Student();
    Student(const std::string &, const std::string &, char, const std::string &,
            float, const std::string &, const std::string &, University *);
    Student(const std::string &, const std::string &, char, const std::string &, // add another constructor with university argument by reference
            float, const std::string &, const std::string &, University &);
    Student(const Student &);
    ~Student() override;
    const std::string &GetCurrentCourse() const { return currentCourse; }
    void SetCurrentCourse(const std::string &);
    void Print() const override;
    void IsA() const override { std::cout << "Student" << std::endl; }
    static int GetNumberStudents() { return numStudents; }

    // access function for embedded id object
    const std::string &GetStudentID() const { return studentID.GetID(); }
    const std::string &GetUniversity() const { return univ->GetName(); }
};

int Student::numStudents = 0;

inline void Student::SetCurrentCourse(const std::string &course)
{
    currentCourse = course;
}

Student::Student() : studentID(std::to_string(numStudents + 100) + "Id")
{
    numStudents++;
}

Student::Student(const std::string &fn, const std::string &ln, char mi, const std::string &t,
                 float avg, const std::string &course, const std::string &id, University *univ)
    : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentID(id)
{
    this->univ = univ;
    univ->EnrollStudent(this);
    numStudents++;
}

Student::Student(const std::string &fn, const std::string &ln, char mi, const std::string &t,
                 float avg, const std::string &course, const std::string &id, University &univ)
    : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentID(id)
{
    *this->univ = univ; // "Called C++ object pointer is null" warning but compiles and runs
    univ.EnrollStudent(this);
    numStudents++;
}

Student::Student(const Student &s)
    : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentID(s.studentID)
{
    this->univ = s.univ;
    univ->EnrollStudent(this);
    numStudents++;
}

Student::~Student()
{
    numStudents--;
    // embedded studentID object will also be destructed
    // Student does not delete university, thus must be specified
    univ = nullptr;
}

void Student::Print() const
{
    std::cout << GetTitle() << " " << GetFirstName() << " " << GetMiddleInitial() << ". " << GetLastName()
              << " with id: " << studentID.GetID() << " has a gpa of: " << std::setprecision(3) << gpa
              << " and course: " << currentCourse << std::endl;
}

void University::PrintStudents() const
{
    std::cout << name << " has the following students:" << std::endl;

    // not ideal/proper way of looping
    for (int i = 0; i < currentNumStudents; i++)
    {
        std::cout << "\t" << studentBody[i]->GetFirstName()
                  << " " << studentBody[i]->GetLastName() << std::endl;
    }
}

int main()
{
    University *u1 = nullptr;
    u1 = new University("The George Washington University");
    University u2("Toronto University");

    Student s1("Gabby", "Doone", 'A', "Miss", 3.85, "C++", "4225GWU", u1);
    Student s2("Giselle", "LeBrun", 'A', "Ms.", 3.45, "C++", "1227GWU", &u2);
    Student s3("Eve", "Kendall", 'B', "Ms.", 3.71, "C++", "5542GWU", u1);

    std::cout << s1.GetFirstName() << " " << s1.GetLastName() << " attends " << s1.GetUniversity() << std::endl;
    std::cout << s2.GetFirstName() << " " << s2.GetLastName() << " attends " << s2.GetUniversity() << std::endl;
    std::cout << s3.GetFirstName() << " " << s3.GetLastName() << " attends " << s3.GetUniversity() << std::endl;

    u1->PrintStudents();
    u2.PrintStudents();

    delete u1;

    return 0;
}