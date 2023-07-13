#include <iostream>
#include <iomanip>
#include <cstring>

char suffix = 'A';

// function prototype
const char *GenId(const char *);

int main()
{
    const char *newId1, *newId2; // pointer declaration
    newId1 = GenId("Group");     // function will allocate memory
    newId2 = GenId("Group");

    std::cout << "New ids: " << newId1 << " " << newId2 << std::endl;
    delete[] newId1; // delete allocated memory
    delete[] newId2; // caution: deleting in different scope than allocation can lead to errors
    return 0;
}

const char *GenId(const char *base)
{
    char *temp = new char[strlen(base) + 2];
    strcpy(temp, base);            // use base to initialize string
    temp[strlen(base)] = suffix++; // append suffix to base
    temp[strlen(base) + 1] = '\0'; // add null character
    return temp;                   // temp will be upcast to a const char * to be treated more
                                   // restrictively than i was defined
}