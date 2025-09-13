/*
An organization intends to get people to sponsor the education of underprivileged
children. As part of their program, they launch a website where people can register
by entering their details and the amount (in USD) they wish to sponsor each
month. The website calculates the number of children the donor can sponsor based
on the amount required to educate one child.
Write a program that inputs the amount required for one child’s education, and
the amount a person is willing to sponsor, and calculates how many children
can be sponsored by that person. The program should also print how much of
the person’s amount is remaining after calculating the number of children, and
suggest how many more dollars would educate another child. (Hint: Use a do
while loop)
*/
#include <iostream>
using namespace std;

int main ( ) {
    float amtEducationChild, amtFinancing;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Enter the amount required for one child's education:";
    cin >> amtEducationChild;
    cout << "Enter the amount you wish to sponsor:";
    cin >> amtFinancing;

    int numKids;
    float remaingAmt = amtFinancing;

    do {
        numKids = static_cast<int>(amtFinancing/amtEducationChild);
        remaingAmt -= static_cast<float>(numKids) * amtEducationChild;
    } while (amtFinancing >= amtEducationChild);

    cout << "Remaining amt: " << remaingAmt << endl
         << "Additional amt to sponsor: " << amtEducationChild - amtFinancing << endl
         << "Kids educated: " << numKids << endl;

    return 0;
}
