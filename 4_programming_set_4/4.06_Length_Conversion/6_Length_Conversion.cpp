/*
(You should do the previous two programming projects before doing this one.)
Write a program that combines the functions in the previous two programming
projects. The program asks the user if he or she wants to convert from feet and
inches to meters and centimeters or from meters and centimeters to feet and inches.
The program then performs the desired conversion. Have the user respond by typing
the integer 1 for one type of conversion and 2 for the other conversion. The
program reads the user’s answer and then executes an if-else statement. Each
branch of the if-else statement will be a function call. The two functions called
in the if-else statement will have function definitions that are very similar to
the programs for the previous two programming projects. Thus, they will be fairly
complicated function definitions that call other functions. Include a loop that lets
the user repeat this computation for new input values until the user says he or she
wants to end the program.
*/

#include <iostream>
#include <cassert>
#include <cmath>
#include <limits>
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::floor;
using std::round;

constexpr double METERS_FEET = 0.3048;
constexpr int INCHES_FEET = 12;
constexpr double METERS_INCH = METERS_FEET / INCHES_FEET;
constexpr int CM_METER = 100.0;

struct FeetInches {
    int feet = 0;
    int inches = 0;
};

struct MetersCentimeters {
    int meters = 0;
    int centimeters = 0;
};

void makeChoice(int& choice);

void getData(FeetInches& feetInches);

void getData(MetersCentimeters& metersCentimeters);

void convertData(const FeetInches& feetInches, MetersCentimeters& metersCentimeters);

void convertData(const MetersCentimeters& metersCentimeters, FeetInches& feetInches);


int main( ) {
    int choice;

    makeChoice(choice);
    switch (choice) {
        case 1: {
            FeetInches feetInches;
            MetersCentimeters metersCentimeters;
            getData(feetInches);
            convertData(feetInches, metersCentimeters);
            // TODO showData
            break;
        }
        case 2: {
            FeetInches feetInches;
            MetersCentimeters metersCentimeters;
            getData(metersCentimeters);
            convertData(metersCentimeters, feetInches);
            // TODO showData
            break;
        }
        case 0:
            cout << "Goodbye\n";
        default:
            break;
    }

    return 0;
}

void makeChoice(int& choice) {
    while (true) {
        cout << "Enter choice:\n"
         << "1. Convert feet inches to meters and cm\n"
         << "2. Convert meters and cm into feet inches\n"
         << "0. Exit\n"
         << "-----------------------------------------\n";
        if (!(cin >> choice)) {
            cout << "Wrong choice.\n\n";
            cin.clear();   // clear err flag and ignore line
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        // Read only choice, discard the remainder of line
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (choice >= 0 && choice <= 2)
            break;
        cout << "Wrong choice.\n\n";
    }
}

void getData(MetersCentimeters& metersCentimeters) {
    while (true) {
        cout << "Enter meters and centimeters: \n";
        if (!(cin >> metersCentimeters.meters
                     >> metersCentimeters.centimeters)) {
            cout << "Wrong Input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        // ignore the remainder of the input
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (metersCentimeters.meters >= 0 &&
            metersCentimeters.meters <= 2 &&
            metersCentimeters.centimeters >= 0 &&
            metersCentimeters.centimeters <= 99) {

            break;
        }
        cout << "Wrong Input.\n";
    }
}

void getData(FeetInches& feetInches) {
    while (true) {
        cout << "Enter feet and inches: \n";
        if (!(cin >> feetInches.feet
                     >> feetInches.inches)) {
            cout << "Wrong Input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
                     }
        // ignore the remainder of the input
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (feetInches.feet >= 0 &&
            feetInches.feet <= 7 &&
            feetInches.inches >= 0 &&
            feetInches.inches <= 11) {

            break;
            }
        cout << "Wrong Input.\n";
    }
}

void convertData(const FeetInches& feetInches, MetersCentimeters& metersCentimeters) {
    double totalMeters = METERS_FEET * feetInches.feet
                         + feetInches.inches * METERS_INCH;

    // round to nearest height
    int totalCentimeters = static_cast<int>(round(totalMeters * CM_METER));

    metersCentimeters.meters = totalCentimeters / CM_METER;
    metersCentimeters.centimeters = totalCentimeters % CM_METER;
}

void convertData(const MetersCentimeters& metersCentimeters, FeetInches& feetInches) {
    int totalCentimeters = metersCentimeters.meters * CM_METER
                           + metersCentimeters.centimeters;

    // trunc the inches to avoid overestimating height
    int totalInches = static_cast<int>(floor(static_cast<double>(totalCentimeters)
                                                    / (METERS_INCH * CM_METER)));

    feetInches.feet = totalInches / INCHES_FEET;
    feetInches.inches = totalInches % INCHES_FEET;
}
