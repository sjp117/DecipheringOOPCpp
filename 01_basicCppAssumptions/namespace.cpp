#include <iostream>

// using namespace std; // Do not open entire std namespace
using std::cout; // Instead, activate individual elements
using std::endl; // within the namespace as needed

namespace DataTypes
{
    int total;
    class LinkList
    {
        // full class definitions
    };

    class Stack
    {
        // full class definitions
    };
};

namespace AbstractDataTypes
{
    class Stack
    {
        // full class definitions
    };

    class Queue
    {
        // full class definitions
    };
};

// Add entries to the AbstractDataTypes namespace
namespace AbstractDataTypes
{
    int total;
    class Tree
    {
        // full class definitions
    };
};

int main()
{
    using namespace AbstractDataTypes; // activate namespace
    using DataTypes::LinkList;         // activate only LinkList
    LinkList list1;                    // LinkList is found in DataTypes
    Stack stack1;                      // Stack is found in AbstractDataTypes
    total = 5;                         // total from activate AbstractDataTypes
    DataTypes::total = 85;             // specify non-active mbr., total
    cout << "total " << total << "\n";
    cout << "Datatypes::total " << DataTypes::total;
    cout << endl;
    return 0;
}