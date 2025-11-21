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

---

## Transform a number into an array
There are two possible strategies to go about transforming a number into an array.

1. The first strategy is to extract each digit of the number and place it into an array. 
   This is done by repeatedly taking the modulus of 10 of the number to get the last 
   digit, and then dividing the number by 10 to remove the last digit. 
   This is done in the function `checkPin` in the code below.
```cpp
bool checkPin(const int pin[], const int nDigitsPin,
const int sequence[], const int nDigits) {

    int givenPin[PIN];
    int temp = GIVEN_PIN;
    for (int idx = PIN - 1; idx >= 0; --idx) {
        givenPin[idx] = temp % DIGITS;
        temp /= DIGITS;
    }
    // other code...
```
2. The second strategy is to convert the number into a string, and then  
   extract each character of the string and convert it back to an integer.
   This is done in the function `enterPin` in the code below.

```cpp
void enterPin(int pin[], const int nDigits) {
    std::string number;
    std::cout << "Enter the PIN sequence:\n";
    while (true) {
        
        // other code...
        
        // add to array
        for (int idx = 0; idx < nDigits; ++idx)
            pin[idx] = number[idx] - '0';
        break;
    }
}
```




## Alternative implementation
Another way to check the correctness is to build an internal
array with all the idx of the `sequence` associated with the corresponding 
randomized number.
However, this strategy requires more space, since we create 
an internal array for each digit of the PIN.

```cpp
bool checkPin(const int pin[], const int nDigitsPin,
              const int sequence[], const int nDigits) {

    int givenPin[PIN];
    int temp = GIVEN_PIN;
    for (int idx = PIN - 1; idx >= 0; --idx) {
        givenPin[idx] = temp % 10;
        temp /= 10;
    }
    
    // build an inner array to check the randomized numbers 
    for (int digit = 0; digit < nDigitsPin; ++digit) {
        int digits[PIN];
        int sizeDigits = 0;
        for (int idx = 0; idx < nDigits; ++idx) {
            if (sequence[idx] == pin[digit])
                digits[sizeDigits++] = idx;
        }
        // now check if randomized number is in sequence
        bool inSequence = false;
        for (int d = 0; d < sizeDigits; ++d)
            if (digits[d] == givenPin[digit]) {
                inSequence = true;
                break;
            }
        if (!inSequence) return false;
    }
    return true;
}
```
