/*
One way to estimate the height of a child is to use the following formula, which
uses the height of the parents:
Hmale_child = ((Hmother 13/12) + Hfather)/2
Hfemale_child = ((Hfather 12/13) + Hmother)/2
All heights are in inches. Write a function that takes as input parameters the gender
of the child, height of the mother in inches, and height of the father in inches,
and outputs the estimated height of the child in inches. Embed your function in a
program that allows you to test the function over and over again until telling the
program to exit. The user should be able to input the heights in feet and inches,
and the program should output the estimated height of the child in feet and inches.
Use the integer data type to store the heights.
*/
#include <iostream>
using namespace std;

double estimatedHeight(char gender, int motherHeight, int fatherHeight);
// Precondition: Gender is either

int main( ) {
    char answer, gender;
    int feetFather, inchesFather, feetMother, inchesMother;
    int feetChild, inchesChild;

    do {
        // Input validation father
        while (true) {
            cout << "Enter the height on the father in feet and inches (separated by space):";
            cin >> feetFather >> inchesFather;
            if (feetFather < 5 || feetFather > 7 || inchesFather < 0 || inchesFather > 11)
                cerr << "Error: Feet must be between 5 and 7, inches between 0 and 11.\n";
            else
                break;
        }
        // Input validation mother
        while (true) {
            cout << "Enter the height on the mother in feet and inches (separated by space):";
            cin >> feetMother >> inchesMother;
            if (feetMother < 5 || feetMother > 7 || inchesMother < 0 || inchesMother > 11)
                cerr << "Error: Feet must be between 5 and 7, inches between 0 and 11.\n";
            else
                break;
        }
        // Input validation gender
        while (true) {
            cout << "Enter the gender of the child (M/F):";
            cin >> gender;
            if (gender != 'M' && gender != 'F')
                cerr << "Wrong gender value. Retry.\n";
            else
                break;
        }

        double result = estimatedHeight(gender,
                                        feetMother * 12 + inchesMother,
                                        feetFather * 12 + inchesFather);

        feetChild = static_cast<int>(result/12);
        inchesChild = static_cast<int>(result) % 12;

        cout << "Height of the child will be: "
             << feetChild << " feet and "
             << inchesChild << " inches.\n";
        cout << "Continue (y/Y)?";
        cin >> answer;
    } while (answer == 'y' && answer == 'Y');

    cout << endl;
    return 0;
}

double estimatedHeight(char gender, int motherHeight, int fatherHeight) {
    double hChild;

    if (gender == 'M')
        hChild = ((motherHeight * 13/12.0) + fatherHeight) / 2;
    else
        hChild = ((fatherHeight * 12/13.0) + motherHeight) / 2;

    return hChild;
}

