/*
*One gallon is 3785.41 milliliters. Write a program that will read the volume of
a package of milk in milliliters, and output the volume in gallons, as well as the
number of packets needed to yield one gallon of milk.
*/

#include <iostream>
using namespace std;

int main( ) {
    const double ML_PER_GALLON = 3785.41;
    double volume_ml;
    double volume_gallons;
    int packets_needed;
    double division;    //store temp variable

    cout << "Enter the volume of the milk package in milliliters:";
    cin >> volume_ml;
    volume_gallons = volume_ml / ML_PER_GALLON;

    cout << "Volume in gallons: " << volume_gallons << endl;
    // Round up to ensure at least one gallon
    division = ML_PER_GALLON/volume_ml;
    packets_needed = static_cast<int>(division);
    if (division > packets_needed) {
        packets_needed++; // Round up if there's a remainder
    }

    cout << "Number of packets needed to yield one gallon: "
         << packets_needed << endl;

    return 0;
}