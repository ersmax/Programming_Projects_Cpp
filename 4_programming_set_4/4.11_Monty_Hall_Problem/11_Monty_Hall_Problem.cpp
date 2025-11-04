/*
You are a contestant on a game show and have won a shot at the grand prize.
Before you are three doors. $1,000,000 in cash has randomly been placed behind
one door. Behind the other two doors are the consolation prizes of dishwasher detergent.
The game show host asks you to select a door, and you randomly pick one.
However, before revealing the prize behind your door, the game show host reveals
one of the other doors that contains a consolation prize. At this point, the game
show host asks if you would like to stick with your original choice or to switch to
the remaining door.
Write a function to simulate the game show problem. Your function should randomly
select locations for the prizes, select a door at random chosen by the contestant,
and then determine whether the contestant would win or lose by sticking with
the original choice or switching to the remaining door. You may wish to create
additional functions invoked by this function.

Next, modify your program so that it simulates playing 10,000 games. Count the
number of times the contestant wins when switching versus staying. If you are
the contestant, what choice should you make to optimize your chances of winning
the cash, or does it not matter?
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;

constexpr int DOORS = 3;

void randomDoorPrice(int& winningDoor);

void makeChoiceDoor(int& selectedDoor);

int main( ) {
    int winningDoor, selectedDoor;

    randomDoorPrice(winningDoor);
    makeChoiceDoor(selectedDoor);
}

void randomDoorPrice(int& winningDoor) {
    // seed the C library pseudorandom generator
    // time(nullptr) returns current time
    // case the result to unsigned required by srand
    srand(static_cast<unsigned>(time(nullptr)));
    winningDoor = rand( ) % DOORS + 1;
}

void makeChoiceDoor(int& selectedDoor) {
    while (true) {
        cout << "Enter the door (1-" << DOORS << ")\n";
        if (!cin >> selectedDoor) {
            cout << "Invalid selection.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // read first number, ignore the rest


    }
}

