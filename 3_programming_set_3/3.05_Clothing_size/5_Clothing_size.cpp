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

float hatSize(float weight, int heightFeet, int heightInches);

float jacketSize(float weight, int heightFeet, int heightInches, int age);

float waistSize(float weight, int age);

bool errorHandlingHeight(int heightFeet, int heightInches);

bool errorHandlingWeight(int weight);

bool errorHandlingAge(int age);






int main( ) {
    int heightFeet, heightInches, age;
    float weight, sizeHat, sizeJacket, sizeWaist;
    char answer = 'y';

    do {
        cout << "Enter the height in feet and in inches\n"
                "separated by a space:";
        cin >> heightFeet >> heightInches;

        if (!errorHandlingHeight(heightFeet, heightInches)) {
            cerr << "Incorrect height. Retry (y/Y)?";
            cin >> answer;
            if (answer != 'y' && answer != 'Y')
                return -1;
        } else {
            break;
        }
    } while (answer == 'y' || answer == 'Y');

    do {
        cout << "Enter the weight (in pounds):";
        cin >> weight;

        if (!errorHandlingWeight(weight)) {
            cerr << "Incorrect weight. Retry (y/Y)?";
            cin >> answer;
            if (answer != 'y' && answer != 'Y')
                return -1;
        } else {
            break;
        }
    } while (answer == 'y' || answer == 'Y');

    // error handling for weight

    do {
        cout << "Enter the age:";
        cin >> age;

        if (!errorHandlingAge(age)) {
            cerr << "Incorrect age. Retry (y/Y)?";
            cin >> answer;
            if (answer != 'y' && answer != 'Y')
                return -1;
        } else {
            break;
        }
    } while (answer == 'y' || answer == 'Y');

    sizeHat = hatSize(weight, heightFeet, heightInches);
    sizeJacket = jacketSize(weight, heightFeet, heightInches, age);
    sizeWaist = waistSize(weight, age);

    cout << "Hat size: " << sizeHat << endl
         << "Jacket size: " << sizeJacket << endl
         << "Waist size: " << sizeWaist << endl;

    return 0;
}

bool errorHandlingHeight(int heightFeet, int heightInches) {
    if (heightFeet < 5 || heightFeet > 8 || heightInches < 0 || heightInches > 11)
        return false;
    return true;
}

bool errorHandlingWeight(int weight) {
    if (weight < 80 || weight > 400)
        return false;
    return true;
}

bool errorHandlingAge(int age) {
    if (age < 0 || age > 120)
        return false;
    return true;
}

float hatSize(float weight, int heightFeet, int heightInches) {
    float height;

    height = heightFeet * 12 + heightInches;
    return ((weight / height) * HAT_CONSTANT);
}

float jacketSize(float weight, int heightFeet, int heightInches, int age) {
    float height, size;

    height = heightFeet * 12 + heightInches;
    size = (height * weight) / JACKET_CONSTANT;
    if (age > 30)
        size += ((age - 30) / 10) * JACKET_OFFSET;

    return size;
}

float waistSize(float weight, int age) {
    float size;

    size = weight / WAIST_CONSTANT;
    if (age > 28)
        size += ((age - 28) / 2) * WAIST_OFFSET;

    return size;
}

