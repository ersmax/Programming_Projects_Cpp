/*
The birthday paradox is that there is a surprisingly high probability that two people
in the same room happen to share the same birthday. By birthday, we mean the same
day of the year (ignoring leap years), but not the exact birthday including the birth
year or time of day. Write a program that approximates the probability that two
people in the same room have the same birthday, for 2 to 50 people in the room.
The program should use simulation to approximate the answer. Over many trials
(say, 5000), randomly assign birthdays to everyone in the room. Count up the
number of times at least two people have the same birthday, and then divide by
the number of trials to get an estimated probability that two people share the same
birthday for a given room size.
Your output should look something like the following. It will not be exactly the
same due to the random numbers:
For 2 people, the probability of two birthdays is about 0.002
For 3 people, the probability of two birthdays is about 0.0082
For 4 people, the probability of two birthdays is about 0.0163
. . .
For 49 people, the probability of two birthdays is about 0.9654
For 50 people, the probability of two birthdays is about 0.969
*/

#include <iostream>
#include <random>

constexpr int MAX_PEOPLE = 50;
constexpr int MAX_TRIALS = 5000;

struct Birthday {
    int month;
    int day;
    bool operator == (const Birthday& other) const {
        return (std::tie(month, day) == std::tie(other.month, other.day));
    }
};

void askBirthday(Birthday people[], int nPeople);

void randomBirthday(Birthday& birthday);

bool isSameBirthday(Birthday people[], int nPeople);

void showResults(const int sameBirthday[], int nPeople, int nTrials);

int main( ) {
    int trial = 0;
    int sameBirthday[MAX_PEOPLE - 1] = {};

    while (trial++ < MAX_TRIALS) {
        for (int peopleRoom = 2; peopleRoom <= MAX_PEOPLE; ++peopleRoom) {
            Birthday people[MAX_PEOPLE] = {};
            askBirthday(people, peopleRoom);
            if (isSameBirthday(people, peopleRoom))
                sameBirthday[peopleRoom - 2] += 1;
        }
    }

    showResults(sameBirthday, MAX_PEOPLE - 1, MAX_TRIALS);

    std::cout << "\n";
    return 0;
}

void askBirthday(Birthday people[], const int nPeople) {
    for (int idx = 0; idx < nPeople; ++idx)
        randomBirthday(people[idx]);
}

void randomBirthday(Birthday& birthday) {
    // use a single static seed the generator, so don't reseed every call
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> monthDistrib(1, 12);
    birthday.month = monthDistrib(rng);

    int maxDay = 31;
    if (birthday.month == 4 || birthday.month == 6 ||
        birthday.month == 9 || birthday.month == 11)
        maxDay = 30;
    else if (birthday.month == 2)
        maxDay = 28;

    std::uniform_int_distribution<int> dayDistrib(1, maxDay);
    birthday.day = dayDistrib(rng);
}

bool isSameBirthday(Birthday people[], int nPeople) {
    for (int p1 = 0; p1 < nPeople - 1; ++p1)
        for (int p2 = p1 + 1; p2 < nPeople; ++p2)
            if (people[p1] == people[p2]) return true;

    return false;
}

void showResults(const int sameBirthday[], const int nPeople, const int nTrials) {
    for (int idx = 0; idx < nPeople; ++idx) {
        std::cout << "For " << idx + 2 << " people, "
                  << "the probability of two birthdays is about "
                  << static_cast<double>(sameBirthday[idx]) / static_cast<double>(nTrials)
                  << "\n";
    }
}
