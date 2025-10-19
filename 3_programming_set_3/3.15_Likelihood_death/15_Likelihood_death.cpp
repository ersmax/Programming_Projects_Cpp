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
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <windows.h>
using namespace std;
namespace fs = std::filesystem;

const string PATH = "3_programming_set_3/3.15_Likelihood_death/likelihood_death_2025.txt";

const int MAX_AGE = 120;

string commaRemoval(const string& word);
//
// Postcondition: remove commas for stoi and stod

bool readFile(const string& path, vector<double>& male, vector<double>& female);

int simulate(int age, char gender, vector<double>& male, vector<double>& female);

int main( ) {
    // seed the C library pseudorandom generator
    //      time(nullptr) returns system time
    //      cast result to uns int required by srand
    srand(static_cast<unsigned int>(time(nullptr)));
    int age;
    char gender;
    vector<double> male, female;

    cout << "Curret working directory: "
         << fs::current_path() << endl;
    
    if (!readFile(PATH, male, female)) return -1;

    cout << "Enter age: ";
    cin >> age;
    cout << "Enter gender (M/F):";
    cin >> gender;

    age = simulate(age, gender, male, female);
    cout << "The expected age for this person is: "
         << age << endl;

    return 0;
}


string commaRemoval(const string &word) {
    string out;
    out.reserve(word.size());           // pre-allocate space for performance
    for (char ch : word)
        if (ch != ',')
            out.push_back(ch);   // push_back won't reallocate
    return out;                         //    until capacity exceeded (performance)
}

bool readFile(const string &path, vector<double> &male, vector<double> &female) {
    string line, text;
    ifstream inputStream;
    int age;
    double maleDeathProbability, femaleDeathProbability;

    inputStream.open(path);

    if (!inputStream) {
        cerr << "Error: unable to open file: `"
             << path  << "`\n";
        return false;
    }

    if (!getline(inputStream, line)) return false; // skip header

    while (getline(inputStream, line)) {    // read rows

        if (line.empty()) continue;

        vector<string> lineFields;  // `container` of fields
        istringstream iss(line);    // create string stream to parse line

        while (iss >> text)
            lineFields.push_back(text);

        if (lineFields.size() < 5)  // at least 5 fields, or discard line
            continue;               //    (women death prob is 5th field)

        try {
            age = stoi(lineFields[0]);  // field age
        } catch (...) {
            continue;
        }

        try {
            maleDeathProbability = stod(lineFields[1]); // field likelihood death men
        } catch (...) {
            maleDeathProbability = 0.0;
        }

        try {
            femaleDeathProbability = stod(lineFields[4]); // field likelihood death women
        } catch (...) {
            femaleDeathProbability = 0.0;
        }

        if (age < 0)
            continue;

        if (age >= static_cast<int>(male.size()) ) {
            male.resize(age + 1, 0.0);
            female.resize(age + 1, 0.0);
        }

        male[age] = maleDeathProbability;
        female[age] = femaleDeathProbability;
    }

    inputStream.close();

    return true;
}

int simulate(int age, char gender, vector<double>& male, vector<double>& female) {
    double deathReference;
    bool isMale = (gender == 'M' || gender == 'm');
    if (age < 0) age = 0;
    if (age > MAX_AGE) age  = MAX_AGE;

    do {
        deathReference = isMale ? male[age] : female[age];
        // [0,1) random number
        double randomGenerator = static_cast<double>(rand( ))
                                / (static_cast<double>(RAND_MAX) + 1.0);

        if (randomGenerator <= deathReference) return age;

    } while (age < MAX_AGE);

    return MAX_AGE;
}
