/*
Traditional password entry schemes are susceptible to “shoulder surfing” in which
an attacker watches an unsuspecting user enter their password or PIN number and
uses it later to gain access to the account. One way to combat this problem is with
a randomized challenge-response system. In these systems, the user enters different
information every time based on a secret in response to a randomly generated challenge.
Consider the following scheme in which the password consists of a five-digit
PIN number (00000 to 99999). Each digit is assigned a random number that is
1, 2, or 3. The user enters the random numbers that correspond to their PIN instead
of their actual PIN numbers.
For example, consider an actual PIN number of 12345. To authenticate, the user
would be presented with a screen such as

| PIN | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|-----|---|---|---|---|---|---|---|---|---|---|
| NUM | 3 | 2 | 3 | 1 | 1 | 3 | 2 | 2 | 1 | 3 |

The user would enter 23113 instead of 12345. This does not divulge the password
even if an attacker intercepts the entry because 23113 could correspond to other
PIN numbers, such as 69440 or 70439. The next time the user logs in, a different
sequence of random numbers would be generated, such as

| PIN | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|-----|---|---|---|---|---|---|---|---|---|---|
| NUM | 1 | 1 | 2 | 3 | 1 | 2 | 2 | 3 | 3 | 3 |

Your program should simulate the authentication process. Store an actual PIN
number in your program. The program should use an array to assign random
numbers to the digits from 0 to 9. Output the random digits to the screen, input
the response from the user, and output whether or not the user’s response correctly
matches the PIN number.
*/

#include <iostream>
#include <random>
#include <string>
#include <limits>
#include <algorithm>


constexpr int NUMBERS = 3;
constexpr int DIGITS = 10;
constexpr int PIN = 5;
constexpr int GIVEN_PIN = 12345;

void createSequence(int sequence[], int size);
void shuffleSequence(int sequence[], int size);
void enterPin(int pin[], int nDigits);
void showSystem(const int sequence[], int size);
bool checkPin(const int pin[], int nDigitsPin, const int sequence[], int nDigits);

int main( ) {
    int sequence[DIGITS];
    int pin[PIN];

    createSequence(sequence, DIGITS);
    shuffleSequence(sequence, DIGITS);
    showSystem(sequence, DIGITS);
    enterPin(pin, PIN);
    if (checkPin(pin, PIN, sequence, DIGITS))
        std::cout << "Correct PIN\n";
    else
        std::cout << "Wrong PIN\n";

    std::cout << "\n";
    return 0;
}

void createSequence(int sequence[], const int size) {
    for (int idx = 0; idx < size; ++idx)
        sequence[idx] = ((idx + (NUMBERS - 1)) % NUMBERS) + 1;
}

void shuffleSequence(int sequence[], const int size) {
    static std::random_device rd;
    static std::mt19937 engine(rd());
    // Fisher-Yates randomization
    for (int idx = size - 1; idx > 0; --idx) {
        std::uniform_int_distribution<int>dist(0, idx);
        const int temp = dist(engine);
        std::swap(sequence[idx], sequence[temp]);
    }
}

void enterPin(int pin[], const int nDigits) {
    std::string number;
    std::cout << "Enter the PIN sequence:\n";
    while (true) {
        if (!(std::cin >> number)) {
            std::cout << "Wrong input. Retry\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // check bounds
        bool isValid = true;
        for (const char c : number)
            if (c < '1' || c > ('0' + NUMBERS)) {
                isValid = false;
                break;
            }
        // check length
        if (number.size() != nDigits) {
            std::cout << "PIN must be " << nDigits << " digits\n";
            continue;
        }
        if (!isValid) {
            std::cout << "Wrong sequence\n";
            continue;
        }
        // add to array
        for (int idx = 0; idx < nDigits; ++idx)
            pin[idx] = number[idx] - '0';
        break;
    }
}

void showSystem(const int sequence[], int size) {
    std::cout << "PIN: ";
    for (int idx = 0; idx < size; ++idx)
        std::cout << idx << " ";
    std::cout << "\nNUM: ";
    for (int idx = 0; idx < size; ++idx)
        std::cout << sequence[idx] << " ";
    std::cout << "\n";
}

bool checkPin(const int pin[], const int nDigitsPin,
              const int sequence[], const int nDigits) {

    int givenPin[PIN];
    int temp = GIVEN_PIN;
    for (int idx = PIN - 1; idx >= 0; --idx) {
        givenPin[idx] = temp % DIGITS;
        temp /= DIGITS;
    }
    for (int digit = 0; digit < nDigitsPin; ++digit) {
        int actualPinDigit = givenPin[digit];
        if (sequence[actualPinDigit] != pin[digit]) return false;
    }
    return true;
}
