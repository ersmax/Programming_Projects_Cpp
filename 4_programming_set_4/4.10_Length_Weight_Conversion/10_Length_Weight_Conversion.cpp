/*
(You should do Programming Projects 4.6 and 4.9 before doing this programming
project.) Write a program that combines the functions of Programming
Projects 4.6 and 4.9. The program asks the user if he or she wants to convert
lengths or weights. If the user chooses lengths, then the program asks the user if
he or she wants to convert from feet and inches to meters and centimeters or from
meters and centimeters to feet and inches. If the user chooses weights, a similar
question about pounds, ounces, kilograms, and grams is asked. The program then
performs the desired conversion. Have the user respond by typing the integer 1 for
one type of conversion and 2 for the other. The program reads the user’s answer
and then executes an if-else statement. Each branch of the if-else statement
will be a function call. The two functions called in the if-else statement will
have function definitions that are very similar to the programs for Programming
Projects 4.6 and 4.9. Thus, these functions will be fairly complicated function
definitions that call other functions; however, they will be very easy to write by
adapting the programs you wrote for Programming Projects 4.6 and 4.9. Notice
that your program will have if-else statements embedded inside of if-else
statements, but only in an indirect way. The outer if-else statement will include
two function calls, as its two branches. These two function calls will each
in turn include an if-else statement, but you need not think about that. They
are just function calls and the details are in a black box that you create when you
define these functions. If you try to create a four-way branch, you are probably
on the wrong track. You should only need to think about two-way branches (even
though the entire program does ultimately branch into four cases). Include a loop
that lets the user repeat this computation for new input values until the user says
he or she wants to end the program.
*/

// #define NDEBUG       // uncomment this line to disable assertions
#include <cassert>      // for assert
#include <iostream>     // for cin, cout
#include <limits>       // for numeric_limits, streamsize
#include <cmath>        // for round
#include <iomanip>      // for setprecision
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::round;
using std::fixed;
using std::showpoint;
using std::setprecision;

constexpr double METERS_FEET = 0.3048;
constexpr int INCHES_FEET = 12;
constexpr double METERS_INCH = METERS_FEET / INCHES_FEET;
constexpr int CM_METER = 100;

constexpr double POUNDS_KILO = 2.2046;
constexpr int OUNCES_POUND = 16;
constexpr double OUNCES_KILO = POUNDS_KILO * OUNCES_POUND;
constexpr int GRAMS_KILO = 1000;

struct Choice {
    int lengthWeight = -1;  // 0: exit, 1: length,      2: weight
    int meterFeet = -1;     // 0: exit, 1: feet/meter,  2: meter/feet
    int kiloPound = -1;     // 0: exit, 1: pound/kg,    2: kg/pound
};

struct FeetInches {
    int feet = 0;
    int inches = 0;
};

struct MetersCentimeters {
    int meters = 0;
    int centimeters = 0;
};

struct PoundsOunces {
    int pounds = 0;
    double ounces = 0.0;
};

struct KilogramsGrams {
    int kilograms = 0;
    double grams = 0.0;
};

void makeChoice(Choice& choice);                        // orchestrator
// Precondition: choice is declared
// Postcondition: organise the top menu
//                and sub-menus function calls


void makeChoice(int& choiceMenu);                       // top-menu
// Precondition: choice is declared
// Postcondition: 1 if user wants to convert length,
//                2 if user wants to convert weight
//                0 to exit program

void makeChoice(const int& choiceMenu,                  // submenu
                int& choiceSubmenu);
// Precondition: choiceMenu is 1 (length) or 2 (weight)
// Postcondition: 1 convert from feet/inches to meters/centimeters
//                  or convert from pounds/ounces to kilograms/grams
//                2 convert from meters/centimeters to feet/inches
//                  or convert from kilograms/grams to pounds/ounces
//                0 to return to main menu

void getData(FeetInches& feetInches);
// Precondition: feetInches is declared
// Postcondition: defines the values of feet and inches

void getData(MetersCentimeters& metersCentimeters);
// Precondition: metersCentimeters is declared
// Postcondition: defines the values of meters and centimeters

void getData(PoundsOunces& poundsOunces);

void getData(KilogramsGrams& kilogramsGrams);

