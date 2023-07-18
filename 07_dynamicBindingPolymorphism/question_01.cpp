// Using your Chapter 5, Exploring Classes in Detail, solution, create a C++ program to build an
// inheritance hierarchy, generalizing Person as a base class from the derived class of Student.

#include <iostream>
#include <iomanip>
#include <string>

class Person
{
private:
    std::string firstName;
    std::string lastName;
    char middleInitial = '\0';
    std::string title; // Mr., Ms., Mrs., Miss., Dr., etc...
    std::string dob;

protected: // make available to derived classes in their scope
    void ModifyTitle(const std::string &);

public:
    Person() = default;
    Person(const std::string &, const std::string &, char, const std::string &, const std::string &);
    Person(const Person &);
    virtual ~Person(); // virtual destructor
    const std::string &GetFirstName() const { return firstName; }
    const std::string &GetLastName() const { return lastName; }
    char GetMiddleInitial() const { return middleInitial; }
    const std::string &GetDateOfBirth() const { return dob; }
    const std::string &GetTitle() const { return title; };
    virtual void Print() const;
    virtual void IsA() const;
};

void Person::ModifyTitle(const std::string &newTitle)
{
    title = newTitle;
}

Person::Person(const std::string &fn, const std::string &ln, char mi, const std::string &t, const std::string &bday) : firstName(fn), lastName(ln), middleInitial(mi), dob(bday), title(t)
{
}

Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial), title(p.title), dob(p.dob)
{
}

Person::~Person()
{
    // announce destruction of person object
    std::cout << "Person destructor <" << firstName << " " << lastName << ">" << std::endl;
}

void Person::Print() const
{
    std::cout << GetTitle() << " " << GetFirstName() << " " << GetMiddleInitial() << ". " << GetLastName() << " was born in " << GetDateOfBirth() << std::endl;
}

void Person::IsA() const
{
    std::cout << "Person" << std::endl;
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
    Student(); // default constructor
    Student(const std::string &, const std::string &, char, const std::string &, const std::string &, float, const std::string &, const std::string &);
    Student(const Student &);
    virtual ~Student() override; // destructor
    virtual void Print() const override;
    virtual void IsA() const override;
    void EarnedPhD(); // public interface to inherited protected member

    // inline function definitions
    float GetGpa() const { return gpa; } // access function for private data mbr
    const std::string &GetCurrentCourse() const { return currentCourse; }
    const std::string &GetStudentID() const { return studentID; }
    void SetCurrentCourse(const std::string &);
    static int GetNumberStudents(); // static member function
};

// definition for static data member
int Student::numStudents = 0; // initial value of 0 which is default for integral values

// definition for static member function
inline int Student::GetNumberStudents()
{
    return numStudents;
}

inline void Student::SetCurrentCourse(const std::string &c)
{
    currentCourse = c;
}

// default constructor uses in-class initial for gpa, while current course is default constructed
Student::Student() : studentID(std::to_string(numStudents + 100) + "ID")
{
    // dynamically allocate memory for pointer members if present (not in this case)
    numStudents++; // increment static counter
}

Student::Student(const std::string &fn, const std::string &ln, char mi, const std::string &t,
                 const std::string &bday, float avg, const std::string &course, const std::string &id) :
                 Person(fn, ln, mi, t, bday), gpa(avg), currentCourse(course), studentID(id)
{
    numStudents++;
}

Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentID(s.studentID)
{
    numStudents++;
}

Student::~Student()
{
    // release allocated memory as needed
    std::cout << "Student destructor <" << GetFirstName() << " " << GetLastName() << ">" << std::endl;
    numStudents--;
}

void Student::Print() const
{
    // private members of person are not accessible within the scope of Student, so we use access functions
    std::cout << GetTitle() << " " << GetFirstName() << " " << GetMiddleInitial() << ". ";
    std::cout << GetLastName() << " with id: " << studentID << " gpa: " << std::setprecision(2) << gpa;
    std::cout << " course: " << currentCourse << std::endl;
}

void Student::IsA() const
{
    std::cout << "Student" << std::endl;
}

void Student::EarnedPhD()
{
    // protected members defined by the base class are accessible within the scope of the derived class.
    // EarnedPhD() provides a public interface to this functionality for derived class instances.
    ModifyTitle("Dr.");
}

class GradStudent : public Student
{
private:
    std::string dissertationTopic;
    std::string advisor;

public: // public members are accessible from any scope
    // member function prototypes
    // default constructor
    GradStudent();
    // alternate constructor
    GradStudent(const std::string &, const std::string &, char, const std::string &, const std::string &,
                float, const std::string &, const std::string &, const std::string &, const std::string &);
    // copy constructor
    GradStudent(const GradStudent &);
    GradStudent(const Student &, const std::string &, const std::string &);
    ~GradStudent() override; // destructor
    void Print() const override final;
    void IsA() const override final;

    // inline function definitions
    const std::string &GetDissertationTopic() const { return dissertationTopic; }
    const std::string &GetAdvisor() const { return advisor; }
};

GradStudent::GradStudent(const std::string &fn, const std::string &ln, char mi, const std::string &t,
            const std::string &bday, float avg, const std::string &course, const std::string &id, 
            const std::string &dissTopic, const std::string &adv) :
            Student(fn, ln, mi, t, bday, avg, course, id), dissertationTopic(dissTopic), advisor(adv)
{
}

