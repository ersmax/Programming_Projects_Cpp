/*
Write a program that reads in the average mileage in kilometers per liter of a car
at 10 different speeds ranging from 10 kilometers per hour to 100 kilometers per
hour, and then reads in the actual mileage obtained for a test drive at each of the 10
speeds. The program then prints out a nicely formatted table showing the mileage
obtained during the 10 test drives and whether it was above or below the average
mileage at that speed, and by how much it varied. The average mileage should be
given for the 10 different speeds in 10 kmph steps. To obtain the mileage during
the test drives, the program repeatedly asks the user to enter the mileage for each
speed. The output should correctly label each speed.
After you have completed the previous program, produce an enhanced version
that also outputs a graph showing the average and actual mileage of the car at each
speed. The graph should be similar to the one shown in Playground repository, Display 5.0.4,
except that there should be two bars for each speed and they should be labeled as average and
actual mileage at each speed.
*/

#include <iostream>
#include <iterator>
#include <limits>
#include <iomanip>
#include <string>
#include <cmath>

constexpr int TESTS = 10;
constexpr int KMH = 10;
constexpr double SCALE_FACTOR = 10.0;

void fillEntry(double mileage[], std::size_t size);

void showTable(const double avgKm[],std::size_t sizeAvg,
               const double mileage[], std::size_t size);

void showGraph(double avgKm[],std::size_t sizeAvg,
               double mileage[], std::size_t size);

void scale(double numbers[],std::size_t size);

void printAsterisk(int number);

int main( ) {
    double avgKm[TESTS] = {40,39,36,34,33,31,29,26,25,24};
    double testDrive[TESTS];
    fillEntry(testDrive, std::size(testDrive));
    showTable(avgKm, std::size(avgKm), testDrive, std::size(testDrive));
    showGraph(avgKm, std::size(avgKm), testDrive, std::size(testDrive));
    std::cout << "\n";
    return 0;
}

void fillEntry(double mileage[], std::size_t size) {
    double next;
    for (int idx = 0; idx < size; ++idx) {
        std::cout << "Mileage (Km/l) for "
                  << (idx + 1) * KMH << " km/h:\n";
        while (true) {
            if (!(std::cin >> next )) {
                std::cout << "Not a number. Retry\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // discard rest of the input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if ((next > 0) && (next <= 50)) {
                mileage[idx] = next;
                break;
            }
            std::cout << "Mileage should be between 0-50\n";
        }
    }
}

void showTable(const double avgKm[], const std::size_t sizeAvg,
               const double mileage[], const std::size_t size) {

    std::cout << std::fixed << std::showpoint << std::setprecision(1);
    std::cout  << std::setw(10) << "Speed"
               << std::setw(8) << "Avg km/l"
               << std::setw(8) << "Test km/l"
               << std::setw(8) << "Diff"
               << std::setw(8) << "+/-"
               << "\n" ;

    for (std::size_t idx = 0; idx < size; ++idx) {
        std::string result;
        double diff = mileage[idx] - avgKm[idx];
        if (diff > 0) result = "above";
        else if (diff < 0) result = "below";
        else result = "equal";

        std::cout  << std::setw(5) << (idx + 1)* KMH << std::setw(5) << "km/h"
                   << std::setw(8) << avgKm[idx]
                   << std::setw(8) << mileage[idx]
                   << std::setw(8) << result
                   << std::setw(8) << diff
                   << "\n";
    }
}

void showGraph(double avgKm[], std::size_t sizeAvg,
               double mileage[], std::size_t size) {

    scale(avgKm, sizeAvg);
    scale(mileage, size);
    std::cout << "Mileage in km/l (in tens of units)\n";
    for (int idx = 0; idx < size; ++idx) {
        std::cout << "Speed: " << (idx + 1) * KMH << " km/h\n"
                  << std::setw(10) << "Average:";
        printAsterisk(static_cast<int>(avgKm[idx]));
        std::cout << "\n";
        std::cout << std::setw(10) << "Actual:";
        printAsterisk(static_cast<int>(mileage[idx]));
        std::cout << "\n";
    }
}

void scale(double numbers[], std::size_t size) {
    for (std::size_t idx = 0; idx < size; ++idx) {
        numbers[idx] = std::floor((numbers[idx] / SCALE_FACTOR) + 0.5);
    }
}

void printAsterisk(int number) {
    for (int count = 1; count <= number; ++count)
        std::cout  << "*";
}
