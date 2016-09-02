#include <iostream>

using namespace std;


int maxMin(int array[], int *max, int *min)
{
    *max = array[0];
    *min = array[0];
    for (int x=0; x < 10; x++)
    {
        *max = (array[x] > *max) ? array[x] : *max;
        *min = (array[x] < *min) ? array[x] : *min;
    }
    return 0;
}


int main()
{
    int array[10] = {8, 3, 5, 34, 1, 8, 6, 4, 643, 1};
    cout << "array values: " << flush;
    for (int x=0; x<10; x++) {cout << array[x] << flush; cout << " ";}
    cout << endl << endl;
    int min = 0;
    int max = 0;
    maxMin(array, &max, &min);
    cout << "Min value: " << min << ". Max value: " << max << endl;
    return 0;
}
