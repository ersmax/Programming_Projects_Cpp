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
#include <random>
#include <vector>
#include <algorithm>
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::vector;
using std::move;
using std::find;
using std::pair;

constexpr int DOORS = 5;

void randomDoorPrice(int& winningDoor);

void initialPick(int& choiceDoor);

void nextPick(const vector<pair<int, double> >& leftDoorsProbs, int& selectedDoor);

void startGame(vector<pair<int, double>>& leftDoorsProbs);

void removeLosingDoor(vector<pair<int, double> >& leftDoorsProbs,
                      int winningDoor,
                      int selectedDoor);

int main( ) {
    int winningDoor, selectedDoor, doorsLeft;
    vector<pair<int, double>> leftDoorsProbs;

    startGame(leftDoorsProbs);
    randomDoorPrice(winningDoor);
    cout << "Winning door: " << winningDoor << "\n";

    initialPick(selectedDoor);

    for (auto pair : leftDoorsProbs)
        cout << pair.first << " " << pair.second << "\t";
    cout << "\n";
    cout << "Selected door: " << selectedDoor << "\n";

    doorsLeft = leftDoorsProbs.size();
    while (doorsLeft > 2) {
        removeLosingDoor(leftDoorsProbs, winningDoor, selectedDoor);
        nextPick(leftDoorsProbs, selectedDoor);
        --doorsLeft;
        for (auto pair : leftDoorsProbs)
            cout << pair.first << " " << pair.second << "\t";
        cout << "\n";
        cout << "Selected door: " << selectedDoor << "\n";
    }
    nextPick(leftDoorsProbs, selectedDoor);

    for (auto pair : leftDoorsProbs)
        cout << pair.first << " " << pair.second << "\t";
    cout << "\n";
    cout << "Selected door: " << selectedDoor << "\n";






    for (auto pair : leftDoorsProbs)
        cout << pair.first << " " << pair.second << "\n";

    return 0;

}

void startGame(vector<pair<int, double> >& leftDoorsProbs) {
    double probabilities = 1.0 / DOORS;
    leftDoorsProbs.reserve(DOORS);
    for (int idx = 1; idx <= DOORS; ++idx)
        // associate door and probabilities
        leftDoorsProbs.emplace_back(idx, probabilities);
}

void randomDoorPrice(int& winningDoor) {
    // seed the C library pseudorandom generator
    // time(nullptr) returns current time
    // case the result to unsigned required by srand
    srand(static_cast<unsigned>(time(nullptr)));
    winningDoor = rand( ) % DOORS + 1;
}

void initialPick(int& choiceDoor) {
    choiceDoor = rand( ) % DOORS + 1;
}

void nextPick(const vector<pair<int, double> >& leftDoorsProbs, int& selectedDoor) {
    // choose among candidates that have higher probability
    //  pick the door(s) with max probability and break ties randomly
    double selectedDoorProb = -1.0;

    for (const auto& door : leftDoorsProbs) {
        if (door.first == selectedDoor) {
            selectedDoorProb = door.second;
            break;
        }
    }
    // find max probability among remaining doors
    double maxProb = -1.0;
    for (const auto& door : leftDoorsProbs) {
       if (door.first == selectedDoor)
           continue;
       if (door.second >= selectedDoorProb && door.second > maxProb)
           maxProb = door.second;
    }

    // collect doors with max probability and break ties randomly
    vector<int> bestDoors;
    for (const auto& door : leftDoorsProbs) {
        if (door.second == maxProb)
            bestDoors.push_back(door.first);
    }

    selectedDoor = bestDoors[rand() % bestDoors.size()];

}


void removeLosingDoor(vector<pair<int, double> >& leftDoorsProbs,
                      const int winningDoor,
                      const int selectedDoor) {

    if (leftDoorsProbs.size() <= 2)
        return;

    // build candidates in the original order
    vector<pair<int, double> > candidates;
    candidates.reserve(leftDoorsProbs.size());
    for (const auto& door : leftDoorsProbs)
        if (door.first != winningDoor && door.first != selectedDoor)
            candidates.push_back(door);

    if (candidates.empty())
        return;

    // pick losing door from candidates (excluding selected and winning doors)
    size_t pickIndex = rand() % candidates.size();
    int losingDoorId = candidates[pickIndex].first;
    double losingProb = candidates[pickIndex].second;

    // compute probability to redistribute - 2:
    // one is for remove losing door, and one for the selected door
    double probsRedistributed = losingProb / static_cast<double>(leftDoorsProbs.size()  - 2);

    // redistribute the probability of losing door to other (non-selected) doors,
    //  including the winning door
    for (auto& door : leftDoorsProbs)
        if (door.first != losingDoorId && door.first != selectedDoor)
            door.second += probsRedistributed;

    // erase the losing door by finding its iterator
    auto iterator = find_if(leftDoorsProbs.begin(), leftDoorsProbs.end(),
                            [&](const pair<int, double>& pair) {
                                return (pair.first == losingDoorId);
                            });

    if (iterator != leftDoorsProbs.end())
        leftDoorsProbs.erase(iterator);
}
