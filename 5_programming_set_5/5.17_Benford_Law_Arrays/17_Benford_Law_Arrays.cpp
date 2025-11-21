/*
Programming Project 2.12 asked you to explore Benford’s Law. An easier way to
write the program is to use an array to store the digit counts. That is, count[0]
might store the number of times 0 is the first digit (if that is possible in your data
set), count[1] might store the number of times 1 is the first digit, and so forth.
Redo Programming Project 2.12 using arrays.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>

constexpr int DIGITS = 10;
const std::string PATH = "./5_programming_set_5/5.17_Benford_Law_Arrays/Utilities/benford.txt";

void readData(const std::string& path, int& totNumbers, int count[], int size);
bool openFile(const std::string& path, std::fstream& inputStream);
void closeFile(const std::string& path, std::fstream& inputStream);
void checkNumber(int number, int& totNumbers, int count[], int size);
void checkBenfordLaw(int totalNumbers, const int count[], int size);

int main( ) {
    int count[DIGITS] = {0};
    int totalNumbers = 0;
    readData(PATH, totalNumbers, count, DIGITS);
    checkBenfordLaw(totalNumbers, count, DIGITS);
    std::cout << "\n";
    return 0;
}

void readData(const std::string& path, int& totNumbers,
              int count[], const int size) {
    std::fstream inputStream;
    if (!openFile(path, inputStream)) {
        std::cerr << "Cannot open file\n";
        return;
    }
    std::string line;

    while(std::getline(inputStream, line)) {
        if (line.empty())   continue;
        std::istringstream iss(line);

        int number;
        while (iss >> number)
            checkNumber(number, totNumbers, count, size);
    }
    closeFile(path, inputStream);
}

void checkNumber(int number, int& totNumbers, int count[], const int size) {
    number = std::abs(number);
    ++totNumbers;
    const std::string s = std::to_string(number);
    int leadingDigit = s[0] - '0';
    if (leadingDigit >= 0 && leadingDigit < size)
        ++count[leadingDigit];
    // alternatively:
    // while (number >= 10) number /= 10;
    // if (number >= 0 && number < size)
    //    ++count[number];
}

bool openFile(const std::string& path, std::fstream& inputStream) {
    inputStream.open(path);
    if (!inputStream)
        return false;
    return true;
}

void closeFile(const std::string& path, std::fstream& inputStream) {
    inputStream.close();
}

void checkBenfordLaw(const int totalNumbers, const int count[], const int size) {
    if (totalNumbers == 0) {
        std::cout << "No numbers read.\n";
        return;
    }
    std::cout << std::fixed << std::showpoint << std::setprecision(1);
    for (int idx = 0; idx < size; ++idx) {
        const double ratio = static_cast<double>(count[idx]) / totalNumbers;
        const double percent = ratio * 100.0;
        std::cout << "#" << idx << ": " << std::setw(5) << percent << "%\n";
    }
}