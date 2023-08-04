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
    University();
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

class Course
{
private:
    std::string courseName;
    int count = 0;
    static const int MAX = 25;
    Student *studentBody[MAX] = {};

public:
    Course();
    Course(const std::string &);
    Course(const Course &);
    ~Course();
    void EnrollStudent(Student *);
    const std::string &GetCourseName() const { return courseName; }
    int GetStudentCount() { return count; }
};

Course::Course(const std::string &n) : courseName(n)
{
}

Course::~Course()
{
    for (int i = 0; i < MAX; i++)
    {
        studentBody[i] = nullptr;
    }
}

void Course::EnrollStudent(Student *s)
{

    studentBody[count++] = s;
}

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
    static const int MAX_COURSES = 2;
    int numberOfCourses = 0;
    Course *currentCourses[MAX_COURSES] = {};
    ID studentID; // is composed of a 'part'
    static int numStudents;
    University *univ = nullptr; // associate with univ object

public:
    Student();
    Student(const std::string &, const std::string &, char, const std::string &,
            float, Course *, const std::string &, University *);
    Student(const std::string &, const std::string &, char, const std::string &, // add another constructor with university argument by reference
            float, Course *, const std::string &, University &);
    Student(const Student &);
    ~Student() override;
    const std::string GetCurrentCourse();
    void SetCurrentCourse(Course *);
    void Print() const override;
    void IsA() const override { std::cout << "Student" << std::endl; }
    static int GetNumberStudents() { return numStudents; }
    virtual void Validate();
    bool TakePrerequisites();

    // access function for embedded id object
    const std::string &GetStudentID() const { return studentID.GetID(); }
    const std::string &GetUniversity() const { return univ->GetName(); }
};

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

int Student::numStudents = 0;

inline const std::string Student::GetCurrentCourse()
{
    if (numberOfCourses < 2)
    {
        return currentCourses[0]->GetCourseName();
    }
    else
    {
        const std::string output = currentCourses[0]->GetCourseName() + ", " + currentCourses[1]->GetCourseName();
        return output;
    }
}

inline void Student::SetCurrentCourse(Course *course)
{
    if (numberOfCourses == MAX_COURSES)
    {
        std::cout << "Course limit reached for " << this->GetFirstName() << " " << this->GetMiddleInitial()
                  << ". " << this->GetLastName() << std::endl;
    }
    else
    {
        this->currentCourses[numberOfCourses] = course;
        currentCourses[numberOfCourses]->EnrollStudent(this);
        numberOfCourses++;
    }
}

Student::Student() : studentID(std::to_string(numStudents + 100) + "Id")
{
    numStudents++;
}

Student::Student(const std::string &fn, const std::string &ln, char mi, const std::string &t,
                 float avg, Course *course, const std::string &id, University *univ)
    : Person(fn, ln, mi, t), gpa(avg), studentID(id)
{
    SetCurrentCourse(course);
    this->univ = univ;
    univ->EnrollStudent(this);
    numStudents++;
}

Student::Student(const std::string &fn, const std::string &ln, char mi, const std::string &t,
                 float avg, Course *course, const std::string &id, University &univ)
    : Person(fn, ln, mi, t), gpa(avg), studentID(id)
{
    SetCurrentCourse(course);
    this->univ = &univ; // "Called C++ object pointer is null" warning but compiles and runs
    univ.EnrollStudent(this);
    numStudents++;
}

Student::Student(const Student &s)
    : Person(s), gpa(s.gpa), studentID(s.studentID)
{
    std::copy(s.currentCourses, s.currentCourses + MAX_COURSES, currentCourses);
    this->univ = s.univ;
    univ->EnrollStudent(this);
    numStudents++;
}

Student::~Student()
{
    for (int i = 0; i < MAX_COURSES; i++)
    {
        currentCourses[i] = nullptr;
    }
    numStudents--;
    univ = nullptr;
}

void Student::Print() const
{
    std::cout << GetTitle() << " " << GetFirstName() << " " << GetMiddleInitial() << ". " << GetLastName()
              << " with id: " << studentID.GetID() << " has a gpa of: " << std::setprecision(3) << gpa
              << std::endl;
}

void Student::Validate()
{
    // check constructed student; see if standards are met. If not, throw an exception
    throw std::string("Does not meet prerequisites");
}

bool Student::TakePrerequisites()
{
    return false;
}

int main()
{
    University *u1 = new University("The George Washington University");

    Course *c1 = new Course("C++");

    Student s1("Gabby", "Doone", 'A', "Miss", 3.85, c1, "4225GWU", u1);

    try
    {
        try
        {
            s1.Validate();
        }
        catch (const std::string &err)
        {
            std::cerr << err << std::endl;
            if (!s1.TakePrerequisites())
                throw;
        }
    }
    catch (const std::string &err)
    {
        std::cout << err << std::endl;
        exit(1);
    }

    u1->PrintStudents();
    delete u1;
    delete c1;

    return 0;
}