GradStudent::GradStudent(const GradStudent &gs) :
                        Student(gs), dissertationTopic(gs.dissertationTopic), advisor(gs.advisor)
{
}

GradStudent::GradStudent(const Student &s, const std::string &dissTopic, const std::string &adv) :
                        Student(s), dissertationTopic(dissTopic), advisor(adv)
{
}

GradStudent::~GradStudent()
{
    // release allocated memory as needed
    std::cout << "Graduate Student destructor <" << GetFirstName() << " " << GetLastName() << ">" << std::endl;
    numStudents--;
}

// void GradStudent::Print() const
// {
//     // private members of person are not accessible within the scope of Student, so we use access functions
//     std::cout << GetTitle() << " " << GetFirstName() << " " << GetMiddleInitial() << ". ";
//     std::cout << GetLastName() << " with id: " << GetStudentID() << " gpa: " << std::setprecision(2) << GetGpa();
//     std::cout << " course: " << GetCurrentCourse() << std::endl;
// }

void GradStudent::Print() const
{
    // private members of person are not accessible within the scope of Student, so we use access functions
    Student::Print();
    std::cout << "Their dissertation topic is: " << dissertationTopic << "\n";
    std::cout << "Their advisor is: " << advisor << std::endl;
}

void GradStudent::IsA() const
{
    std::cout << "Graduate Student" << std::endl;
}

class NonDegreeStudent : public Student
{
private:
    // I decide to not add any more private data members
public: // public members are accessible from any scope
    // member function prototypes
    // default constructor
    NonDegreeStudent();
    // alternate constructor
    NonDegreeStudent(const std::string &, const std::string &, char, const std::string &, const std::string &,
                float, const std::string &, const std::string &);
    // copy constructor
    NonDegreeStudent(const Student &);
    ~NonDegreeStudent() override; // destructor
    void IsA() const override final;

    // inline function definitions
};

NonDegreeStudent::NonDegreeStudent(const std::string &fn, const std::string &ln, char mi, const std::string &t,
            const std::string &bday, float avg, const std::string &course, const std::string &id) :
            Student(fn, ln, mi, t, bday, avg, course, id)
{
}

NonDegreeStudent::NonDegreeStudent(const Student &s) :
                        Student(s)
{
}

NonDegreeStudent::~NonDegreeStudent()
{
    // release allocated memory as needed
    std::cout << "Non-degree Student destructor <" << GetFirstName() << " " << GetLastName() << ">" << std::endl;
    numStudents--;
}


void NonDegreeStudent::IsA() const
{
    std::cout << "Non-degree Student" << std::endl;
}

int main()
{
    constexpr int MAX = 5;
    constexpr int MAXStudents = 3;

    Person *people[MAX] = { }; // initialize with nullptr
    people[0] = new Person("Juliet", "Martinez", 'M', "Ms.", "03/23/1998");
    people[1] = new Student("Hana", "Sato", 'U', "Mr.", "12/04/2001", 3.8, "C++", "178PSU");
    people[2] = new GradStudent("Sara", "Kato", 'B', "Ms.", "03/22/2003", 3.9, "OOP w/ C++", "272PSU",
                                "OOP", "Dr. Very Smart");
    people[3] = new NonDegreeStudent("Giselle", "LeBran", 'R', "Miss", "05/02/2004", 3.3, "C++", "674HOP");
    people[4] = new Person("Linus", "Van Pelt", 'S', "Mr.", "08/11/2004");

    Student *students[MAXStudents] = { }; // initialize with nullptr
    // students[0] = new Student("Hana", "Sato", 'U', "Mr.", "12/04/2001", 3.8, "C++", "178PSU");
    // students[1] = new GradStudent("Sara", "Kato", 'B', "Ms.", "03/22/2003", 3.9, "OOP w/ C++", "272PSU",
    //                             "OOP", "Dr. Very Smart");
    // students[2] = new NonDegreeStudent("Giselle", "LeBran", 'R', "Miss", "05/02/2004", 3.3, "C++", "674HOP");

    for (int i = 0; i < MAXStudents; i++)
    {
        students[i] = dynamic_cast<Student *>(people[i+1]);
    }

    for (int i = 0; i < MAX; i++)
    {
        people[i]->IsA();
        std::cout << "  ";
        people[i]->Print();
    }

    std::cout << std::endl;

    // only graduate students earn a PhD, everyone else change course
    for (int i = 0; i < MAXStudents; i++)
    {
        if (typeid(*students[i]) == typeid(GradStudent))
        {
            students[i]->EarnedPhD();
        }
        else
        {
            students[i]->SetCurrentCourse("OOP w/ C++");
        }
        students[i]->IsA();
        std::cout << "  ";
        students[i]->Print();
    }

    std::cout<< std::endl;

    // destruction of people pointers
    for (int i = 0; i < MAX; i++)
    {
        delete people[i]; // engage virtual destructor sequence
    }

    // destruction of student pointers
    for (int i = 0; i < MAXStudents; i++)
    {
        delete students[i]; // engage virtual destructor sequence
    }

    return 0;
}