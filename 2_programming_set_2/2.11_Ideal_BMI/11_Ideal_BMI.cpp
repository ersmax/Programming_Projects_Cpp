/*
(This is an extension of an exercise from Chapter 1.) A simple rule to estimate
your ideal body weight is to allow 110 pounds for the first 5 feet of height and 5
pounds for each additional inch. Create the following text in a text file. It contains
the names and heights in feet and inches of Tom Atto (6'3"), Eaton Wright (5'5"),
and Cary Oki (5'11"):
Tom Atto
6
3
Eaton Wright
5
5
Cary Oki
5
11
Write a program that reads the data in the file and outputs the full name and ideal
body weight for each person. Use a loop to read the names from the file. Your
program should also handle an arbitrary number of entries in the file instead of
handling only three entries.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int idealBMI(const string& firstName, const string& lastName, int feet, int inch) {
    if (feet < 5 || feet >= 8) {
        cerr << firstName << " " << lastName << ": "
             << "Error. Height should be "
                "at least 5 or less than 8 inches.\n";
        return -1; // Return an error value
    }
    return 110 * 5 + (feet - 5) * 5 + (inch * 5);
}

int main ( ) {
    string firstName;
    fstream inputStream;

    inputStream.open("99_Text_files/2_11_Ideal_BMI.txt");

    if (!inputStream.is_open()) {
        cout << "Failed to open file." << endl;
        return -1;
    }

    while (inputStream >> firstName) {
        string lastName;
        int feet, inches;

        inputStream >> lastName
                    >> feet
                    >> inches;
        int BMI = idealBMI(firstName, lastName, feet, inches);

        if (BMI == -1)
            continue;

        cout << firstName  << " " << lastName
             << ", your ideal BMI is: "
             << BMI << endl;
    }

    inputStream.close();
    return 0;
}