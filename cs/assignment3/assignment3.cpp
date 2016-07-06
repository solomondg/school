/* Program by Solomon Greenberg
 * 2016/06/23
 * Note: C++14
 * Outside sources:
 * http://en.cppreference.com/w/cpp/container/vector
 * http://stackoverflow.com/questions/903221/press-enter-to-continue
 *
 */

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int charYNToInt(char input) {return (input == 'y') ? 1 : 0;} // Takes in char (y/n) and returns 1/0, respectively
bool intToBool(int input) {return (input == 1) ? true : false;} // In: 1/0, Out: true/false, respectively

vector<int> getResponses() { // Will get the responses from user, return as int array
    vector<int> responses = {0, 0, 0, 0, 0};
    /* 
     * Main array. Indexes:
     *             0 - # of adults
     *             1 - # of children
     *             2 - vehicle (bool - 0:false, 1:true)
     *             3 - vehicle length
     *             4 - over 7 ft? ( bool - 0:false, 1:true)
     */
    int tmpInt;
    char tmpChar;

    cout << "Welcome to Solomon Greenberg's Fare Calculator" << endl;
    cout << "How many adults (age 12 or over) are in your party? ";
    cin >> tmpInt;
    responses[0] = tmpInt;
    cout << "How many children (age 5 to 11) are in your party? ";
    cin >> tmpInt;
    responses[1] = tmpInt;
    cout << "Are you driving a vehicle onto the ferry? (y/n): ";
    cin >> tmpChar;
    responses[2] = charYNToInt(tmpChar);
    // Executed if there are any cars
    if (intToBool(responses[2])) { 
        cout << "What is the length of the vehicle in feet? ";
        cin >> tmpInt;
        responses[3] = tmpInt;
        cout << "Is the vehicle over 7 feet high? (y/n): ";
        cin >> tmpChar;
        responses[4] = charYNToInt(tmpChar);
    }
    return responses;
}

vector<float> fareCalc(vector<int> responseInput) {
    float fare = 0;
    float fuelCharge = 0;

    // Fare and fuel surcharge for adults
    fare += (responseInput[0] * 13);
    fuelCharge += (responseInput[0] * 1.25);

    // Fare and fuel surcharge for children
    fare += (responseInput[1] * 6.5);
    fuelCharge += (responseInput[1] * 1.25);

    // Executed if there are any cars
    if (intToBool(responseInput[2])) {
        switch(responseInput[4]) {
            case 0: { // If it's not oversized (<7 ft tall)
                        fare += 43.0;
                        fuelCharge += 4.15;
                        fare += (responseInput[3] > 20) ? 2.15 * float (responseInput[3] - 20) : 0; // Add $2.15 for every ft over 20 if it's over 20 ft, else add none
                        break;
                    }
            case 1: { // If it's oversized (>7 ft tall)
                        fare += 69.0;
                        fuelCharge += 10.4;
                        fare += (responseInput[3] > 20) ? 3.45 * float (responseInput[3] - 20) : 0; // Add $3.45 for every ft over 20 if it's over 20 ft, else add none
                        break;
                    }
        }
    }
    vector<float> responses = {fare, fuelCharge, fare + fuelCharge};
    return responses;
}

int fareResponse(vector<float> fareAndFuel) {
    cout << "Your fare is $" << fareAndFuel[0] << " plus a fuel surcharge of $" << fareAndFuel[1] << endl;
    cout << "The total amount payable is $" << fareAndFuel[2] << endl;
    cout << "Thank you for using Solomon Greenberg's Fare Calculator" << endl;
    return 0;
}

int returnToContinue(int blanklines) {
    int x;
    for (x = 0; x<blanklines; x++) {
        cout << endl;
    }
    #ifdef __unix__
        cout << "Press enter to continue..." << flush;
        //cout << endl;
        system("read");
    #elif defined(_WIN32) || defined(WIN32)
        system("pause");
    #endif
    return 0;
}

int main() {
    fareResponse(fareCalc(getResponses()));
    returnToContinue(3);
    return 0;
}
