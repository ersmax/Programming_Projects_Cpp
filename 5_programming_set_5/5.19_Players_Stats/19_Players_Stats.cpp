/*
Write a program that manages a list of up to ten players and their high scores in the
computer’s memory (not on disk as in Programming Project 18). Use two arrays
to manage the list. One array should store the player’s name, and the other array
should store the player’s high score. Use the index of the arrays to correlate the
names with the scores. In the next chapter you will learn a different way to organize
related data by putting them into a struct or class. Do not use a struct or class for
this program. Your program should support the following features:
a. Add a new player and score (up to ten players).
b. Print all player names and their scores to the screen.
c. Allow the user to enter a player name and output that player’s score or a message
if the player name has not been entered.
d. Allow the user to enter a player name and remove the player from the list.
Create a menu system that allows the user to select which option to invoke.
*/

#include <iostream>
#include <limits>
#include <iomanip>

constexpr int MAX = 10;

void menu(char& choice);
bool handleChoice(char choice, std::string names[],
                  int scores[], int maxSize, int& size);
void addPlayer(std::string names[], int scores[], int maxSize, int& size);
std::string enterName();
int enterScore();
void showPlayers(const std::string names[], const int scores[], int size);
void showStat(const std::string names[], const int scores[], int size);
void removePlayers(std::string names[], int scores[], int& size);
int findPlayer(const std::string& name, const std::string names[], int size);

int main( ) {
    char choice;
    std::string names[MAX];
    int scores[MAX], size = 0;
    while (true) {
        menu(choice);
        if (!handleChoice(choice, names, scores, MAX, size)) break;
    }
    std::cout << "\n";
    return 0;
}

void menu(char& choice) {
    std::cout << "MENU\n"
              << "a. Add a new player and score\n"
              << "b. Print player names and their scores\n"
              << "c. Show the score by searching the player name\n"
              << "d. Remove a player by typing the name\n"
              << "0. Exit the program\n\n"
              << "Make a choice:\n";
    std::string line;
    while (true) {
        if (!std::getline(std::cin, line)) {    // EOF
            choice = '0';
            return;
        }
        std::size_t first = 0;
        while (first < line.size() && std::isspace(line[first]))    ++first;
        char letter = static_cast<char>(std::tolower(line[first]));
        if ((letter >= 'a' && letter <= 'd') || letter == '0') {
            choice = letter;
            return;
        }
        std::cout << "Not a valid choice. Retry\n";
    }
}

bool handleChoice(const char choice, std::string names[],
                  int scores[], const int maxSize, int& size) {
    switch (choice) {
        case 'a':
            addPlayer(names, scores, maxSize, size);
            break;
        case 'b':
            showPlayers(names, scores, size);
            break;
        case 'c':
            showStat(names, scores, size);
            break;
        case 'd':
            removePlayers(names, scores, size);
            break;
        case '0':
            return false;
        default:
            break;
    }
    return true;
}

void addPlayer(std::string names[], int scores[], const int maxSize, int& size) {
    if (size >= maxSize) {
        std::cout << "Roster is full\n";
        return;
    }
    names[size] = enterName();
    scores[size++] = enterScore();
}

void showPlayers(const std::string names[], const int scores[], const int size) {
    std::cout << std::setw(2) << "#"
              << std::setw(25) << "Player"
              << std::setw(10) << "Score\n";
    for (int idx = 0; idx < size; ++idx)
        std::cout << std::setw(2)    << idx + 1
                  << std::setw(25)   << names[idx]
                  << std::setw(10)   << scores[idx] << "\n";
    std::cout << std::string(37, '-') << "\n";
}

void showStat(const std::string names[], const int scores[], const int size) {
    if (size < 0) {
        std::cout << "Rooster is empty\n";
        return;
    }
    const std::string player = enterName();
    const int playerRanked = findPlayer(player, names, size);
    if (playerRanked == -1)
        std::cout << "Player not found\n";
    else
        std::cout << names[playerRanked]    << "'s score: "
                  << scores[playerRanked]   << "\n";
}

void removePlayers(std::string names[], int scores[], int& size) {
    if (size < 0) {
        std::cout << "Rooster is empty\n";
        return;
    }
    const std::string player = enterName();
    const int playerRanked = findPlayer(player, names, size);
    if (playerRanked == -1) {
        std::cout << "Player not found\n";
        return;
    }
    for (int idx = playerRanked; idx < size - 1; ++idx) {
        names[idx] = names[idx + 1];
        scores[idx] = scores[idx + 1];
    }
    --size;
}

int findPlayer(const std::string& name, const std::string names[], const int size) {
    bool found = false;
    int idx;
    for (idx = 0; idx < size; ++idx)
        if (names[idx] == name) {
            found = true;
            break;
        }
    if (found)  return idx;
    return -1;
}

std::string enterName() {
    while (true) {
        std::cout << "Enter a name:\n";
        std::string name;
        if (!std::getline(std::cin, name)) { // EOF
            std::cin.clear();
            continue;
        }
        // trim
        while (!name.empty() && std::isspace(name.front()))
            name.erase(name.begin());
        while (!name.empty() && std::isspace(name.back()))
            name.pop_back();    // name.erase(name.back() - 1);
        if (name.empty()) {
            std::cout << "Name cannot be empty\n";
            continue;
        }
        return name;
    }
}

int enterScore() {
    int score;
    while (true) {
        std::cout << "Enter score:\n";
        if (!(std::cin >> score)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Wrong value\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (score < 0) {
            std::cout << "Score should be greater than 0.\n";
            continue;
        }
        return score;
    }
}
