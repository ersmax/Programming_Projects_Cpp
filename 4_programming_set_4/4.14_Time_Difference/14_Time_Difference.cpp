/*
Your time machine is capable of going forward in time up to 24 hours. The machine
is configured to jump ahead in minutes. To enter the proper number of minutes
into your machine, you would like a program that can take a start time and an
end time and calculate the difference in minutes between them. The end time will
always be within 24 hours of the start time. Use military notation for both the start
and end times (e.g., 0000 for midnight and 2359 for one minute before midnight).
Write a function that takes as input a start time and an end time represented as an
int, using military notation. The function should return the difference in minutes
as an integer. Write a driver program that calls your subroutine with times entered
by the user.
Hint: Be careful of time intervals that start before midnight and end the following day.
*/

#include <iostream>
#include <string>
#include <limits>

void enterDate(std::string& startingDate, std::string& endingDate);

bool validDate(const std::string& date);

int main( ) {
    std::string startingDate, endingDate;
    enterDate(startingDate, endingDate);
}

void enterDate(std::string& startingDate, std::string& endingDate) {
    while (true) {
        std::cout << "Enter valid starting date";
        if (!(std::cin >> startingDate)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (startingDate == "-1") std::exit(-1);
        if (!validDate(startingDate)) {
            std::cout << "Invalid starting time. Try again.\n";
            continue;
        }
        break;
    }

}

bool validDate(const std::string& date) {
    if (date.size() != 4)  // right length
        return false;
    for (const unsigned char& c : date) // a number
        if (!std::isdigit(c))
            return false;

    int value = std::stoi(date);
    int hours = value / 100;
    int minutes = value % 100;

    return (hours >= 0 && hours <= 23 &&
            minutes >= 0 && minutes <= 59);
}



