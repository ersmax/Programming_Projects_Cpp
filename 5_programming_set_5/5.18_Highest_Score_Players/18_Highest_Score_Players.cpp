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
#include <iomanip>
#include <algorithm>

constexpr int MAX = 1000;
constexpr int BEST = 3;
const std::string PATH = "./5_programming_set_5/5.18_Highest_Score_Players/Utilities/Scores.txt";

void copyData(std::string name[], int score[], int maxSize, int& nPlayers);
bool openFile(const std::string& pathFile, std::ifstream& inputStream);
void closeFile(std::ifstream& inputStream);
void parseFile(std::ifstream& inputStream,
               std::string name[], int score[], int maxSize, int& nPlayers);
void showBest(const std::string name[], const int score[], int size, int topPlayers);
void orderData(std::string name[], int score[], int size);
void merge(const int arr1[], const std::string name1[], int size1,
           const int arr2[], const std::string name2[], int size2,
           int result[], std::string names[], int totSize);
void mergeSort(std::string name[], int score[], int size);

int main( ) {
    std::string name[MAX];
    int score[MAX];
    int nPlayers = 0;
    copyData(name, score, MAX, nPlayers);
    orderData(name, score, nPlayers);
    showBest(name, score, nPlayers, BEST);

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

bool openFile(const std::string& pathFile, std::ifstream& inputStream) {
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

void orderData(std::string name[], int score[], const int size) {
    if (size <= 1) return;
    mergeSort(name, score, size);
}

void mergeSort(std::string name[], int score[], int size) {
    if (size <= 1) return;

    const int sizeLeft = size / 2;
    const int sizeRight = size - sizeLeft;
    int score1[MAX], score2[MAX];
    std::string name1[MAX], name2[MAX];

    std::copy_n(score, sizeLeft, score1);
    std::copy_n(name, sizeLeft, name1);
    // for (int idx = 0; idx < sizeLeft; ++idx) {
    //     score1[idx] = score[idx];
    //     name1[idx] = name[idx];
    // }
    std::copy_n(score + sizeLeft, sizeRight, score2);
    std::copy_n(name + sizeLeft, sizeRight, name2);
    // for (int idx = 0; idx < sizeRight; ++idx) {
    //     score2[idx] = score[sizeLeft + idx];
    //     name2[idx] = name[sizeLeft + idx];
    // }
    mergeSort(name1, score1, sizeLeft);
    mergeSort(name2, score2, sizeRight);
    merge(score1, name1, sizeLeft, score2, name2, sizeRight, score, name, size);
}

void merge(const int arr1[], const std::string name1[], const int size1,
           const int arr2[], const std::string name2[], const int size2,
           int result[], std::string names[], const int totSize) {

    int p1 = 0, p2 = 0, idx = 0;
    while ((p1 < size1) && (p2 < size2) && (idx < totSize)) {
        if (arr1[p1] >= arr2[p2]) {
            result[idx] = arr1[p1];
            names[idx] = name1[p1];
            ++p1;
        } else {
            result[idx] = arr2[p2];
            names[idx] = name2[p2];
            ++p2;
        }
        ++idx;
    }
    // Merge wrap-up
    while ((p1 < size1) && (idx < totSize)) {
        result[idx] = arr1[p1];
        names[idx] = name1[p1];
        ++p1;
        ++idx;
    }
    while ((p2 < size2) && (idx < totSize)) {
        result[idx] = arr2[p2];
        names[idx] = name2[p2];
        ++p2;
        ++idx;
    }
}

void showBest(const std::string name[], const int score[],
              const int size, const int topPlayers) {
    for (int idx = 0; idx < size; ++idx) {
        const bool highlight = (idx < topPlayers);
        if (highlight) std::cout << "*** ";
        else           std::cout << "    ";
        std::cout << "Player #" << std::setw(2) << idx + 1
                  << ": " << std::setw(12) << name[idx]
                  << ", score: " << std::setw(6) << score[idx];
        if (highlight) std::cout << " ***";
        std::cout << "\n";
    }
}
