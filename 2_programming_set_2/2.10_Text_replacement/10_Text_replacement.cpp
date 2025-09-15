/*
Create a text file that contains the text “I hate C++ and hate programming!” Write
a program that reads in the text from the file and outputs each word to the console
but replaces any occurrence of “hate” with “love.” Your program should work with
any line of text that contains the word “hate,” not just the example given in this
problem.
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main ( ) {
    string line;
    fstream inputStream;

    inputStream.open("99_Text_files/2_10_Text_replacement.txt");

    while (getline(inputStream, line)) {
        string word;
        istringstream iss(line);
        while (iss >> word) {
            if (word == "hate")
                word = "love";
            cout << word << " ";
        }
        cout << endl;
    }

    inputStream.close();

    return 0;
}