/*
Write a program that accepts input like the program in Display 5.4 (repository Playgroud 5_0_4)
and that outputs a bar graph like the one in that program, except that your program will
output the bars vertically rather than horizontally. A two-dimensional array may
be useful.
*/

#include <iostream>
#include <sstream>
#include <string>

constexpr int PLANTS = 4;

void enterData(int production[], int nPlants);

void getTotal(int& production, int nPlant);

int main( ) {
    int production[PLANTS];
    enterData(production, PLANTS);

    std::cout << "\n";
    return 0;
}


void enterData(int production[], const int nPlants) {
    for (int idx = 0; idx < nPlants; ++idx) {
        std::cout << "Production for plant #"
                  << idx + 1 << ":\n";
        getTotal(production[idx], idx+1);
    }
}

void getTotal(int& production, int nPlant) {
    production = 0;
    std::string line;
    while (true) {
        std::cout << "Enter production of Plant " << nPlant
                  << " for each line separated by space or comma."
                     "(-1 to exit)\n";
        // EOF or input error
        if (!std::getline(std::cin, line)) {
            std::cout << "End of input\n";
            return;
        }
        // Replace any non-digit char with space
        for (char& c : line) {
            auto uc = static_cast<unsigned char>(c);        // portability
            if (!std::isdigit(uc) && c != '-' && !std::isspace(uc))
                c = ' ';
        }

        std::istringstream iss(line);
        int val;
        bool terminate = false;
        while (iss >> val) {
            if (val == -1) {
                terminate = true;
                break;
            }
            if (val < 0) continue;  // Production cannot be negative
            production += val;
        }

        std::cout << "Current total production Plant " << nPlant
                  << ": " << production << "\n";
        if (terminate) break;
    }
}
