/* By Solomon Greenberg
 * 2016/05/25
 * Sources:
 * http://en.cppreference.com/w/cpp/io/cin
 * http://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
 * http://stackoverflow.com/questions/13294067/how-to-convert-string-to-char-array-in-c
 * http://stackoverflow.com/questions/8666378/detect-windows-or-linux-in-c-c
 * http://en.cppreference.com/w/cpp/io/manip/flush
 * http://www.cplusplus.com/reference/cstdlib/rand/
 */
#ifdef __unix__
    #include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)
    #include <windows.h>
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std; // Don't like writing std::whatever

void wait(int loops) // Random wait within bounds, essentially
{
    int x;
    for (x=0;x<loops;x++){
        #ifdef __unix__
            usleep(((rand() % 25) + 1 ) * 2500);
        #elif defined(_WIN32) || defined(WIN32)
            Sleep((rand() % 25) + 1)
        #endif
    }
}

void slowOutput(string toPrint) // Function for the cool little delayed text (hey, crystal balls aren't instant)
{
    char charArray[toPrint.length()];
    strcpy(charArray, toPrint.c_str()); // Turn the inputted string into a char array
    int x;
    for (x=0;x<(int)toPrint.length();x++){ // Print each character after running the wait function once
        cout << charArray[x] << flush;
        wait(1);
    }
}

int main()
{
    srand(time(NULL)); // Seed the random function for more random-ness
    slowOutput("Welcome to Solomon Greenberg's Crystal Ball!\n");
    wait(25);
    slowOutput("What is your name, please? ");
    string x;
    cin >> x;
    wait(25);
    slowOutput("Hello, ");
    slowOutput(x);
    slowOutput(". My name is Solomon.\n");
    wait(25);
    slowOutput("What subject are you studying? ");
    string y;
    cin >> y;
    wait(25);
    slowOutput("Well, ");
    slowOutput(x);
    slowOutput(", Solomon's crystal ball says you will do very well in ");
    slowOutput(y);
    slowOutput(" this term.\n");
    wait(25);
    slowOutput("Good luck!\n");
	#ifdef __unix__
	    cout << "Press any key to continue..." << flush;
	    system("read -n1");
        cout << endl;
	#elif defined(_WIN32) || defined(WIN32)
	    system("pause");
	#endif

    return 0;
}
