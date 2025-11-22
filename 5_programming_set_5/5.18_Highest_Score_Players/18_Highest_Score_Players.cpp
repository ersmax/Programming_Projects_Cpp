/*
This project is an extension of Programming Project 4.16. Consider a text file
named scores.txt that contains player scores for a game. A possible sample is
shown next where Ronaldo’s best score is 10400, Didier’s best score is 9800, etc.
Put at least five names and scores in the file.
Ronaldo
10400
Didier
9800
Pele
12300
Kaka
8400
Cristiano
8000
Write a function named getHighScores that takes two array parameters, an array
of strings and an array of integers. The function should scan through the file and
set the string array entry at index 0 to the name of the player with the highest score
and set the integer array entry at index 0 to the score of the player with the highest
score. The string array entry at index 1 should be set to the name of the player with
the second highest score and the integer array entry at index 1 should be set to the
score of the player with the second highest score. Do the same for the entries at
index 2. Together, these two arrays give you the names and scores of the top three
players. In your main function, test the getHighScores function by calling it and
outputting the top three players and scores.
*/

#include <iostream>
#include <fstream>
#include <sstream>

constexpr int MAX = 1000;
const std::string PATH = "./5_programming_set_5/5.18_Highest_Score_Players/Utilities/Scores.txt";

void copyData(std::string name[], int score[], int maxSize, int& nPlayers);
bool openFile(const std::string& pathFile, std::ifstream& inputStream);
void closeFile(std::ifstream& inputStream);
void parseFile(std::ifstream& inputStream,
               std::string name[], int score[], int maxSize, int& nPlayers);

int main( ) {
    std::string name[MAX];
    int score[MAX];
    int nPlayers = 0;
    copyData(name, score, MAX, nPlayers);


    std::cout << "\n";
    return 0;
}

void copyData(std::string name[], int score[], const int maxSize, int& nPlayers) {
    std::ifstream inputStream;
    if (!openFile(PATH, inputStream)) {
        std::cerr << "Cannot open file\n";
        return;
    }
    parseFile(inputStream, name, score, maxSize, nPlayers);
    closeFile(inputStream);
}

bool openFile(const std::string& pathFile, std::fstream& inputStream) {
    inputStream.open(pathFile);
    if (!inputStream)
        return false;
    return true;
}

void closeFile(std::ifstream& inputStream) {
    inputStream.close();
}

void parseFile(std::ifstream& inputStream,
               std::string name[], int score[], const int maxSize, int& nPlayers) {
    nPlayers = 0;
    std::string nameLine, scoreLine;
    while (nPlayers < maxSize && std::getline(inputStream, nameLine)) {
        if (nameLine.empty())   continue;
        if (!std::getline(inputStream, scoreLine))  break;  // expect score in next line

        std::istringstream iss(scoreLine);
        int points;
        while (iss >> points) {
            name[nPlayers] = nameLine;
            score[nPlayers++] = points;
        }
    }
}

