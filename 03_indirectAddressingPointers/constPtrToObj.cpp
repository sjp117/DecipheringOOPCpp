// Using constant pointers to objects

// define. allocate, load simple strings using strcpy()

char *regularString = new char[36]; // sized for str below
strcpy(regularString, "I am a modifiable string");
char *anotherRegularString = new char[21]; // sized for string below
strcpy(anotherRegularString, "I am also modifiable");

// Define a const pointer to a string; must be initialized
char *const constStringAndPtr = regularString; // Ok

// You may not modify a const pointer to point elsewhere
// constPtrString = anotherRegularString; // No!

// But you may change the data which you point to
strcpy(constPtrString, "I can change the value"); // Yes

// Trying to change the pointer or the data is illegal
constStringAndPtr = anotherRegularString; // No! Can't modify address
strcpy(constStringAndPtr, "Nope");        // No! Can't modify data


