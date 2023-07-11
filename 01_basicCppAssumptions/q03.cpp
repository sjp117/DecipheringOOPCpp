/*
1. Create a simple program using a struct or class to make a user defined type for Book.
2. Add data members for title, author, and number of pages.
3. Create two variables of type Book and use the dot operator . to fill in the data members
   for each such instance.
4. Use iostreams to both prompt the user for input values, and to print each Book instance when
   complete.
5. Use only features covered in this chapter.
*/

#include <iostream>
#include <iomanip>

class Book
{
public:
    std::string title;
    std::string author;
    int numberOfPages;
};

int main()
{
    // define user input variables
    int choice;
    int choiceIndex;

    // define books and array of books
    Book b1, b2;
    Book books[2] = {b1, b2};

    // initialize books
    books[0].title = "Adventure of Badger";
    books[0].author = "Dave Doodle";
    books[0].numberOfPages = 342;

    books[1].title = "Introduction to Badgers";
    books[1].author = "Bob Lee";
    books[1].numberOfPages = 324;

    // prompt for user choice
    std::cout << "Choose book 1 or 2: ";
    std::cin >> std::setw(1) >> choice;
    std::cout << std::flush; // I'm guessing it's proper to flush since it couldn't when asking for input.
    choiceIndex = choice - 1;

    // output information on book of choice
    std::cout << "The title of book " << choice << " is \"" << books[choiceIndex].title << "\".\n";
    std::cout << "It was written by " << books[choiceIndex].author << ".\n";
    std::cout << "It has " << books[choiceIndex].numberOfPages << " pages." << std::endl;
}