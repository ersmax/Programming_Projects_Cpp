/*
Write a program like that of the previous exercise that converts from kilograms and
grams into pounds and ounces. Use functions for the subtasks.
*/

#include <iostream>
#include <limits>
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;

void getData(int& kilograms, double& grams);

int main( ) {
    char answer;
    int kilograms, pounds, ounces;
    double grams;

    do {
        getData(kilograms, grams);

        cout << "Repeat (y/Y)?:";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (answer == 'y' || answer == 'Y');

    return 0;
}

void getData(int& kilograms, double& grams) {
    while (true) {
        cout << "Enter kilo and grams separated by a space:";
        if (!(cin >> kilograms >> grams)) {
            cout << "Wrong values.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // read only kilo and grams, ignore the rest
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (kilograms >= 0 || grams >= 0)
            break;

        cout << "Weight cannot be negative.\n";
    }
}
