/* Solomon Greenberg
 * Jul 20 or whenever
 * Outside sources:
 * Pulled a couple functions from my code from assignment #4
 * http://stackoverflow.com/questions/25658931/strcmp-in-a-function-in-c
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



vector<unsigned long> checksums; // Using vectors gives us the flexibility to essentially store the checksums for an indefinite amount of files
vector<string> filenames;

string promptFile() { // Simply prompts for a file path
    string tmp;
    cout << "Enter the full path to the file:" << endl;
    cin >> tmp;
    return tmp;
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


string wrongFile () // Errors until you enter a valid file path, then returns it
{
    cout << "File not found or you do not have read permissions. Try again: " << endl;
    ifstream remedialFile;
    string remedialFilePath;
    remedialFilePath = promptFile();
    remedialFile.open(remedialFilePath.c_str(), ios::binary);
    if (!remedialFile.good())
    {
        remedialFile.close();
        remedialFile.clear(ios_base::goodbit);
        remedialFilePath = wrongFile();
    }
    return remedialFilePath;
}


vector<char> returnFile(string filePath, string *tovector) { // Returns the content of a file (and closes it neatly) into a vector

    ifstream fileBin;
    fileBin.open(filePath.c_str(), ios::binary);
    string f = filePath;
    if (!fileBin.good()) // Nonexistant file or we don't have read permissions
    {
        fileBin.close();
        fileBin.clear(ios_base::goodbit);
        f = wrongFile();
        fileBin.open(f.c_str(), ios::binary);
    }
    *tovector = f;

    fileBin.seekg(0, ios_base::end);
    unsigned int fileLen = fileBin.tellg();
    fileBin.seekg(0, ios_base::beg);

    char tmpArray[fileLen]; // Yes, it's supposed to have a size of 100,000, but there'sno point in allocating more memory than you really need, hence setting it to fileLen.

    fileBin.read(tmpArray, fileLen);

    fileBin.close();
    fileBin.clear(ios_base::goodbit);


    vector<char> fileContents;

    for (unsigned int x=0; x<fileLen-1; x++)
    {
        fileContents.push_back(tmpArray[x]);
    }
    return fileContents;
}

unsigned int menuPrompt(bool screwedup) // Returns 0 for compute, 1 for verify, and 2 for quit
{
    char selection;
    if (screwedup) cout << "Invalid menu choice. Try again:" << endl;
    cout << "Please select:" << endl;
    cout << "\tA) Compute checksum of specified file" << endl;
    cout << "\tB) Verify integrity of specified file" << endl;
    cout << "\tQ) Quit" << endl;
    cin >> selection;
    cin.clear();
    fflush(stdin);
    return (tolower(selection) == 'a') ? 0 // Evil multi line ternary thing that works
        : (tolower(selection) == 'b') ? 1
        : (tolower(selection) == 'q') ? 2
        : menuPrompt(true); // Recursion, yay! (well, kind of)
}

unsigned int checksumFile(vector<char> file)
{
    unsigned int checksum = 0;
    for (unsigned int x=0; x<file.size()-1; x++)
    {
        checksum += (int) file[x];
    }
    return checksum;
}

int menuParse(int selection)
{
    string tmpStringFilePath;
    string tmpStringName;
    vector<char> tmpVectorFile;
    int tmpChecksum;
    tmpStringFilePath = promptFile();
    tmpVectorFile = returnFile(tmpStringFilePath, &tmpStringName); // Tmpstringname is needed because the user could enter a wrong file and pointers allows us to not have to reassign the variable which can be confusing
    tmpChecksum = checksumFile(tmpVectorFile);
    cout << tmpChecksum << endl;
    bool endChecking = false; // If set to true, we assume we already did something and we don't need to push_back the new checksum.
    switch (selection)
    {
        case 0:
            for (unsigned int x=0; x<filenames.size() && !endChecking; x++)
            {
                const char *string_1 = filenames[x].c_str();
                const char *string_2 = tmpStringName.c_str();
                if (strcmp(string_1, string_2) == 0) // Check to see if there's an existing string
                {
                    char response;
                    cout << "Warning: existing checksum for this file stored" << endl;
                    if (checksums[x] == tmpChecksum)
                    {
                        cout << "Old and new checksums match (" << tmpChecksum << "), not doing anything" << endl;
                        endChecking = true;
                    }
                    else
                    {
                        cout << "Old and new checksums differ (old: " << checksums[x] << ", new: " << tmpChecksum << "). Overwrite checksum? (y/n) " << flush;
                        cin >> response;
                        cin.clear();
                        fflush(stdin);
                        if (tolower(response) == 'y')
                        {
                            cout << "Overwriting...." << endl;
                            checksums[x] = tmpChecksum;
                            cout << "Done! Checksum successfully overwritten" << endl;
                            cout << endl;
                        }
                        endChecking = true;
                    }
                }
            }
            if (!endChecking)
            {
                cout << "New checksum for file " << tmpStringName << " (" << tmpChecksum << ").\nWriting...." << endl;
                cout << "Done!" << endl;
                cout << endl;
                checksums.push_back(tmpChecksum);
                filenames.push_back(tmpStringName);
            }
            break;
        case 1:
            for (unsigned int x=0; x<filenames.size() && !endChecking; x++)
            {
                const char *string_1 = filenames[x].c_str();
                const char *string_2 = tmpStringName.c_str();
                if (strcmp(string_1, string_2) == 0)
                {
                    cout << "Found entry for " << tmpStringName << endl;
                    cout << "Stored checksum: " << checksums[x] << endl;
                    cout << "File checksum:   " << tmpChecksum << endl;
                    if (tmpChecksum == checksums[x])
                    {
                        cout << "Checksums match! File verified" << endl;
                        cout << endl;
                    }
                    else
                    {
                        cout << "Checksums don't match. File changed" << endl;
                        cout << endl;
                    }
                    endChecking = true;
                }
            }
            break;
            
    }
    return 0;
}


int main()
{
    int selection;
    while ((selection = menuPrompt(false)) != 2) // We don't want to run menuprompt more than once per while loop
    {
        menuParse(selection);
        if (checksums.size() != filenames.size())
        {
            cout << "Fatal Error! Size of the checksums and the filenames vector differ!" << endl;
            cout << "Size of vector of checksums: " << checksums.size() << endl;
            cout << "Size of vector of filenames: " << filenames.size() << endl;
            cout << "Unrecoverable error: Exiting.";
            endProgram();
            return 0;
        }
    }
    endProgram();
    return 0;
}
