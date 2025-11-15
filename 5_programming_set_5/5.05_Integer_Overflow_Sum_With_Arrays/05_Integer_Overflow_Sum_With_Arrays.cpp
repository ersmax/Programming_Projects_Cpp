/*
An array can be used to store large integers one digit at a time. For example, the
integer 1234 could be stored in the array a by setting a[0] to 1, a[1] to 2, a[2]
to 3, and a[3] to 4. However, for this exercise you might find it more useful to
store the digits backward, that is, place 4 in a[0], 3 in a[1], 2 in a[2], and 1 in
a[3]. In this exercise you will write a program that reads in two positive integers
that are 20 or fewer digits in length and then outputs the sum of the two numbers.
Your program will read the digits as values of type char so that the number
1234 is read as the four characters '1', '2', '3', and '4'. After they are read into
the program, the characters are changed to values of type int. The digits will be
read into a partially filled array, and you might find it useful to reverse the order
of the elements in the array after the array is filled with data from the keyboard.
(Whether or not you reverse the order of the elements in the array is up to you. It
can be done either way, and each way has its advantages and disadvantages.) Your
program will perform the addition by implementing the usual paper-and-pencil
addition algorithm. The result of the addition is stored in an array of size 20 and
the result is then written to the screen. If the result of the addition is an integer with
more than the maximum number of digits (that is, more than 20 digits), then your
program should issue a message saying that it has encountered “integer overflow.”
You should be able to change the maximum length of the integers by changing
only one globally defined constant. Include a loop that allows the user to continue
to do more additions until the user says the program should end.
*/

#include <iostream>
#include <span>

constexpr int SIZE = 20;

void fillUpNumbers(int number[], int size, int& usedSize);

int main( ) {
    int number1[SIZE], number2[SIZE];
    int sizeNumber1, sizeNumber2;
    fillUpNumbers(number1, SIZE, sizeNumber1);
    fillUpNumbers(number2, SIZE, sizeNumber2);

    for (int digit : std::span(number1, sizeNumber1))
        std::cout << digit << " ";

    std::cout << "\n";

    for (int digit : std::span(number2, sizeNumber2))
        std::cout << digit << " ";

    std::cout << "\n";
    return 0;
}

void fillUpNumbers(int number[], int size, int& usedSize) {
    std::string line;

    while (true) {
        std::cout << "Enter the number up to " << size
                  << "digits, or `exit` to terminate\n";
        std::getline(std::cin, line);
        if (line == "exit") return;

        // check correct number of digits
        if (line.size() > static_cast<size_t>(size)) {
            std::cout << "Too many digits. Retry\n";
            continue;
        }

        // check every letter is a digit
        bool invalidDigit = false;
        for (const char ch : line)
            if (!std::isdigit(static_cast<unsigned char>(ch))) {
                std::cout << "Not a valid number. Retry\n";
                invalidDigit = true;
                break;
            }
        if (invalidDigit) continue;

        break;
    }

    usedSize = static_cast<int>(line.size());

    // store least significant digit first
    for (int idx = 0; idx < usedSize; ++idx)
        number[idx] = line[usedSize - idx - 1] - '0';

    for (int idx = usedSize; idx < size; ++idx)
        number[idx] = 0;
}
