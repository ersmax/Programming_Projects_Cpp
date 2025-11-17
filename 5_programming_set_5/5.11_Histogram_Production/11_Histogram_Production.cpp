/*
Write a program that accepts input like the program in Display 5.4 (repository Playgroud 5_0_4)
and that outputs a bar graph like the one in that program, except that your program will
output the bars vertically rather than horizontally. A two-dimensional array may
be useful.
*/

#include <iostream>

constexpr int PLANTS = 4;

void enterData(int production[], int nPlants);

void getTotal();

int main( ) {
    int production[PLANTS];
    enterData(production, PLANTS);

    std::cout << "\n";
    return 0;
}


void enterData(int production[], const int nPlants) {
    for (int idx = 0; idx < nPlants; ++idx) {
        getTotal(production[idx]);
    }
}
