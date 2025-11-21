Programming Project 2.12 asked you to explore Benford’s Law. An easier way to
write the program is to use an array to store the digit counts. That is, count[0]
might store the number of times 0 is the first digit (if that is possible in your data
set), count[1] might store the number of times 1 is the first digit, and so forth.
Redo Programming Project 2.12 using arrays.

---

# Overview

## Getting the lead digit using string conversion
It is possible to get the leading digit of a number by converting it to a string and
extracting the first character. This approach is straightforward and works well for
integers of any size.

```cpp
void checkNumber(int number, int& totNumbers, int count[], const int size) {
    number = std::abs(number);
    ++totNumbers;
    const std::string s = std::to_string(number);
    int leadingDigit = s[0] - '0';
    if (leadingDigit >= 0 && leadingDigit < size)
        ++count[leadingDigit];
}
```

Alternatively, you can extract the leading digit using mathematical operations, 
which avoids string conversion and works directly with the numeric value.
This method is preferred for performance and simplicity when dealing with integers.
```cpp
void checkNumber(int number, int& totNumbers, int count[], const int size) {
    number = std::abs(number);
    ++totNumbers;
    while (number >= 10) number /= 10;
    if (number >= 0 && number < size)
        ++count[number];
}
```