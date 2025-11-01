/*
(You should do Programming Projects 4.6 and 4.9 before doing this programming
project.) Write a program that combines the functions of Programming
Projects 4.6 and 4.9. The program asks the user if he or she wants to convert
lengths or weights. If the user chooses lengths, then the program asks the user if
he or she wants to convert from feet and inches to meters and centimeters or from
meters and centimeters to feet and inches. If the user chooses weights, a similar
question about pounds, ounces, kilograms, and grams is asked. The program then
performs the desired conversion. Have the user respond by typing the integer 1 for
one type of conversion and 2 for the other. The program reads the user’s answer
and then executes an if-else statement. Each branch of the if-else statement
will be a function call. The two functions called in the if-else statement will
have function definitions that are very similar to the programs for Programming
Projects 4.6 and 4.9. Thus, these functions will be fairly complicated function
definitions that call other functions; however, they will be very easy to write by
adapting the programs you wrote for Programming Projects 4.6 and 4.9. Notice
that your program will have if-else statements embedded inside of if-else
statements, but only in an indirect way. The outer if-else statement will include
two function calls, as its two branches. These two function calls will each
in turn include an if-else statement, but you need not think about that. They
are just function calls and the details are in a black box that you create when you
define these functions. If you try to create a four-way branch, you are probably
on the wrong track. You should only need to think about two-way branches (even
though the entire program does ultimately branch into four cases). Include a loop
that lets the user repeat this computation for new input values until the user says
he or she wants to end the program.
*/

#include <iostream>
#include <limits>
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;

struct Choice {
    int lengthWeight = -1;  // 0 exit, 1 length,   2 weight
    int meterFeet = -1;     // 0 exit, 1 feet/m,   2 m/feet
    int kiloPound = -1;     // 0 exit, 1 pound/kg, 2 kg/pound
};

void makeChoice(Choice& choice);             // orchestrator
void makeChoice(int& choice);                // top-level menu
void makeChoice(int& choice, bool isLength); // submenu

int main ( ) {
    Choice choice;

    while (true) {
        makeChoice(choice);
        if (choice.lengthWeight == 1) {
            makeChoice(choice, subChoice);
            if (choice.lengthWeight == 0)
                break;
            // TODO
        }
        else if (choice.lengthWeight == 2) {
            makeChoice(choice, subChoice);
            if (choice.lengthWeight == 0)
                break;
            // TODO
        } else
            break;
    }
    cout << '\n';
    return 0;
}

void makeChoice(Choice& choice) {
    while (true) {
        cout << "Menu:\n"
             << "1. Convert length (feet & inches <-> km & meters)\n"
             << "2. Convert weight (pounds & ounces <-> kg & grams)\n"
             << "0. Exit\n"
             << "Choice:";
        if (!(cin >> choice.lengthWeight)) {
            cout  << "Invalid choice.\n\n";
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore remaining input
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        if (choice.lengthWeight == 0 ||
            choice.lengthWeight == 1 ||
            choice.lengthWeight == 2)
            break;

        cout << "Invalid choice.\n\n";
    }
}

void makeChoice(Choice& choice, Choice& subChoice) {
    while (true) {
        int answer;
        if (choice.lengthWeight == 1)
            cout << "Length menu:\n"
                 << "1. Convert feet & inches to meters and centimeters\n"
                 << "2. Convert meters & centimeters to feet & inches\n";
        else if (choice.lengthWeight == 2)
            cout << "Length menu:\n"
                 << "1. Convert pounds & ounces to kilos and grams\n"
                 << "2. Convert kilo & grams to pounds & ounces\n";

        cout << "0. Exit\n"
             << "Enter action:\n";

        if (!(cin >> answer)) {
            cout << "Invalid choice.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore remaining input after 1 or 2
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (answer < 0 || answer > 2) {
            cout << "Invalid choice.\n\n";
            continue;
        }
        if (choice.lengthWeight == 1)
            subChoice.meterFeet = answer;
        if (choice.lengthWeight == 2)
            subChoice.kiloPound = answer;
        if (choice.lengthWeight == 0)
            choice.lengthWeight = 0;
        break;
    }
}

// TODO: assess whether is more convenient to use an orchestrator to handle submenu.