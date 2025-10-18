/*
Write a program that inputs a date (e.g., July 4, 2008) and outputs the day of
the week that corresponds to that date. The following algorithm is from http://
en.wikipedia.org/wiki/Calculating_the_day_of_the_week. The implementation
will require several functions:
bool isLeapYear(int year);
This function should return true if year is a leap year and false if it is not. Here
is pseudocode to determine a leap year:
leap_year = ((year divisible by 400) or (year divisible by 4 and year not divisible
by 100))
int getCenturyValue(int year);
This function should take the first two digits of the year (i.e., the century), divide
by 4, and save the remainder. Subtract the remainder from 3 and return this
value multiplied by 2. For example, the year 2008 becomes (20/4) = 5 remainder
0. 3 - 0 = 3. Return 3 * 2 = 6.
int getYearValue(int year);
This function computes a value based on the years since the beginning of the
century. First, extract the last two digits of the year. For example, 08 is extracted
for 2008. Next, factor in leap years. Divide the value from the previous step by 4
and discard the remainder. Add the two results together and return this value. For
example, from 2008 we extract 08. Then (8/4) = 2 remainder 0. Return 2 + 8 = 10.
int getMonthValue(int month, int year);
This function should return a value based on the following table and will require
invoking the isLeapYear function:
MONTH RETURN VALUE
January 0 (6 if year is a leap year)
February 3 (2 if year is a leap year)
March 3
April 6
May 1
June 4
July 6
August 2
September 5
October 0
November 3
December 5
Finally, to compute the day of the week, compute the sum of the date’s day plus
the values returned by getMonthValue, getYearValue, and getCenturyValue.
Divide the sum by 7 and compute the remainder. A remainder of 0 corresponds to
Sunday, 1 corresponds to Monday, etc.—up to 6—which corresponds to Saturday.
For example, the date July 4, 2008 should be computed as (day of month) +
(getMonthValue) + (getYearValue) + (getCenturyValue) = 4 + 6 + 10 + 6 =
26. 26/7 = 3 remainder 5. The fifth day of the week corresponds to Friday.
Your program should allow the user to enter any date and output the corresponding
day of the week in English.
*/

#include <algorithm>    // for transform
#include <iostream>     // for cin, cout, cerr
#include <string>       // for string class
#include <cctype>       // for toupper
using namespace std;

const string days[] = { "Sunday", "Monday",
                        "Tuesday", "Wednesday",
                        "Thursday", "Friday",
                        "Saturday" };

bool isLeapYear(int year);
// Precondition: year is a positive integer
// Postcondition: returns true if year is a leap year, false otherwise

int getCenturyValue(int year);
// Precondition: year is a positive integer
// Postcondition: returns the century value for the given year

int getYearValue(int year);
// Precondition: year is a positive integer
// Postcondition: returns the year value for the given century (e.g. 2025 -> 25)

int getMonthValue(int monthRaw, int year);
// Precondition: month is an integer between 1 and 12, year is a positive integer
// Postcondition: returns the month value for the given month and year,
// accounting for leap years

int convertMonth(const string& monthRaw);
// Precondition: monthRaw is a string representing the month name
// Postcondition: returns the integer value of the month (1-12), (1 = January, etc.)

int main( ) {
    // Postcondition: Prompts user for a date (e.g., July 4 2008)
    // and displays the corresponding day of the week.
    int dayOfMonth, year, monthValue, yearValue, centuryValue;
    int dayOfWeek;
    string month;

    cout << "Enter date (Month Day Year, for example: July 4 2008):";
    cin >> month >> dayOfMonth >> year;

    int monthInt = convertMonth(month);
    if (monthInt == -1) {
        cerr << "Error: Invalid month name.\n";
        return -1;
    }
    monthValue = getMonthValue(monthInt, year);
    yearValue = getYearValue(year);
    centuryValue = getCenturyValue(year);

    dayOfWeek = (dayOfMonth + monthValue+ yearValue + centuryValue) % 7;
    cout << days[dayOfWeek] << ", "
         << month << " "
         << dayOfMonth << ", "
         << year << endl;
    return 0;
}

bool isLeapYear(int year) {
    return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
}

int getCenturyValue(int year) {
    int century = year / 100;
    int remainder = century % 4;
    return ((3 - remainder) * 2);
}

int getYearValue(int year) {
    int yearCentury = year % 100;
    return (yearCentury + yearCentury / 4);
}

int getMonthValue(int month, int year) {
    switch (month) {
        // Month values based on the table provided by wikipedia.
        // Factor in leap years for Jan and Feb.
        case 1:  return isLeapYear(year) ? 6 : 0;
        case 2:  return isLeapYear(year) ? 2 : 3; 
        case 3:  return 3;
        case 4:  return 6;
        case 5:  return 1;
        case 6:  return 4;
        case 7:  return 6;
        case 8:  return 2;
        case 9:  return 5;
        case 10: return 0;
        case 11: return 3;
        case 12: return 5;
        default: return -1; // Invalid month
    }
}

int convertMonth(const string& monthRaw) {
    static const string months[] = {
        "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE",
        "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"
    };

    string month = monthRaw;
    transform(monthRaw.begin(), monthRaw.end(), month.begin(), ::toupper);

    for (int idx = 0; idx < 12; ++idx)
        if (month == months[idx])
            return (idx + 1);

    return -1; // Invalid month
}
