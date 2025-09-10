/*
The video game machines at your local arcade output coupons depending on how
well you play the game. You can redeem 10 coupons for a candy bar or 3 coupons
for a gumball. You prefer candy bars to gumballs. Write a program that inputs the
number of coupons you win and outputs how many candy bars and gumballs you
can get if you spend all of your coupons on candy bars first and any remaining
coupons on gumballs.
*/
#include <iostream>
using namespace std;

int main() {
    int total_coupons;
    int candy_bars = 0, gumballs = 0, remaining_coupons = 0;

    cout << "Enter the number of coupons you have: ";
    cin >> total_coupons;

    candy_bars = total_coupons / 10;
    remaining_coupons = total_coupons % 10;
    gumballs = remaining_coupons / 3;

    cout << "You can get " << candy_bars << " candy bar(s) and "
         << gumballs << " gumball(s).\n";

    return 0;
}