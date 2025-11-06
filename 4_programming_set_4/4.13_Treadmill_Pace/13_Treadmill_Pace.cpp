/*
You would like to know how fast you can run in miles per hour. Your treadmill
will tell you your speed in terms of a pace (minutes and seconds per mile, such as
“5:30 mile”) or in terms of kilometers per hour (kph).
Write an overloaded function called convertToMPH. The first definition should
take as input two integers that represent the pace in minutes and seconds per mile
and return the speed in mph as a double. The second definition should take as
input one double that represents the speed in kph and return the speed in mph as
a double. One mile is approximately 1.61 kilometers. Write a driver program to
test your function.
*/

// define NDEBUG        // uncomment this line todisable assertions
#include <iostream>     // for cin, cout
#include <limits>       // for numeric_limits, streamsize

constexpr double KM_MILE = 1.61;

double convertToMPH(int& paceMinutesMile, int& paceSecondsMile);
// Precondition: paceMinutesMile and paceSecondsMile are non-negative
// Postcondition: returns speed in mph as a double

double convertToMPH(double speedKPH);
// Precondition: speedKPH is non-negative
// Postcondition: returns speed in mph as a double.
//                As side effect, seconds are normalized
//                (avoid 61 seconds, but 1 min 1 sec)

void enterData(int& paceMinutesMile, int& paceSecondsMile);
// Precondition: paceMinutesMile and paceSecondsMile are declared
// Postcondition: defines the values of paceMinutesMile and paceSecondsMile

int main( ) {
    int paceMinutesMile, paceSecondsMile;
    enterData(paceMinutesMile, paceSecondsMile);
    double speedMph = convertToMPH(paceMinutesMile, paceSecondsMile);
    double speedMph2 = convertToMPH(speedMph * KM_MILE);
    std::cout << speedMph << " mph or "
              << paceMinutesMile << "::"
              << paceSecondsMile
              << " min, seconds";
    std::cout << "\n";
    return 0;
}

void enterData(int& paceMinutesMile, int& paceSecondsMile) {
    while (true) {
        std::cout << "Enter pace in minutes and seconds per mile (separated by a space):";
        if (!(std::cin >> paceMinutesMile >> paceSecondsMile )) {
            std::cout << "Wrong input.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // read first two inputs, ignore the rest
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (paceMinutesMile >= 0 && paceSecondsMile >= 0)
            break;
        std::cout << "Enter valid number.\n";
    }
}

double convertToMPH(int& paceMinutesMile, int& paceSecondsMile) {
    paceMinutesMile += paceSecondsMile / 60;
    paceSecondsMile %= 60;
    const int totalSeconds = paceMinutesMile * 60 + paceSecondsMile;
    const double mph = 3600.0 / static_cast<double>(totalSeconds);
    return mph;
}

double convertToMPH(const double speedKPH) {
    return (speedKPH / KM_MILE);
}
