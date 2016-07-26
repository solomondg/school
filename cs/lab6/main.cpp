/*
 * lab 6
 * Solomon Greenberg
 *   2016/07/26
 * Outside sources:
 * Previous labs/assignments
 */

#include <iostream>
#include <fstream>

using namespace std;

int endProgram() {
#ifdef __unix__
    cout << "Press return to continue" << flush;
    system("read -n1");
#elif defined(_WIN32) || defined(WIN32)
    system("pause");
#endif
    return 0;
}

int main() {
    cout << "Please enter the file path: " << flush;
    string path;
    cin >> path;

    ifstream file;
    file.open(path); // Open file
    if (!file) // Excutes if file not found 
    {
        cout << "File not found. Exiting." << endl;
        endProgram();
        return 0;
    }
    string name; // For each line of the file
    double num1, num2;
    while (file)
    {
        file >> name >> num1 >> num2;
        if (file)
            cout << name << " " << num1 << " " << num2 << endl;
    }
    endProgram();
    return 0;
}

