#include <iostream>
#include <iomanip>
#include <string>

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

class Student : public Person // 'whole' object
{
private:
    float gpa = 0.0;
    std::string currentCourse;
    ID studentID; // is composed of a 'part'
    static int numStudents;

public:
    Student();
    Student(const std::string &, const std::string &, char, const std::string &,
            float, const std::string &, const std::string &);
    Student(const Student &);
    ~Student() override;
    // member functions
    void EarnPhD() { ModifyTitle("Dr."); }
    float GetGpa() const { return gpa; }
    const std::string &GetCurrentCourse() const { return currentCourse; }
    void SetCurrentCourse(const std::string &);
    void Print() const override;
    void IsA() const override { std::cout << "Student" << std::endl; }
    static int GetNumberStudents() { return numStudents; }

    // access function for embedded id object
    const std::string &GetStudentID() const;
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
                 float avg, const std::string &course, const std::string &id)
    : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentID(id)
{
    numStudents++;
}

Student::Student(const Student &s)
    : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentID(s.studentID)
{
    numStudents++;
}

Student::~Student()
{
    numStudents--;
    // embedded studentID object will also be destructed
}

void Student::Print() const
{
    std::cout << GetTitle() << " " << GetFirstName() << " " << GetMiddleInitial() << ". " << GetLastName()
              << " with id: " << studentID.GetID() << " has a gpa of: " << std::setprecision(3) << gpa
              << " and course: " << currentCourse << std::endl;
}

const std::string &Student::GetStudentID() const
{
    return studentID.GetID();
}

int main()
{
    Student s1("Cyrus", "Bond", 'I', "Mr.", 3.65, "C++", "6996CU");
    Student s2("Anne", "Brennan", 'M', "Ms.", 3.95, "C++", "909EU");
    std::cout << s1.GetFirstName() << " " << s1.GetLastName() << " has id: " << s1.GetStudentID() << std::endl;
    std::cout << s2.GetFirstName() << " " << s2.GetLastName() << " has id: " << s2.GetStudentID() << std::endl;
    return 0;
}