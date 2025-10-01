/*
Write a program that asks for the user’s height, weight, and age, and then computes
clothing sizes according to the following formulas.
• Hat size = weight in pounds divided by height in inches and all that multiplied
by 2.9.
• Jacket size (chest in inches) = height times weight divided by 288 and then
adjusted by adding one-eighth of an inch for each 10 years over age 30. (Note
that the adjustment only takes place after a full 10 years. So, there is no adjustment
for ages 30 through 39, but one-eighth of an inch is added for age 40.)
• Waist in inches = weight divided by 5.7 and then adjusted by adding one-tenth
of an inch for each 2 years over age 28. (Note that the adjustment only takes
place after a full 2 years. So, there is no adjustment for age 29, but one-tenth
of an inch is added for age 30.)
Use functions for each calculation. Your program should allow the user to repeat
this calculation as often as he or she wishes.
*/
#include <iostream>
using namespace std;

const float HAT_CONSTANT = 2.9f,
            JACKET_CONSTANT = 288.0f,
            JACKET_OFFSET = 0.125f,
            WAIST_CONSTANT = 5.7f,
            WAIST_OFFSET = 0.1f;

float hatSize(int weight, int heightFeet, int heightInches);
// Precondition: weight, heightFeet, and heightInches are positive integers
// Postcondition: returns the hat size in inches

float jacketSize(int weight, int heightFeet, int heightInches, int age);
// Precondition: weight, heightFeet, heightInches, and age are positive integers
// Postcondition: returns the jacket size in inches

float waistSize(int weight, int age);
// Precondition: weight and age are positive integers
// Postcondition: returns the waist size in inches

int getValidatedInput(const string& prompt, int min, int max);
// Precondition: 0 <= min < max <= 120. Pass prompt by reference
//               to avoid copying and improve performance
// Postcondition: Prompts user for input until a valid integer
//                within the specified range is entered.
//                Or exits if user chooses not to retry.

int main( ) {
    // Postcondition: Prompts user for height, weight, and age,
    //                then displays the hat, jacket, and waist sizes.
    int heightFeet, heightInches, age, weight;
    float sizeHat, sizeJacket, sizeWaist;



    heightFeet = getValidatedInput("Enter the height in feet (5-7): ", 5, 7);
    heightInches = getValidatedInput("Enter the height in inches (0-11): ", 0, 11);
    weight = getValidatedInput("Enter the weight (80-400): ", 80, 400);
    age = getValidatedInput("Enter the age (0-120): ", 0, 120);

    sizeHat = hatSize(weight, heightFeet, heightInches);
    sizeJacket = jacketSize(weight, heightFeet, heightInches, age);
    sizeWaist = waistSize(weight, age);

    cout << "Hat size: " << sizeHat << endl
         << "Jacket size: " << sizeJacket << endl
         << "Waist size: " << sizeWaist << endl;

    return 0;
}

int getValidatedInput(const string& prompt, int min, int max) {
    int value;
    char answer;

    while (true) {
        cout << prompt;
        cin >> value;
        if (value < min || value > max) {
            cerr << "Error: Value must be between "
                 << min << " and " << max << ".\n";
            cout << "Do you want to try again? (y/Y): ";
            cin >> answer;

            if (answer != 'y' && answer != 'Y')
                exit(-1);
        } else
            return value;
    }
}

float hatSize(int weight, int heightFeet, int heightInches) {
    float height;

    height = heightFeet * 12.0f + heightInches;
    return ((weight / height) * HAT_CONSTANT);
}

float jacketSize(int weight, int heightFeet, int heightInches, int age) {
    int height;
    float size;

    height = heightFeet * 12 + heightInches;
    size = (height * weight) / JACKET_CONSTANT;
    if (age > 30)
        size += ((age - 30) / 10.0f) * JACKET_OFFSET;

    return size;
}

float waistSize(int weight, int age) {
    float size;

    size = weight / WAIST_CONSTANT;
    if (age > 28)
        size += ((age - 28) / 2.0f) * WAIST_OFFSET;

    return size;
}
