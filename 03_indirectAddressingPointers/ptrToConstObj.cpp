// Using pointers to constant objects

#include <cstring>

// const qualified str; the data pointed to will be const
const char *constData = "constant";
const char *moreConstData = nullptr;

// regular string, defined. One is loaded using strcpy()
char *regularString = nullptr;
char *anotherRegularString = new char[8];

strcpy(anotherRegularString, "regular"); // I'm not sure why this gives an error.
                                         // Maybe it's just not a working example

// // trying to modify data marked as const will not work
// strcpy(constData, "Can I do this? "); // NO!
// // Try to circumvent by having a char * point to a const char * also will not work
// regularString = constData; // NO!

// But we can treat a char * more strictly by assigning to const char *.
// It will be a const from that viewpoint only
moreConstData = anotherRegularString; // Yes - can do this!