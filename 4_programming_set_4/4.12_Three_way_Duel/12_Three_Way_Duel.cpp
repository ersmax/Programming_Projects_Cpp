/*
In the land of Puzzlevania, Aaron, Bob, and Charlie had an argument over which
one of them was the greatest puzzle-solver of all time. To end the argument once
and for all, they agreed on a duel to the death. Aaron was a poor shot and only hit
his target with a probability of 1/3. Bob was a bit better and hit his target with a
probability of 1/2. Charlie was an expert marksman and never missed. A hit means
a kill and the person hit drops out of the duel.
To compensate for the inequities in their marksmanship skills, the three decided
that they would fire in turns, starting with Aaron, followed by Bob, and then by
Charlie. The cycle would repeat until there was one man standing. That man
would be remembered for all time as the Greatest Puzzle-Solver of All Time.
An obvious and reasonable strategy is for each man to shoot at the most accurate
shooter still alive, on the grounds that this shooter is the deadliest and has the best
chance of hitting back.
Write a program to simulate the duel using this strategy. Your program should use
random numbers and the probabilities given in the problem to determine whether
a shooter hits his target. You will likely want to create multiple subroutines and
functions to complete the problem. Once you can simulate a duel, add a loop to
your program that simulates 10,000 duels. Count the number of times that each
contestant wins and print the probability of winning for each contestant (e.g., for
Aaron your program might output “Aaron won 3595/10,000 duels or 35.95%”).
An alternate strategy is for Aaron to intentionally miss on his first shot. Modify the
program to accommodate this new strategy and output the probability of winning
for each contestant. What strategy is better for Aaron, to intentionally miss on the
first shot or to try and hit the best shooter?
*/

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <random>
#include <vector>
#include <string>
#include <utility>
#include <numeric>
using std::vector;
using std::pair;
using std::string;
using std::cout;
using std::bernoulli_distribution;
using std::showpoint;
using std::fixed;
using std::setprecision;
using std::iota;
using std::sort;
using std::setfill;
using std::setw;

constexpr double AARON_SKILLS = 1.0/3.0;
constexpr double BOB_SKILLS = 0.5;
constexpr double CHARLIE_SKILLS = 1.0;

constexpr int GAMES = 10000;

std::random_device rd;
std::mt19937 rng(rd());

void gameStart(vector<pair<string, double> >& participants);

void orderShoot(vector<pair<string, double> >& participants);

bool oneLeft(const vector<pair<string, double> >& participants);

void gameRound(vector<pair<string, double> >& participants, bool bias);

void addStats(const vector<pair<string, double> >& participants,
              vector<pair<string, int> >& winStats);

void showStats(const vector<pair<string, int> >& winStats, bool bias);

void eraseStats(vector<pair<string, int> >& vectorPlayers);

int main( ) {
    cout << fixed << showpoint << setprecision(2);
    vector<pair<string, double> > participants;
    vector<pair<string, int> > winStats;
    vector<pair<string, int> > winStatsBiased;

    // Strategy 1: Aaron hits at first shot
    for (int game = 0; game < GAMES; ++game ) {
        gameStart(participants);
        while (!oneLeft(participants)) {
            gameRound(participants, false);
        }
        addStats(participants, winStats);
    }
    showStats(winStats, false);

    // Strategy 2: Aaron intentionally misses first shot
    for (int game = 0; game < GAMES; ++game ) {
        gameStart(participants);

        size_t initial_size = participants.size();
        while (initial_size == participants.size())
            gameRound(participants, true);
        while (!oneLeft(participants)) {
            gameRound(participants, false);
        }
        addStats(participants, winStatsBiased);
    }
    showStats(winStatsBiased, true);



    cout << "\n";
    return 0;
}


void gameStart(vector<pair<string, double> >& participants) {
    // clean list each game
    participants.clear();
    participants.emplace_back("Aaron", AARON_SKILLS);
    participants.emplace_back("Bob", BOB_SKILLS);
    participants.emplace_back("Charlie", CHARLIE_SKILLS);
    orderShoot(participants);
}

void orderShoot(vector<pair<string, double> >& participants) {
    if (participants.size() < 2) return;

    for (size_t idx1 = 0; idx1 < participants.size() - 1; ++idx1) {

        size_t bestShooterId = idx1;
        double bestShooterStats = participants[idx1].second;

        for (size_t idx2 = idx1 + 1; idx2 < participants.size(); ++idx2) {
            if (participants[idx2].second < bestShooterStats) {
                bestShooterId = idx2;
                bestShooterStats =  participants[idx2].second;
            }
        }
        if (bestShooterId != idx1)
            participants[idx1].swap(participants[bestShooterId]);
    }
}

bool oneLeft(const vector<pair<string, double> >& participants) {
    return (participants.size() == 1);
}

void gameRound(vector<pair<string, double> >& participants, const bool bias) {
    if (participants.size() < 2) return;

    // set starting player depending on Aaron missing (biased) or hitting
    size_t nPlayer = (bias == true) ? 1 : 0;

    while (nPlayer < participants.size()) {
        bernoulli_distribution hit(participants[nPlayer].second);
        if (!hit(rng)) {
            // missed shot
            ++nPlayer;
            continue;
        }

        // Players shoot in order of skills (ascending).
        // Kill the most lethal (last) then second to last, etc.
        const size_t mostLethal = participants.size() - 1;
        const size_t target = (nPlayer == mostLethal) ? nPlayer - 1 : mostLethal;

        // most lethal is shot
        using diff_t = vector<pair<string, double>>::difference_type;
        participants.erase(participants.begin() + static_cast<diff_t>(target));

        if (bias)       // if Aaron doesn't shoot at first (bias),
            return;     // he starts when one participant dies

        // if we removed element before current shooter,
        // current shooter's index decreased by 1
        if (target < nPlayer) --nPlayer;

        if (participants.size() < 2) break;

        ++nPlayer;
    }
}


void addStats(const vector<pair<string, double> >& participants, vector<pair<string, int> >& winStats) {
    if (participants.empty()) return;

    const string& winner = participants.front().first;

    for (auto& entry : winStats)
        if (entry.first == winner) {
            ++entry.second;
            return;
        }

    winStats.emplace_back(winner, 1);
}

void showStats(const vector<pair<string, int> >& winStats, const bool bias) {
    // avoid copying strings, but sort the indices only

    vector<size_t> indices(winStats.size());
    iota(indices.begin(), indices.end(), 0);

    sort(indices.begin(), indices.end(),
        [&](const size_t pair1, const size_t pair2) {
            return (winStats[pair1].first < winStats[pair2].first);
            });
    if (bias)
        cout << setfill('-') << setw(50) << "" << setfill(' ') << "\n"
             << "Biased game (Aaron misses intentionally first)\n";

    for (size_t idx : indices) {
        double stats = static_cast<double>(winStats[idx].second) / GAMES;
        cout << winStats[idx].first << " won "
             << winStats[idx].second << "/"
             << GAMES << " duels or "
             << stats * 100.0 << "%\n";
    }
}

void eraseStats(vector<pair<string, int> >& vectorPlayers) {
    vectorPlayers = vector<pair<string, int> >();
}
