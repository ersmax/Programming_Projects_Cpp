/*
Write a program that will read a weight in pounds and ounces and will output
the equivalent weight in kilograms and grams. Use at least three functions: one
for input, one or more for calculating, and one for output. Include a loop that lets
the user repeat this computation for new input values until the user says he or she
wants to end the program. There are 2.2046 pounds in a kilogram, 1000 grams in
a kilogram, and 16 ounces in a pound.
*/
// define NDEBUG
#include <iomanip>
#include <iostream>
#include <limits>
using std::cin;
using std::cout;
using std::numeric_limits;
using std::streamsize;
using std::fixed;
using std::showpoint;
using std::showpoint;

constexpr double POUNDS_KILO = 2.2046;
constexpr int OUNCES_POUND = 16;
constexpr double OUNCES_KILO = POUNDS_KILO * OUNCES_POUND;
constexpr int GRAMS_KILO = 1000;

void getData(int& pound, int& ounce);

void transformData(int pound, int ounce, int& kilo, double& grams);

void showData()

int main( ) {
    char answer;
    int pound, ounce, kilo;
    double grams;

    do {
        getData(pound, ounce);
        transformData(pound, ounce, kilo, grams);
        cout << fixed << std::setprecision(0);
        cout << kilo << " " << grams << '\n';
        cout << "Continue (y/Y)?: ";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (answer == 'y' || answer == 'Y');
}

void getData(int& pound, int& ounce) {
    while (true) {
        cout << "Enter the weight in pounds and ounces (separated by a space):";
        if (!(cin >> pound >> ounce)) {
            cout << "Wrong input\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore input after pound and ounce
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pound >= 0 && ounce >= 0)
            break;

        cout << "Weight must be greater than 0.\n";
    }
}

void transformData(int pound, int ounce, int& kilo, double& grams) {
    int totalOunce = pound * OUNCES_POUND + ounce;
    double totalKilos = totalOunce / OUNCES_KILO;
    double totalGrams = totalKilos * GRAMS_KILO;

    kilo = static_cast<int>(totalGrams / GRAMS_KILO);
    grams = totalGrams - static_cast<double>(kilo * GRAMS_KILO);
}
