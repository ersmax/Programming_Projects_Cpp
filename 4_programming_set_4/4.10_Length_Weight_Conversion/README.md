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

---

If the user wants to exit at the sub-menu (choosing betweeen feet & meters conversion or pound & kilo conversion),
one needs to change the signature and definition of the function `void makeChoice(const int& choiceMenu, int& choiceSubmenu)`
to the following:
```
void makeChoice(int& choiceMenu, int& choiceSubmenu);
```
```
void makeChoice(int& choiceMenu, int& choiceSubmenu) {
    while (true) {
        int answer;

        if (choiceMenu == 1)
            cout << "Length menu:\n"
                 << "1. Convert feet & inches to meters and centimeters\n"
                 << "2. Convert meters & centimeters to feet & inches\n";
        if (choiceMenu == 2)
            cout << "Weight menu:\n"
                 << "1. Convert pounds & ounces to kilos and grams\n"
                 << "2. Convert kilo & grams to pounds & ounces\n";

        cout     << "0. Exit sub-menu\n"
                 << "Enter action:\n";

        if (!(cin >> answer)) {
            cout << "Invalid choice.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore remaining input after 1 or 2
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n";

        if (answer == 0) {
            choiceMenu = answer;
            break;
        }
        if (answer == 1 || answer == 2) {
            choiceSubmenu = answer;
            break;
        }

        cout << "Invalid result.\n\n";
    }
}
``` 
An additional local variable `int answer` is declared, because the input from the user (`cin >> answer`) 
guides the program whether to exit from execution (`choiceMenu = answer` and later `if (choice.lengthWeight == 0) break;`)
or continue with the execution (`choiceSubmenu = answer`).
Should the user wants to exit from the submenu, the option of returning to the menu from submenu in the main should 
also be removed. That is, the following condition in the main should be removed or commented out:
```
if (choice.meterFeet == 0 ||                    // sub-menu termination
    choice.kiloPound == 0) continue;
```