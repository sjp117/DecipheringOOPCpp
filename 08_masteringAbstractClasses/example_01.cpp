// Abstract classes

#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>

constexpr int MAX = 5;

class LifeForm // abstract class
{
private:
    int lifeExpectancy = 0; // in-class initialization
public:
    LifeForm() = default;
    LifeForm(int life) : lifeExpectancy(life) { }
    virtual ~LifeForm() = default; // virtual destructor is required
    [[nodiscard]] int GetLifeExpectancy() const { return lifeExpectancy; }
    virtual void Print() const = 0;
    virtual std::string IsA() const = 0;
    virtual std::string Speak() const = 0;
};

class Cat : public LifeForm
{
private:
    int numberLivesLeft = 9; // in-class initialization
    std::string name;
    static constexpr int CAT_LIFE = 15; // life expectancy of cat
public:
    Cat() : LifeForm(CAT_LIFE) { } // note prior in-class init
    Cat(int lives) : LifeForm(CAT_LIFE), numberLivesLeft(lives) { }
    Cat(const std::string &);
    // proper destructor provided by default
    const std::string &GetName() const { return name; }
    int GetNumberLivesLeft() const { return numberLivesLeft; }
    void Print() const override; // redefine pure virtual function
    std::string IsA() const override { return "Cat"; }
    std::string Speak() const override { return "Meow!"; }
};

Cat::Cat(const std::string &n) : LifeForm(CAT_LIFE), name(n)
{
    // number of lives is set using in-class initialization
}

void Cat::Print() const
{
    std::cout << "\t" << name << " has " << numberLivesLeft << " lives left" << std::endl;
}

class Person : public LifeForm
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial = '\0';
    std::string title; // Mr., Ms., Mrs., Miss., Dr., etc...
    static constexpr int PERSON_LIFE = 80; // life expectancy of person

protected: // make available to derived classes in their scope
    void ModifyTitle(const std::string &);

public:
    Person(); // must specify constructor
    Person(const std::string &, const std::string &, char, const std::string &);
    Person(const Person &) = default; // copy-constructor redundant, provided automatically
    virtual ~Person() override = default; // virtual destructor redundant, provided automatically
    const std::string &GetFirstName() const { return firstName; }
    const std::string &GetLastName() const { return lastName; }
    char GetMiddleInitial() const { return middleInitial; }
    const std::string &GetTitle() const { return title; };
    virtual void Print() const override; // redefine pure virtual functions
    virtual std::string IsA() const override;
    virtual std::string Speak() const override;
};

Person::Person() : LifeForm(PERSON_LIFE)
{
    // middleInitial has a default value and strings will automatically be empty
}

Person::Person(const std::string &fn, const std::string &ln, char mi, const std::string &t) :
               firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

void Person::ModifyTitle(const std::string &newTitle)
{
    title = newTitle;
}

void Person::Print() const
{
    std::cout << "\t" << title << " " << firstName << " " << middleInitial << ". " << lastName << std::endl;
}

std::string Person::IsA() const
{
    return "Person";
}

std::string Person::Speak() const
{
    return "Hello!";
}

class Student : public Person
{
private:
    float gpa = 0.0;
    std::string currentCourse = "NA";
    const std::string studentID; // constant data member

protected:
    static int numStudents;      // status data member

public: // public members are accessible from any scope
    // member function prototypes
    Student(); // default constructor needs specification
    Student(const std::string &, const std::string &, char, const std::string &, float, const std::string &, const std::string &);
    Student(const Student &);
    virtual ~Student() override; // destructor
    void EarnedPhD(); // public interface to inherited protected member

    // inline function definitions
    float GetGpa() const { return gpa; } // access function for private data mbr
    const std::string &GetCurrentCourse() const { return currentCourse; }
    const std::string &GetStudentID() const { return studentID; }
    void SetCurrentCourse(const std::string &);
    static int GetNumberStudents(); // static member function

    // redefine virtual functions
    void Print() const override final;
    virtual std::string IsA() const override;
};

int Student::numStudents = 0;

inline void Student::SetCurrentCourse(const std::string &course)
{
    currentCourse = course;
}

inline int Student::GetNumberStudents()
{
    return numStudents;
}

// default constructor
Student::Student() : studentID(std::to_string(numStudents + 100) + "Id")
{
    numStudents++;
}

// alternate constructor
Student::Student(const std::string &fn, const std::string &ln, char mi, const std::string &t,
                float avg, const std::string &course, const std::string &id) :
                Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentID(id)
{
    numStudents++;
}

// Copy constructor definition
Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentID(s.studentID)
{
    numStudents++;
}

// destructor definition
Student::~Student()
{
    numStudents--;
}

void Student::EarnedPhD()
{
    ModifyTitle("Dr.");
}

void Student::Print() const
{
    // private members of person are not accessible within the scope of Student, so we use access functions
    std::cout << "\t" << GetTitle() << " " << GetFirstName() << " " << GetMiddleInitial() << ". " << GetLastName();
    std::cout << " id: " << studentID << "\n\twithgpa: " << std::setprecision(3) << gpa;
    std::cout << " enrolled in: " << currentCourse << std::endl;
}

std::string Student::IsA() const
{
    return "Student";
}

int main()
{
    // Since LifeForms cannot be instantiated we create an array of pointers to LifeForms
    LifeForm *entity[MAX] = { }; // initialize with null pointers
    entity[0] = new Person("Joy", "Lin", 'M', "Ms.");
    entity[1] = new Student("Renee", "Alexander", 'Z', "Dr.", 3.95, "C++", "21-MIT"); 
    entity[2] = new Student("Gabby", "Doone", 'A', "Ms.", 3.95, "C++", "18-GWU");
    entity[3] = new Cat("Katje");
    entity[4] = new Person("Giselle", "LeBrun", 'R', "Miss");

    // use range for-loop to process each element of entity
    for (LifeForm *item : entity) // each item is a LifeForm pointer to each element in entity
    {
        std::cout << item->Speak();
        std::cout << " I am a " << item->IsA() << std::endl;
        item->Print();
        std::cout << "\tHas a life expectancy of: " << item->GetLifeExpectancy() << "\n";
    }

    for (LifeForm *item : entity)
    {
        delete item;
        item = nullptr;
    }
    return 0;
}