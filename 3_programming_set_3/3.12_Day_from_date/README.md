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
value multiplied by 2. For example, the year 2008 becomes (20/4) = 5 remainder 0. 
Then 3 - 0 = 3. Return 3 * 2 = 6.
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
(getMonthValue) + (getYearValue) + (getCenturyValue) = 4 + 6 + 10 + 6 = 26.
26/7 = 3 remainder 5. The fifth day of the week corresponds to Friday.
Your program should allow the user to enter any date and output the corresponding
day of the week in English.

---

### 1. Map-Based Solution


**Description:**  
Uses a `std::map<string, int>` to associate month names (as uppercase strings) 
with their corresponding values. Leap years are handled by appending `"_LEAP"` 
to the month string for January and February.

**Advantages:**
- **Scalability:** Easy to add or modify month values.
- **Readability:** Direct mapping, less code clutter.
- **String Input:** Accepts month names directly from user input.

**Disadvantages:**
- **Memory:** Slightly more memory usage for the map.
- **String Manipulation:** Requires string transformation and concatenation.

**Example:**
```cpp
int getMonthValue(const string& monthRaw, int year) {
    string month = monthRaw;
    transform(month.begin(), month.end(), month.begin(), ::toupper);
    if (isLeapYear(year) && (month == "JANUARY" || month == "FEBRUARY"))
        month += "_LEAP";
    auto it = monthMap.find(month);
    if (it != monthMap.end())
        return it->second;
    return -1;
}
```

---

### 2. Switch-Based Solution

**Description:**  
Uses a `switch` statement on an integer month value (1-12) to return the corresponding value. Requires a separate function to convert month names to integers.

**Advantages:**
- **Performance:** Slightly faster, no map lookup.
- **Simplicity:** Straightforward for small, fixed sets.

**Disadvantages:**
- **Verbosity:** More code, less maintainable for changes.
- **String Conversion:** Needs a function to convert month names to integers.
- **Error-Prone:** Harder to extend or modify.

**Example:**
```cpp
int getMonthValue(int month, int year) {
    switch (month) {
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
        default: return -1;
    }
}

int convertMonth(const string& monthRaw) {
    string month = monthRaw;
    transform(month.begin(), month.end(), month.begin(), ::toupper);
    if (month == "JANUARY") return 1;
    if (month == "FEBRUARY") return 2;
    if (month == "MARCH") return 3;
    if (month == "APRIL") return 4;
    if (month == "MAY") return 5;
    if (month == "JUNE") return 6;
    if (month == "JULY") return 7;
    if (month == "AUGUST") return 8;
    if (month == "SEPTEMBER") return 9;
    if (month == "OCTOBER") return 10;
    if (month == "NOVEMBER") return 11;
    if (month == "DECEMBER") return 12;
    return -1;
}
```

---

### **Summary Table**

| Feature         | Map-Based Solution         | Switch-Based Solution      |
|-----------------|---------------------------|---------------------------|
| Readability     | High                      | Medium                    |
| Maintainability | High                      | Low                       |
| Performance     | Medium                    | High                      |
| Scalability     | High                      | Low                       |
| Input Type      | String (direct)           | Integer (conversion req.) |

--- 

Here is an updated section for your `README.md` explaining the other functions used in the program:

---

### Other Functions Explained

#### `bool isLeapYear(int year)`
Checks if a given year is a leap year using the standard rules:
- Returns `true` if the year is divisible by 400, or divisible by 4 but not by 100.
- Returns `false` otherwise.

#### `int getCenturyValue(int year)`
Calculates a value based on the century part of the year:
- Extracts the first two digits (century).
- Divides by 4 and gets the remainder.
- Subtracts the remainder from 3, multiplies by 2, and returns the result.

#### `int getYearValue(int year)`
Calculates a value based on the last two digits of the year:
- Extracts the last two digits.
- Divides by 4 and discards the remainder.
- Adds the result to the last two digits and returns the sum.

#### `int getMonthValue(...)`
Explained above, with both map-based and switch-based solutions.

#### Day of the Week Calculation
- Sums the day of the month, month value, year value, and century value.
- Divides the sum by 7 and uses the remainder to determine the day of the week (0 = Sunday, 1 = Monday, ..., 6 = Saturday).

---