void convertData(const FeetInches& feetInches, MetersCentimeters& metersCentimeters);

void convertData(const MetersCentimeters& metersCentimeters, FeetInches& feetInches);

void convertData(const PoundsOunces& poundsOunces, KilogramsGrams& kilogramsGrams);

void convertData(const KilogramsGrams& kilogramsGrams, PoundsOunces& poundsOunces);

void showData(const FeetInches& feetInches, const MetersCentimeters& metersCentimeters);

void showData(const PoundsOunces& poundsOunces, const KilogramsGrams& kilogramsGrams);

int main ( ) {
    Choice choice;

    while (true) {
        makeChoice(choice);
        if (choice.lengthWeight == 0) break;            // menu termination
        if (choice.meterFeet == 0 ||                    // sub-menu termination
            choice.kiloPound == 0) continue;

        if (choice.lengthWeight == 1) {                 // outer if-else
            FeetInches feetInches;
            MetersCentimeters metersCentimeters;

            if (choice.meterFeet == 1) {                // inner if-else
                getData(feetInches);

                assert(feetInches.feet >= 0 &&
                       feetInches.inches >= 0);
                convertData(feetInches, metersCentimeters);
            }
            if (choice.meterFeet == 2) {
                getData(metersCentimeters);

                assert(metersCentimeters.meters >= 0 &&
                       metersCentimeters.centimeters >= 0);
                convertData(metersCentimeters, feetInches);
            }
            assert(metersCentimeters.meters >= 0 &&
                   metersCentimeters.centimeters >= 0);
            showData(feetInches, metersCentimeters);
        }
        if (choice.lengthWeight == 2) {                 // outer if-else
            PoundsOunces poundsOunces;
            KilogramsGrams kilogramsGrams;

            if (choice.kiloPound == 1) {                // inner if-else
                getData(poundsOunces);

                assert(poundsOunces.pounds >= 0 &&
                       poundsOunces.ounces >= 0);
                convertData(poundsOunces, kilogramsGrams);
            }
            if (choice.kiloPound == 2) {
                getData(kilogramsGrams);

                assert(kilogramsGrams.kilograms >= 0 &&
                       kilogramsGrams.grams >= 0);
                convertData(kilogramsGrams, poundsOunces);
            }

            assert(kilogramsGrams.kilograms >= 0 &&
                   kilogramsGrams.grams >= 0);
            showData(poundsOunces, kilogramsGrams);
        }
    }
    cout << '\n';
    return 0;
}


void makeChoice(Choice& choice) {
    makeChoice(choice.lengthWeight);                        // top-menu
    if (choice.lengthWeight == 1) {
        assert(choice.lengthWeight == 1);
        makeChoice(choice.lengthWeight, choice.meterFeet);  // length sub-menu
    }
    else if (choice.lengthWeight == 2) {
        assert(choice.lengthWeight == 2);
        makeChoice(choice.lengthWeight, choice.kiloPound);  // weight sub-menu
    }
}

void makeChoice(int& choiceMenu) {
    while (true) {
        cout << "Menu:\n"
             << "1. Convert length (feet & inches <-> meters & centimeters)\n"
             << "2. Convert weight (pounds & ounces <-> kilograms & grams)\n"
             << "0. Exit\n"
             << "Choice:";
        if (!(cin >> choiceMenu)) {
            cout  << "Invalid choice.\n\n";
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore remaining input
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "\n";

        if (choiceMenu == 0 || choiceMenu == 1 || choiceMenu == 2)
            break;

        cout << "Invalid choice.\n\n";
    }
}

void makeChoice(const int& choiceMenu, int& choiceSubmenu) {
    while (true) {
        if (choiceMenu == 1)
            cout << "Length menu:\n"
                 << "1. Convert feet & inches to meters and centimeters\n"
                 << "2. Convert meters & centimeters to feet & inches\n";
        if (choiceMenu == 2)
            cout << "Weight menu:\n"
                 << "1. Convert pounds & ounces to kilos and grams\n"
                 << "2. Convert kilo & grams to pounds & ounces\n";

        cout     << "0. Return to main menu\n"
                 << "Enter action:";

        if (!(cin >> choiceSubmenu)) {
            cout << "Invalid choice.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore remaining input after 1 or 2
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n";

        if (choiceSubmenu == 0 ||
            choiceSubmenu == 1 ||
            choiceSubmenu == 2)
            break;

        cout << "Invalid result.\n\n";
    }
}

void getData(MetersCentimeters& metersCentimeters) {
    while (true) {
        cout << "Enter meters and centimeters:";
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
            metersCentimeters.centimeters >= 0) {

            break;
            }
        cout << "Length must be positive.\n";
    }
}

void getData(FeetInches& feetInches) {
    while (true) {
        cout << "Enter feet and inches:";
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
            feetInches.inches >= 0)
            break;

        cout << "Length must be positive.\n";
    }
}

