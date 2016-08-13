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
    cout << "\nSearching...\n" << endl;
    return author;
}

string promptTitle()
{
    string title;
    cout << "Title of book: " << flush;
    cin >> title;
    cout << "\nSearching...\n" << endl;
    return title;
}

int parser(int response)
{
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
    }
    endProgram();
    return 0;
}
