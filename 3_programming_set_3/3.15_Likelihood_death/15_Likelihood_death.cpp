/*
The Social Security Administration maintains an actuarial life table that contains
the probability that a person in the United States will die (http://www.ssa.gov/
OACT/STATS/table4c6.html). The death probabilities for 2009 are stored in the
file LifeDeathProbability.txt, which is included on the website for the book.
There are three values for each row: the age, the death probability for a male, and
the death probability for a female. For example, the first five lines are
0 0.006990 0.005728
1 0.000447 0.000373
2 0.000301 0.000241
3 0.000233 0.000186
4 0.000177 0.000150
The interpretation for the fourth line is that a 3-year-old female has a 0.000186
chance of dying during year 3 to 4.
Write a program that inputs an age and sex from the keyboard in the main function.
The main function should call a function named simulate (that you must
write), sending in the age and sex as parameters. The function should simulate to
what age a person will live by starting with the death probability for the given age
and sex. You can do this by reading the data from the file row by row. Skip rows
that are less than the input age. Once the input age is reached, generate a random
number between 0 and 1, and if this number is less than or equal to the corresponding
death probability, then predict that the person will live to the current age
and return that age. If the random number is greater than the death probability,
then increase the age by one and repeat the calculation for the next row in the file.
If the simulation reaches age 120, then stop and predict that the user will live to
120. The main function should output the simulated age at which the person will
die. This program is merely a simulation and will give different results each time it
is run, assuming you change the seed for the random number generator.
*/

// 1. Openfile
// 2. Save it into two arrays
// 3. Write the functions

/*
Yes — the idea is correct. Brief checklist and clarifications:
Data: read LifeDeathProbability.txt (age, maleProb, femaleProb). You can either load into two std::vector<double> (and an age vector) or stream through the file on each simulation.
Input/validation: accept an integer age and a sex flag ('M'/'F'), validate ranges (0..120) and handle bad cin with cin.clear() and cin.ignore(numeric_limits<streamsize>::max(), '\n');.
Simulation (simulate(age, sex)):
Start reading rows, skipping until the input age row.
For each row from current age up to 120:
generate a uniform random number in [0,1) (use std::mt19937 + std::uniform_real_distribution<double>).
if random <= deathProbability(for sex at that age) then return that age (the person dies during that year).
otherwise increment age and continue.
If you reach 120, return 120.
Edge cases:
If input age > max age in file, treat as 120 or return input age per your requirement.
Seed RNG once (e.g., std::random_device or fixed seed for reproducible tests).
Use std::isnan only if you choose to signal errors with NaN; otherwise prefer exceptions or sentinel return values.
Implementation notes:
Prefer reading file once into memory if you will run many simulations.
Keep stopping condition consistent: death during year at age A means return A (not A+1).
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

const string PATH = "likelihood_death_2025.txt";

void readFile(const string& path, vector<double>& male, vector<double>& female);

int main( ) {
    // TODO
    return 0;
}


void readFile(const string &path, vector<double> &male, vector<double> &female) {
    string line;
    ifstream inputStream;
    istringstream iss;
    string field;
    vector<string> token;
    int age;
    double maleDeathProbability, femaleDeathProbability;

    inputStream.open(PATH);

    if (!inputStream)
        return;

    // skip header
    if (!getline(inputStream, line))
        return;

    // read rows
    while (inputStream >> line) {


        if (line.empty())
            continue;

        iss.open(line);

        while (iss >> field)
            token.push_back(field);

        if (token.size() < 5)
            continue;

        try {
            age = stoi(token[0]);
        } catch (...) {
            continue;
        }

        try {
            maleDeathProbability = stod(token[1]);
        } catch (...) {
            maleDeathProbability = 
        }

    }

    inputStream.close();
}



