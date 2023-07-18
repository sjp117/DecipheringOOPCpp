#include <iostream>
#include <iomanip>
#include <string>

constexpr int MAX = 5;

class Person
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial = '\0';  // in class initialization
    std::string title;

protected:
    void ModifyTitle(const std::string &);

public:
    Person() = default;
    Person(const std::string &, const std::string &, char, const std::string &);
    virtual ~Person();  // state virtual destructor
    const std::string &GetFirstName() const { return firstName; }
    const std::string &GetLastName() const { return lastName; }
    char GetMiddleInitial() const { return middleInitial; }
    const std::string &GetTitle() const { return title; }
    virtual void Print() const;
    virtual void IsA() const;
    virtual void Greeting(const std::string &) const;
};

// alternate constructor
Person::Person(const std::string &fn, const std::string &ln, char mi, const std::string &t) :
               firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
    // dynamically allocate memory as needed
}

Person::~Person()
{
    // release memory as needed
    std::cout << "Person destructor <" << firstName << " " << lastName << ">" << std::endl;
}

void Person::ModifyTitle(const std::string &newTitle)
{
    title = newTitle;
}

void Person::Print() const
{
    std::cout << title << " " << firstName << " " << middleInitial << ". " << lastName << std::endl;
}

void Person::IsA() const
{
    std::cout << "Person" << std::endl;
}

void Person::Greeting(const std::string &msg) const
{
    std::cout << msg << std::endl;
}

class Student: public Person
{
private:
    float gpa = 0.0; // in-class initialization
    std::string currentCourse;
    const std::string studentID;
    static int numStudents; // static data member

public:
    Student(); // default constructor
    Student(const std::string &, const std::string &, char, const std::string &, float,
            const std::string &, const std::string &);
    Student(const Student &); // copy constructor
    ~Student() override; // virtual destructor
    void EarnedPhD();

    // inline function definitions
    float GetGpa() const { return gpa; }
    const std::string &GetCurrentCourse() const { return currentCourse; }
    const std::string &GetStudentID() const { return studentID; }
    void SetCurrentCourse(const std::string &); // prototype

    // in derived classes and without knowing whether it will be derived again, its better to use
    // override keyword
    void Print() const final override;
    void IsA() const override;
    // we chose not to redefine
    // Person::Greeting(const std::string &) const
    static int GetNumberStudents(); // static member function
};

// define the static data member
int Student::numStudents = 0;

inline void Student::SetCurrentCourse(const std::string &c)
{
    currentCourse = c;
}

// definition for static member function
inline int Student::GetNumberStudents()
{
    return numStudents;
}

Student::Student() : studentID(std::to_string(numStudents + 100) + "Id")
{
    numStudents++;
}

// alternate constructor definition
Student::Student(const std::string &fn, const std::string &ln, char mi, const std::string &t, float avg,
                 const std::string &course, const std::string &id) :
                 Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentID(id)
{
    numStudents++;
}

// copy constructor definition
Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentID(s.studentID)
{
    numStudents++;
}

// destructor definition
Student::~Student()
{
    // release allocated memory as needed
    std::cout << "Student destructor <" << GetFirstName() << " " << GetLastName() << ">" << std::endl;
    numStudents--;
}

void Student::EarnedPhD()
{
    ModifyTitle("Dr.");
}

void Student::Print() const
{
    // need to use access functions as these data members are defined in Person as private
    // Person::Print(); // this seems to be an option but changes the example
    std::cout << GetTitle() << " " << GetFirstName() << " " << GetMiddleInitial() << ", ";
    std::cout << GetLastName() << " with id: " << studentID << " GPA: " << std::setprecision(3);
    std::cout << gpa << " Course: " << currentCourse << std::endl;
}

void Student::IsA() const
{
    std::cout << "Student" << std::endl;
}

int main()
{
    Person *people[MAX] = { }; // initialize with nullptr
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