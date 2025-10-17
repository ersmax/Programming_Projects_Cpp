/*
The game of Pig is a simple two player dice game in which the first player to
reach 100 or more points wins. Players take turns. On each turn a player rolls a
six-sided die:
• If the player rolls a 2–6 then he or she can either
— ROLL AGAIN or
— HOLD. At this point the sum of all rolls made this turn is added to the
player’s total score and it becomes the other player’s turn.
• If the player rolls a 1 then the player loses his or her turn. The player gets no
new points and it becomes the opponent’s turn.
If a player reaches 100 or more points after holding then the player wins.
Write a program that plays the game of Pig, where one player is a human and the
other is the computer. Allow the human to input “r” to roll again or “h” to hold.
The computer program should play according to the following rule: keep rolling
on the computer’s turn until it has accumulated 20 or more points, then hold. Of
course, if the computer wins or rolls a 1 then the turn ends immediately. Allow the
human to roll first.
Write your program using at least two functions:
int humanTurn(int humanTotalScore);
int computerTurn(int computerTotalScore);
These functions should perform the necessary logic to handle a single turn for
either the computer or the human. The input parameter is the total score for the
human or computer. The functions should return the turn total to be added to the
total score upon completion of the turn. For example, if the human rolls a 3 and 6
and then holds, then humanTurn should return 9. However, if the human rolls a 3
and 6 and then a 1, then the function should return 0.
*/


#include <iostream>
#include <cstdlib>  // rand & srand
#include <ctime>    // srand
#include <limits>   // input validation
using namespace std;

constexpr int GOAL = 100;

int humanTurn(int humanTotalScore);

int computerTurn(int computerTotalScore);

int main( ) {

    // seeds the C library pseudorandom generator
    // time(nullptr) returns current time
    // cast the result to unsigned required by srand
    srand(static_cast<unsigned>(time(nullptr)));
    int humanScore = 0, computerScore = 0;
    string dummy;

    cout << "Press enter to start the game.\n";
    getline(cin, dummy);

    while (true) {
        cout << "Player turn.\n";
        humanScore += humanTurn(humanScore);
        if (humanScore >= GOAL) {
            cout << "Congrats, you won!\n";
            break;
        }

        cout << "Computer turn.\n";
        computerScore += computerTurn(computerScore);
        if (computerScore >= GOAL) {
            cout << "Game over. Computer won.\n";
            break;
        }
    }

    return 0;
}

int humanTurn(int humanTotalScore) {
    int roll, turnPoints = 0;
    char answer;

    while (true) {
        roll = rand( ) % 6 + 1;
        cout << "Face on the dice: " << roll <<  "\n";

        // Trivial case
        if (roll == 1) {
            cout << "Tough luck. All points this turn are lost!\n"
                 << "----------------\n";
            return 0;
        }

        turnPoints += roll;
        cout << "Turn points: " << turnPoints << "\n"
             << "Total if held: " << (humanTotalScore + turnPoints) << endl
             << "----------------\n";

        if (humanTotalScore + turnPoints >= GOAL)
            cout << "Congratulations, you reached " << GOAL << " points";

        // Input validation
        while (true) {
            cout << "Roll again (r) or hold (h)? ";
            // Extract the next non-whitespace character,
            // discards everything up to the next newline \n.
            // In case of errors, clean the stream.
            if (!(cin >> answer)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Input error. Please enter \"r\" or \"h\"\n.";
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (answer == 'r' || answer == 'R')
                break;
            if (answer == 'h' || answer == 'H' )
                return turnPoints;
            cerr << "Invalid input. Please enter \"r\" or \"h\".\n";
        }
    // Outer loop: continue rolling
    }
}

int computerTurn(int computerTotalScore) {
    int turnPoint = 0, roll;

    do {
        roll = rand() % 6 + 1;
        cout << "Computer rolled " << roll << endl;
        if (roll == 1) {
            cout << "Turn points by computer: 0.\n"
                 << "Tot. points by computer: "
                 << computerTotalScore << endl
                 << "----------------\n";;
            return 0;
        }
        turnPoint += roll;
    } while (turnPoint < 20 && computerTotalScore + turnPoint < GOAL);

    cout << "Turn points by computer: " << turnPoint << endl
         << "Tot. points by computer: " << turnPoint + computerTotalScore << endl
         << "----------------\n";

    return turnPoint;
}
