/*
 * Solomon Greenberg
 * 2016/07/30
 * Assignment 7b (extra credit w/ structs & search algorithms)
 * 
 * Outside Sources:
 * Previous assignments
 *
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <string>
#include <string.h>
#include <algorithm>
#include <iomanip> 
#include <cstring>

using namespace std;

struct Book
{
    string title;
    string author;
};

vector<Book> books;

int loadData(string pathname);  
void showAll(int count);
int showBooksByAuthor (int count, string name);
int showBooksByTitle (int count, string title);


Book lineToBook(string bookLine, string authorLine); // Turns 2 lines from GetLine function to a Book object

void greeter()
{
    string pathname;
    cout << "\n\n" << endl;
    cout << "Welcome to Solomon's Library Database" << endl;
    cout << "\n\n" << endl;
    cout << "Please enter the name of the backup file: " << endl;

    cin >> pathname;

    while (loadData(pathname) == 1) // It'll return 1 if something fails, so then we just prompt the user again
    {
        cout << "\nNo file found or incorrect permissions. Try again: " << endl;
        cin >> pathname;
    }
    cout << "File successfully read." << endl;
}

int endProgram() {
#ifdef __unix__
    cout << "Press return to continue" << flush;
    system("read -n1");
#elif defined(_WIN32) || defined(WIN32)
    system("pause");
#endif
    return 0;
}

int loadData(string pathname) // Populates the vector of books with the Book datatype, based on loaded data.
{
    ifstream file(pathname.c_str());
    string tmpLine;
    vector<string> fileContents; // each element = 1 line
    if (!file.good()) return 1; // Means we could not read the file
    while (getline(file, tmpLine)) 
    {
        fileContents.push_back(tmpLine);
    }
    file.close();
    file.clear(ios_base::goodbit);
    for (unsigned int x=0; x<fileContents.size(); x+=2)
    {
        books.push_back(lineToBook(fileContents[x], fileContents[x+1]));
    }
    return 0;
}

Book lineToBook(string bookLine, string authorLine) // Turns 2 lines from GetLine function to a Book object
{
    Book tmpBook;
    tmpBook.title = bookLine;
    tmpBook.author = authorLine;
    return tmpBook;
}

int menuprompt(bool screwedup)
{
    if (screwedup) cout << "Invalid menu choice. Please try again:" << endl;
    int selection;
    cout << "Select an option from the menu: " << endl;
    cout << "Enter Q to (Q)uit, Search (A)uthor, Search (T)itle, (S)how All: " << flush;
    char tmpvar;
    cin >> tmpvar;
    cin.clear();
    fflush(stdin);

    selection = (tolower(tmpvar) == 'q') ? 0 // Sets it to the correct thingy
        :       (tolower(tmpvar) == 'a') ? 1
        :       (tolower(tmpvar) == 't') ? 2
        :       (tolower(tmpvar) == 's') ? 3
        : menuprompt(true);
    return selection;
}

string promptAuthor()
{
    string author;
    cout << "Name of author: " << flush;
    cin >> author;
    cout << "\nSearching" << flush;
    return author;
}

string promptTitle()
{
    string title;
    cout << "Title of book: " << flush;
    cin >> title;
    cout << "\nSearching" << flush;
    return title;
}

vector<Book *> searchByAuthor(string name)
{
    int bookVectorSize = books.size();
    vector<Book *> foundBooks;
    for (int x=0; x<bookVectorSize; x++)
    {
        if (books[x].author.find(name) != string::npos)
        {
            foundBooks.push_back(&books[x]);
        }
        cout << "." << flush;
    }
    cout << endl << endl;
    cout << "Total of " << bookVectorSize << " books in database." << endl;
    cout << "Found " << foundBooks.size() << " books with matching authors.\n" << endl;
    return foundBooks;
}

vector<Book *> searchByTitle(string name)
{
    int bookVectorSize = books.size();
    vector<Book *> foundBooks;
    for (int x=0; x<bookVectorSize; x++)
    {
        if (books[x].title.find(name) != string::npos)
        {
            foundBooks.push_back(&books[x]);
        }
        cout << "." << flush;
    }
    cout << endl << endl;
    cout << "Total of " << bookVectorSize << " books in database." << endl;
    cout << "Found " << foundBooks.size() << " books with matching titles.\n" << endl;
    return foundBooks;
}

inline bool sortComparison(Book * book1, Book * book2, char metric) // compares book titles, case insensitive. Metric can be a or t, a == author, t == title. Inline cause that's apparently faster with GCC
{
    return (metric == 't') ? // Evil, I know.
        ((transform(book1->title.begin(), book1->title.end(),book1->title.begin(), ::toupper) > (transform(book2->title.begin(), book2->title.end(),book2->title.begin(), ::toupper))))
        : ((transform(book1->author.begin(), book1->author.end(),book1->author.begin(), ::toupper) > (transform(book2->author.begin(), book2->author.end(),book2->author.begin(), ::toupper)))); // is it normal to feel shame while writing code?
}

bool isSorted(vector<Book *> toCheck, char metric) 
{
    for (unsigned int x=1; x<toCheck.size(); x++)
    {
        if (!sortComparison(toCheck[x], toCheck[x-1], metric))
        {
            cout << "Sort thingy canceled at pos " << x << endl;
            return false;
        }
    }
    return true;
}

vector<Book *> bubbleSort(vector<Book *> foundBooks, char metric, bool ascending) // garbage bubble sort
{
    Book * tmpBook;
    while (!isSorted(foundBooks, metric))
    {
        for (unsigned int x=1; x<foundBooks.size(); x++)
        {
            if (!sortComparison(foundBooks[x], foundBooks[x-1], metric))
            {
                tmpBook = foundBooks[x];
                foundBooks[x] = foundBooks[x-1];
                foundBooks[x-1] = foundBooks[x];
            }
        }
    }

    if (ascending) return foundBooks; // It's sorted ascending if we want ascending
    
    reverse(foundBooks.begin(), foundBooks.end());
    return foundBooks;
}

void printBookVector(vector<Book *> bookVector) // Version of the function for vectors of pointers to books
{
    for (unsigned int x=0; x<bookVector.size(); x++)
    {
        cout << "Book " << x << ": " << endl;
        cout << "Title: " << bookVector[x]->title << endl;
        cout << "Author: " << bookVector[x]->author << endl;
        cout << endl;
    }
}

// void printBookVector(vector<Book> bookVector) // Version of the function for vectors of books
// {
//     for (unsigned int x=0; x<bookVector.size(); x++)
//     {
//         cout << "Book " << x << ": " << endl;
//         cout << "Title: " << bookVector[x].title << endl;
//         cout << "Author: " << bookVector[x].author << endl;
//         cout << endl;
//     }
// }

int parser(int response)
{
    if (response == 1) // Means the user wants to search by author
    {
        string author = promptAuthor();
        vector<Book *> foundBooks = searchByAuthor(author);

        char sortByTitleOrAuthor;
        cout << "Sort by author (not title): y/N " << flush;
        cin >> sortByTitleOrAuthor;
        cin.clear();
        fflush(stdin);

        cout << "ascending order (not decending)? Y/n " << flush;
        char tmpchar;
        cin >> tmpchar;
        cin.clear();
        fflush(stdin);

        vector<Book *> foundBooksSorted = bubbleSort(foundBooks, (sortByTitleOrAuthor == 'y') ? 'a' : 't', !(tmpchar == 'n'));
        printBookVector(foundBooksSorted);
        cout << endl;
    }

    else if (response == 2) // Means the user wants to search by title 
    {
        string title = promptTitle();
        vector<Book *> foundBooks = searchByTitle(title);

        char sortByTitleOrAuthor;
        cout << "Sort by author (not title): y/N " << flush;
        cin >> sortByTitleOrAuthor;
        cin.clear();
        fflush(stdin);

        cout << "ascending order (not decending)? Y/n " << flush;
        char tmpchar;
        cin >> tmpchar;
        cin.clear();
        fflush(stdin);

        vector<Book *> foundBooksSorted = bubbleSort(foundBooks, (sortByTitleOrAuthor == 'y') ? 'a' : 't', !(tmpchar == 'n'));
        printBookVector(foundBooksSorted);
        cout << endl;
    }

    else if (response == 3) // Means the user simply wants to print a list of books
    {
        vector<Book *> bookPointerVector; // I was stupid and coded everything for option 2/3 using vectors and I don't want to go make overloaded functions cause that is u g l y

        for (unsigned int x=0; x<books.size(); x++) bookPointerVector.push_back(&books[x]); // Just takes the book things and makes them pointers or whatever

        char sortByTitleOrAuthor;
        cout << "Sort by author (not title): y/N " << flush;
        cin >> sortByTitleOrAuthor;
        cin.clear();
        fflush(stdin);

        cout << "ascending order (not decending)? Y/n " << flush;
        char tmpchar;
        cin >> tmpchar;
        cin.clear();
        fflush(stdin);

        vector<Book *> sortedBooks = bubbleSort(bookPointerVector, (sortByTitleOrAuthor == 'y') ? 'a' : 't', !(tmpchar == 'n'));
        printBookVector(sortedBooks);
        cout << endl;
    }

    return 0;
}


int main()
{
    greeter();
    int response;
    while (true)
    {
        response = menuprompt(false);
        if (response == 0) break;
        parser(response);
    }
    endProgram();
    return 0;
}