void getData(PoundsOunces& poundsOunces) {
    while (true) {
        cout << "Enter the weight in pounds and ounces (separated by a space):";
        if (!(cin >> poundsOunces.pounds >> poundsOunces.ounces)) {
            cout << "Wrong input\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore input after pound and ounce
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (poundsOunces.pounds >= 0 && poundsOunces.ounces >= 0)
            break;

        cout << "Weight must be greater than or equal to 0.\n";
    }
}

void getData(KilogramsGrams& kilogramsGrams) {
    while (true) {
        cout << "Enter kilo and grams separated by a space:";
        if (!(cin >> kilogramsGrams.kilograms >> kilogramsGrams.grams )) {
            cout << "Wrong values.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // read only kilo and grams, ignore the rest
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (kilogramsGrams.kilograms >= 0 && kilogramsGrams.grams >= 0)
            break;

        cout << "Weight cannot be negative.\n";
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

    int totalInches = static_cast<int>(round(static_cast<double>(totalCentimeters)
                                                    / (METERS_INCH * CM_METER)));

    feetInches.feet = totalInches / INCHES_FEET;
    feetInches.inches = totalInches % INCHES_FEET;
}

void convertData(const PoundsOunces& poundsOunces, KilogramsGrams& kilogramsGrams) {
    double totalOunce = poundsOunces.pounds * OUNCES_POUND + poundsOunces.ounces;
    double totalKilos = totalOunce / OUNCES_KILO;

    kilogramsGrams.kilograms = static_cast<int>(totalKilos);
    kilogramsGrams.grams = (totalKilos - kilogramsGrams.kilograms) * GRAMS_KILO;
}

void convertData(const KilogramsGrams& kilogramsGrams, PoundsOunces& poundsOunces) {
    double totalPounds = (kilogramsGrams.kilograms + kilogramsGrams.grams / GRAMS_KILO ) * POUNDS_KILO;
    poundsOunces.pounds = static_cast<int>(floor(totalPounds));
    poundsOunces.ounces = (totalPounds - poundsOunces.pounds) * OUNCES_POUND;
}

void showData(const FeetInches& feetInches, const MetersCentimeters& metersCentimeters) {
    cout << feetInches.feet << " feet, " << feetInches.inches << "\" are equivalent to "
         << metersCentimeters.meters << " meters and " << metersCentimeters.centimeters << " cm.\n\n";
}

void showData(const PoundsOunces& poundsOunces, const KilogramsGrams& kilogramsGrams) {
    cout << fixed << showpoint << std::setprecision(2);
    const char* kiloLabel = (kilogramsGrams.kilograms == 0 || kilogramsGrams.kilograms == 1) ?
                            "kilo" : "kilos";
    const char* gramLabel = (round(kilogramsGrams.grams) == 0 || round(kilogramsGrams.grams) == 1) ?
                            "gram" : "grams";
    const char* poundLabel = (poundsOunces.pounds == 0 || poundsOunces.pounds == 1) ?
                            "pound" : "pounds";
    const char* ounceLabel = (round(poundsOunces.ounces) == 0 || round(poundsOunces.ounces) == 1) ?
                            "ounce" : "ounces";
    cout << kilogramsGrams.kilograms << " " << kiloLabel << " "
         << kilogramsGrams.grams << " " << gramLabel << " "
         << " are equivalent to "
         << poundsOunces.pounds << " " << poundLabel << " "
         << poundsOunces.ounces << " " << ounceLabel << ".\n\n";
}
