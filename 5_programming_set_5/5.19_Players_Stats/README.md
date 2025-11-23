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

---

##  Alternative input validation
An alternative to input validation in `showMenu` could be:
However, this implementation works for simple input but has weaknesses: 
it reads a single token with operator>> (so multi-character input can be mishandled), 
doesn't accept uppercase, and doesn't handle EOF cleanly. 
The version that uses std::getline, trims leading whitespace, converts to lowercase, 
handles EOF by returning '0', and improve the logic of  showMenu(char& choice).

```cpp
void showMenu(char& choice) {
    std::cout << "a. Add a new player and score\n"
              << "b. Print player names and their scores\n"
              << "c. Show the score by searching the player name\n"
              << "d. Remove a player by typing the name\n"
              << "0. Exit the program\n\n"
              << "Make a choice:\n";

    char letter;
    while (true) {
        if (!(std::cin >> letter)) {
            std::cout << "Error in the choice\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
        if ((letter >= 'a' && letter <= 'd') || letter == '0') {
            choice = letter;
            break;
        }
        std::cout << "Not a valid choice.\n";
    }
}
```