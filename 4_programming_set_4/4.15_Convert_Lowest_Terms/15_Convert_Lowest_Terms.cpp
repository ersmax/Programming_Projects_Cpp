/*
Write a function named convertToLowestTerms that inputs two integer parameters
by reference named numerator and denominator. The function should treat
these variables as a fraction and reduce them to lowest terms. For example, if
numerator is 20 and denominator is 60, then the function should change the
variables to 1 and 3, respectively. This will require finding the greatest common
divisor for the numerator and denominator then dividing both variables by that
number. If the denominator is zero, the function should return false, otherwise the
function should return true. Write a test program that uses convertToLowestTerms
to reduce and output several fractions.
*/

#include <iostream>
#include <vector>
#include <limits>

void enterData(int& numerator, int& denominator);

bool convertToLowestTerms(int& numerator, int& denominator);

std::vector<int> findFactors(int number);

void findGCD(const int& numerator, const int& denominator, int& gcd);

void showResults(const int& numerator, const int& denominator);

int main( ) {
    int numerator, denominator;
    enterData(numerator, denominator);
    convertToLowestTerms(numerator, denominator);
    showResults(numerator, denominator);

    std::cout << "\n";
    return 0;
}

void enterData(int& numerator, int& denominator) {
    while (true) {
        std::cout << "Enter numerator and denominator:";
        if (!(std::cin >> numerator >> denominator)) {
            std::cout << "Wrong numbers.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        // ignore remaining input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (numerator >= 0 && denominator >= 0)
            break;
        std::cout << "Numbers must be positive.\n";
    }
}

void showResults(const int& numerator, const int& denominator) {
    std::cout << numerator << ", " << denominator;
    std::cout << "\n";
}

bool convertToLowestTerms(int& numerator, int& denominator) {
    if (denominator == 0)
        return false;

    int gcd = 1;
    findGCD(numerator, denominator, gcd);
    numerator /= gcd;
    denominator /= gcd;
    return true;
}


void findGCD(const int& numerator, const int& denominator, int& gcd) {
    std::vector<int> factorsNumerator = findFactors(numerator);
    std::vector<int> factorsDenominator = findFactors(denominator);
    if (factorsNumerator.empty() || factorsDenominator.empty())
        return;

    size_t p1 = 0, p2 = 0;
    while (p1 < factorsNumerator.size() && p2 < factorsDenominator.size()) {
        if (factorsNumerator[p1] == factorsDenominator[p2]) {
            gcd *= factorsNumerator[p1];
            ++p1;
            ++p2;
        } else if (factorsNumerator[p1] < factorsDenominator[p2])
            ++p1;
        else
            ++p2;
    }
}


std::vector<int> findFactors(int number) {
    int divisor = 2;
    std::vector<int> factors = {};
    while (number != 1) {
        if (number % divisor == 0) {
            factors.push_back(divisor);
            number /= divisor;
            continue;
        }
        divisor += 1;
    }
    return factors;
}
