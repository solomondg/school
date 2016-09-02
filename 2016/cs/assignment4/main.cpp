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
#include <iomanip> 



using namespace std;

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

vector<string> returnFile(string filePath) { // Returns the content of a file (and closes it neatly)
    string tmpLine;
    vector<string> fileContents; // Each element in the vector is one line
    ifstream file (filePath);
    while (getline (file, tmpLine)) {
        fileContents.push_back(tmpLine);
    }
    file.close();
    file.clear(ios_base::goodbit);
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
    // }

    return vectorMarketing;
}

int main() {
    vector<string> readFileContents;
    readFileContents = returnFile(promptFile()); // Read file to readFileContents

    if (readFileContents.size() == 0) { // Check to make sure file was read
        endProgram();
        return 1;
    }

    vector<vector<string> > vectorArray; // having to adhere to c++98 is Really Fun! 

     // If file was read correctly (signified by the program not stopping/erroring), print file and add parsed vectors into vectorArray
    for (vector<string>::const_iterator i = readFileContents.begin(); i != readFileContents.end(); i++) {
        vectorArray.push_back(pythonIsSoMuchBetter(stripWhiteSpace(*i))); // Parse and stuff, put it all in vectorArray
    }

    vector<vector<string>*> childNoAd, childYesAd, adultNoAd, adultYesAd; // Make the 4 vectors that'll be filled with the pointers to the appropriate vectors

    for (int iter = 0; iter<(int)vectorArray.size(); iter++) {
        if (vectorArray[iter][1] == "Y") {
            (stoi(vectorArray[iter][2]) < 18) ? childYesAd.push_back(&vectorArray[iter]) : adultYesAd.push_back(&vectorArray[iter]);
        }
        else {
            (stoi(vectorArray[iter][2]) > 18) ? childNoAd.push_back(&vectorArray[iter]) : adultNoAd.push_back(&vectorArray[iter]);
        }
    }



    /* 
     * We need to:
     * 1. Find average of <18 who has watched the ad
     * 2. Find average of <18 who has not watched the ad
     * 3. Find average of >=18 who has watched the ad
     * 4. Find average of >=18 who has not watched the ad
     * 5. Find average of total
     */

    float childYesAdAverage, childNoAdAverage, adultYesAdAverage, adultNoAdAverage, totalAverage; // Initialize variables we will use
    childYesAdAverage = childNoAdAverage = adultYesAdAverage = adultNoAdAverage = totalAverage = 0.0;

    for (int iter = 0; iter<(int)childYesAd.size(); iter++) { // Step 1 + 5
        childYesAdAverage += stoi((*childYesAd[iter])[3]);
        totalAverage += stoi((*childYesAd[iter])[3]);
    }
    childYesAdAverage /= childYesAd.size();

    for (int iter = 0; iter<(int)childNoAd.size(); iter++) { // 2 + 5
        childNoAdAverage += stoi((*childNoAd[iter])[3]);
        totalAverage += stoi((*childNoAd[iter])[3]);
    }
    childNoAdAverage /= childNoAd.size();

    for (int iter = 0; iter<(int)adultYesAd.size(); iter++) { // 3 + 5
        adultYesAdAverage += stoi((*adultYesAd[iter])[3]);
        totalAverage += stoi((*adultYesAd[iter])[3]);
    }
    adultYesAdAverage /= adultYesAd.size();

    for (int iter = 0; iter<(int)adultNoAd.size(); iter++) { // 4 + 5
        adultNoAdAverage += stoi((*adultNoAd[iter])[3]);
        totalAverage += stoi((*adultNoAd[iter])[3]);
    }
    adultNoAdAverage /= adultNoAd.size();

    totalAverage /= childYesAd.size() + childNoAd.size() + adultYesAd.size() + adultNoAd.size();


    cout << fixed << showpoint; // Set precision of cout to 2
    cout << setprecision(2);
    cout << "Average score for subjects under 18 who have not seen the ad:\t" << childNoAdAverage << endl;
    cout << "Average score for subjects under 18 who have seen the ad:\t" << childYesAdAverage << endl;
    cout << "Average score for subjects over 18 who have not seen the ad:\t" << adultNoAdAverage << endl;
    cout << "Average score for subjects over 18 who have seen the ad:\t" << adultYesAdAverage << endl;
    cout << "Average score for all subjects:\t\t\t\t\t" << totalAverage << endl;

    endProgram();
    return 0;
}
