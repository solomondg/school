/*
 * Assignment #2
 * 2016/06/21 (June 21)
 * No outside sources used
 */

#include <iostream>



using namespace std;
const float dollarEuroConversion = 0.6938;
const float lbKgConversion       = 0.4536;
const float ozLbConversion       = 0.0625;

int main() {
    cout << "Welcome to Solomon Greenberg's Conversion Program."    << endl;
    cout << "What is the weight of your item in pounds and ounces?" << endl;
    float weightlbs, weightoz, realWeightlbs, weightkgs, priceDollar, priceEuro, pricePerlb, pricePerkg;
    string temp;
    cout << "\nPounds: ";
    cin >> weightlbs;
    cout << "\nOunces: ";
    cin >> weightoz;
    cout << "What is the price in dollars and cents: ";
    cin >> priceDollar;
    cout << endl;

    /* We need to:
     * 1. Turn pounds + oz to just pounds
     * 2. Turn pounds to kg
     * 3. Turn USD to EUR
     * 4. Compute USD/lb
     * 5. Compute EUR/kg
     */
    
    realWeightlbs = weightlbs + (weightoz * ozLbConversion); // Step 1
    weightkgs = weightlbs * lbKgConversion; // Step 2
    priceEuro = priceDollar * dollarEuroConversion; // Step 3
    pricePerlb = priceDollar / realWeightlbs; // Step 4
    pricePerkg = priceEuro / weightkgs; // Step 5

    cout << "The price of this item is $" << pricePerlb << " per pound." << endl;
    cout << "This is equivilant to €" << pricePerkg << " per kg." << endl;
    cout << "Thank you for using Solomon Greenberg's Conversion Program." << endl;

    system("pause");

    return 0;
}
