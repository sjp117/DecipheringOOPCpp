#include <iostream>
#include <string>
#include <iomanip>

class Student; // forward declaration

class ID
{
private:
    std::string idNumber;
    Student *student = nullptr;

public:
    ID() = default;
    ID(const std::string &id) : idNumber(id) {}
    const std::string &GetID() const { return idNumber; }

    void SetStudent(Student *);
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
    ID studentID;
    static int numStudents;

public:
    Student();
    Student(const std::string &, const std::string &, char, const std::string &,
            float, const std::string &, const std::string &);
    Student(const Student &);
    ~Student() override;
    const std::string GetCurrentCourse() { return currentCourse; };
    void SetCurrentCourse(std::string &);
    void Print() const override;
    void IsA() const override { std::cout << "Student" << std::endl; }
    static int GetNumberStudents() { return numStudents; }

    // access function for embedded id object
    const std::string &GetStudentID() const { return studentID.GetID(); }

    // only the following member function of ID is a friend function of student
    friend void ID::SetStudent(Student *);
};

int Student::numStudents = 0;

inline void Student::SetCurrentCourse(std::string &course)
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
}

void Student::Print() const
{
    std::cout << GetTitle() << " " << GetFirstName() << " " << GetMiddleInitial() << ". " << GetLastName()
              << " with id: " << studentID.GetID() << " has a gpa of: " << std::setprecision(3) << gpa
              << std::endl;
}

int main()
{
    const int MAX = 5;

    Person *people[MAX] = {}; // initialize with nullptr
    
    people[0] = new Person("Juliet", "Martinez", 'M', "Ms.");
    people[1] = new Student("Hana", "Sato", 'U', "Dr.", 3.8, "C++", "178PSU");
    people[2] = new Student("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU");
    people[3] = new Person("Giselle", "LeBran", 'R', "Miss");
    people[4] = new Person("Linus", "Van Pelt", 'S', "Mr.");

    // we will soon see a more safer and modern way of looping using range (ch 8)
    for (int i = 0; i < MAX; i++)
    {
        people[i]->IsA();
        std::cout << "  ";
        people[i]->Print();
    }
    for (int i = 0; i < MAX; i++)
    {
        delete people[i]; // engage virtual destructor sequence
    }
    return 0;
}