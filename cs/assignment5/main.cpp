/*
 * Solomon Greenberg
 * 2016/05/12
 * Outside Sources:
 * http://stackoverflow.com/questions/1801391/what-is-the-best-algorithm-for-checking-if-a-number-is-prime
 */

#include <iostream>
#include <vector>
#include <math.h>
#include <sstream>


using namespace std;

bool isPrime (long n) // check to see if a number is prime
{
    long maxToSearch = (long) sqrt(n); // We actually only need to search numbers up to and including √n. Example: √36 = 6, 36's factors are 1*36, 2*18, 3*12, 4*9, and 6*6. 1, 2, 3, 4, and 6 <= 6, all other factors are multiplied by these. 
    if ((n == 0) or (n % 2 == 0) or (n % 3 == 0)) // Get rid of the easy ones 
        return false;
    long index = 4; // We already tested if n was divisible by 2 or 3, don't want to waste the extra cycles (this is obviously a very performance-oriented application </sarcasm>)
    while (index < maxToSearch)
    {
        if (n % index == 0)
            return false;
        index++;
    }
    return true;
}
 
bool smartass_isPrime()
{
    return false;
}

long power2 (long n) // same as pow(2, n)
{
    long result = 1;
    if (n == 0) return 1;
    while (n > 0) // literally just double a ton
    {
        result *= 2;
        n--;
    }
    return result;
}

vector< vector<long> > mersenne(long topnumber) // return vector of vectors of long, index 0 is n, 1 is 
{
    vector< vector<long> > returnVector;
    vector<long> tmpVector;  // LLVM is yelling at me that generalized initializer lists are incompatible with C++98, so I have to use a tmp vector for the push_back operation (can't just say returnVector.push_back(vector<long> {index, tmpNumber}))
    long index = 0;
    long tmpNumber = 0; // For storing the (2^n)-1 value in case it's a prime
    while (tmpNumber < topnumber)
    {
        cout << index << endl;
        tmpNumber = power2(index) - 1;
        if (isPrime(tmpNumber))
        {
            tmpVector.clear();
            tmpVector.push_back(index);
            tmpVector.push_back(tmpNumber);
            returnVector.push_back(tmpVector);
        }
        index++;
    }
    return returnVector;
}

int pad_and_print_n(long n) // Fancy text padding for n-values
{
    string outputString = "";
    string tmpString = to_string(n);
    for (unsigned int x=0; x<2-tmpString.length(); x++)
    {
        outputString += " ";
    }
    cout << outputString << to_string(n);
    return 0;
}

int pad_and_print_prime(long n) // Fancy text padding for primes
{
    string outputString = "";
    string tmpString = to_string(n);
    for (unsigned int x=0; x<7-tmpString.length(); x++)
    {
        outputString += " ";
    }
    cout << outputString << to_string(n);
    return 0;
}

string pspace(unsigned int n) // return set number of spaces
{
    string returnstring = "";
    for (unsigned int x=0; x<n; x++)
    {
        returnstring += " ";
    }
    return returnstring;
}

int returnToContinue(int blanklines) { // Cross-platform system("pause") equivilant
    int x;
    for (x = 0; x<blanklines; x++) {
        cout << endl;
    }
    #ifdef __unix__
        cout << "Press enter to continue..." << flush;
        //cout << endl;
        system("read -n1");
    #elif defined(_WIN32) || defined(WIN32)
        system("pause");
    #endif
    return 0;
}


int main() 
{
    cout << "Mersenne Primes by Solomon Greenberg" << endl;
    cout << " n              Mersenne Prime" << endl;
    cout << "==              ==============" << endl;
    long topnumber = 100000000000;
    vector< vector<long> >mersenneVector = mersenne(topnumber);
    for (unsigned long x=0; x<mersenneVector.size(); x++)
    {
        cout << pad_and_print_n(mersenneVector[x][0]) << pspace(19) << pad_and_print_prime(mersenneVector[x][1]) << endl;
    }
    // returnToContinue(2);
    return 0;
}
