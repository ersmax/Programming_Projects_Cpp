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