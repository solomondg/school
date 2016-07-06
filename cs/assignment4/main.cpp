/*
 * Solomon Greenberg
 * 2016/07/05
 * http://www.cplusplus.com/reference/vector/vector/
 * http://stackoverflow.com/questions/10750057/how-to-print-out-the-contents-of-a-vector
 * http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 * http://www.cplusplus.com/reference/string/string/append/
 *
 */

#include <iostream>
#include <fstream>
#include <vector> 
#include <typeinfo>
#include <string>



using namespace std;

string promptFile() { // Simply prompts for a file path
    string tmp;
    cout << "Enter a full path to the results file: " << endl;
    cin >> tmp;
    return tmp;
}

int endProgram() {
#ifdef __unix__
    cout << "Press any key to continue..." << flush;
    system("read -n1");
    cout << endl;
#elif defined(_WIN32) || defined(WIN32)
    system("pause");
#endif
    return 0;
}

vector<string> returnFile(string filePath) { // Returns the content of a file (and closes it neatly)
    string tmpLine;
    vector<string> fileContents; // Each element in the vector is one line
    ifstream file (filePath);
    while (getline (file, tmpLine)) {
        fileContents.push_back(tmpLine);
    }
    file.close();
    return fileContents;
}

string stripWhiteSpace(string line) { // Removes unneccessary whitespace in a string
    vector<char> parsedLine; 
    for (unsigned long index=0; index<line.length(); index++) {
        if (line[index] != ' ' ) {
            parsedLine.push_back(line[index]);
        } // We don't want to mess with the character if it's not whitespace
        else if ((line[index] == ' ') && (line[index+1] != ' ') && (index != line.length()-1)){ // If it is whitespace and the next character isn't whitespace and it isn't at the end of the line, keep it. 
            parsedLine.push_back(line[index]);
        }
    }

    string strParsedLine(parsedLine.begin(), parsedLine.end()); // eew c++ why
    return strParsedLine;
}

vector<string> pythonIsSoMuchBetter (string line) { // WHY CAN'T I JUST HAVE LINE.SPLIT()
    vector<string> vectorMarketing; // my life is complete 

    char delimiter = ' ';
    string tmp = "";

    int iter; // not using size_t cause that's dumb and this isn't going to be 2^16 bytes long like wtf
    for (iter=0; iter<(int)line.length(); iter++) {
        if (line[iter] == delimiter) {
            vectorMarketing.push_back(tmp);
            tmp = "";
        }
        else {
            tmp += line[iter];
        }
    }

    if (tmp.length() != 0) {
        vectorMarketing.push_back(tmp);
    }

    // Debug code
    // for (vector<string>::const_iterator i = vectorMarketing.begin(); i != vectorMarketing.end(); i++) {
    //     cout << *i << endl;
    // }

    return vectorMarketing;
}

int main() {
    vector<string> readFileContents;
    readFileContents = returnFile(promptFile()); // Read file to readFileContents

    if (readFileContents.size() == 0) { // Check to make sure file was read
        cout << "Error reading file. Please check file path. " << endl;
        endProgram();
        return 1;
    }

    vector<vector<string> > vectorArray; // I can't have '>>'?! What the hell, C++

     // If file was read correctly (signified by the program not stopping/erroring), print file and add parsed vectors into vectorArray
    cout << "Read file contents: " << "\n" << endl;
    for (vector<string>::const_iterator i = readFileContents.begin(); i != readFileContents.end(); i++) {
        cout << *i << endl; // 'cat' file 
        vectorArray.push_back(pythonIsSoMuchBetter(stripWhiteSpace(*i))); // Parse and stuff, put it all in vectorArray
    }
    cout << "\n\n\n";

    vector<vector<string>*> childNoAd, childYesAd, adultNoAd, adultYesAd; // Make the 4 vectors that'll be filled with the pointers to the appropriate vectors

    for (int iter = 0; iter<(int)vectorArray.size(); iter++) {
        if (vectorArray[iter][1] == "Y") {
            (stoi(vectorArray[iter][2]) < 18) ? childYesAd.push_back(&vectorArray[iter]) : adultYesAd.push_back(&vectorArray[iter]);
        }
        else {
            (stoi(vectorArray[iter][2]) > 18) ? childNoAd.push_back(&vectorArray[iter]) : adultNoAd.push_back(&vectorArray[iter]);
        }
    }

    cout << childYesAd.size() << endl;



    return 0;
}
