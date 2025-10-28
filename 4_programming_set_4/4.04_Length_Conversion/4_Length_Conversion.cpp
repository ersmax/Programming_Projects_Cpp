/*
Write a program that will read in a length in feet and inches and output the equivalent
length in meters and centimeters. Use at least three functions: one for input,
one or more for calculating, and one for output. Include a loop that lets the user
repeat this computation for new input values until the user says he or she wants to
end the program. There are 0.3048 meters in a foot, 100 centimeters in a meter,
and 12 inches in a foot.
*/
// define NDEBUG
#include <iostream>
#include <limits>
#include <cassert>
using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;

void getLength(double& feetMeter, double& inchesCentimeter);

void lengthConversion(double& feetMeter, double& inchesCentimeter);

void showLength(double feetMeter, double inchesCentimeter);


int main( ) {
    double lengthFtMt, lengthInCm;
    char answer;

    do {

        getLength(lengthFtMt, lengthInCm);

        // assert(lengthFtMt >= 5 && lengthFtMt < 8 &&
        //        lengthInCm >= 0 && lengthInCm < 12);
        // lengthConversion(lengthFtMt, lengthInCm);
        //
        // assert(lengthFtMt >= 1.524 && lengthFtMt < 2.4384 &&
        //        lengthInCm >= 0 && lengthInCm < 100);
        // showLength(lengthFtMt, lengthInCm);

        cout << "Repeat (y/Y)?";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

    } while (answer == 'y' || answer == 'Y');

    return 0;
}

void getLength(double& feetMeter, double& inchesCentimeter) {

    int feetInt, inchesInt;

    while (true) {
        cout << "Enter the height of an adult (feet: 5-7; inches: 0-11)\n"
             << "format: feet inches (e.g. 5 10)...: ";
        if (!(cin >> feetInt >> inchesInt)) {
            cout << "Wrong input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        // discard extra token on the same line
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        if (feetInt < 5 || feetInt > 7 ||
            inchesInt < 0 || inchesInt > 11)
            cout << "Invalid range\n";
        else {
            feetMeter = static_cast<double>(feetInt);
            inchesCentimeter = static_cast<double>(inchesInt);
            break;
        }
    }
}

