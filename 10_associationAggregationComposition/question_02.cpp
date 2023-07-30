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

    // access function for embedded id object
    const std::string &GetStudentID() const { return studentID.GetID(); }
    const std::string &GetUniversity() const { return univ->GetName(); }
};

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

    Course *c1 = new Course("Psychology");
    Course *c2 = new Course("C++");
    Course *c3 = new Course("Python");

    Student s1("Gabby", "Doone", 'A', "Miss", 3.85, c1, "4225GWU", u1);
    Student s2("Giselle", "LeBrun", 'A', "Ms.", 3.45, c2, "1227GWU", &u2);
    Student s3("Eve", "Kendall", 'B', "Ms.", 3.71, c3, "5542GWU", u1);

    std::cout << s1.GetFirstName() << " " << s1.GetLastName() << " attends " << s1.GetUniversity()
              << " takes: " << s1.GetCurrentCourse() << std::endl;
    std::cout << s2.GetFirstName() << " " << s2.GetLastName() << " attends " << s2.GetUniversity()
              << " takes: " << s2.GetCurrentCourse() << std::endl;
    std::cout << s3.GetFirstName() << " " << s3.GetLastName() << " attends " << s3.GetUniversity()
              << " takes: " << s3.GetCurrentCourse() << std::endl;

    s1.SetCurrentCourse(c3);
    std::cout << s1.GetFirstName() << " " << s1.GetLastName() << " attends " << s1.GetUniversity()
              << " takes: " << s1.GetCurrentCourse() << std::endl;

    s1.SetCurrentCourse(c2);

    std::cout << "# of students taking " << c1->GetCourseName() << " is: " << c1->GetStudentCount() << std::endl;
    std::cout << "# of students taking " << c2->GetCourseName() << " is: " << c2->GetStudentCount() << std::endl;
    std::cout << "# of students taking " << c3->GetCourseName() << " is: " << c3->GetStudentCount() << std::endl;

    u1->PrintStudents();
    u2.PrintStudents();

    delete u1;
    delete c1;
    delete c2;
    delete c3;

    return 0;
}