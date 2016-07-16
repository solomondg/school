#include <iostream>

using namespace std;

int GetMax(int x, int y) 
{
    return (x > y) ? x : y;
}

int main()
{
    int x, y;
    cout << "Enter two numbers:"<< endl << "Number 1: ";
    cin >> x;
    cout << endl << "Number 2: " << flush;
    cin >> y;
    cout << endl << GetMax(x, y) << " is the greatest number" << endl;
    system("pause");
    return 0;
}
