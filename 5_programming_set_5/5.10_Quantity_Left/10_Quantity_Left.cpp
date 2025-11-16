/*
Write a program that displays the list of flavors available at an ice-cream parlor with
a unique code for each flavor, as shown below.
Code Flavor
1 Chocolate
2 Vanilla
3 Strawberry
4 Raspberry
5 Butterscotch
The program then displays the code and quantity available for customers to purchase
as shown below.
1 20
2 15
3 15
4 20
5 20
The program should read the user’s choice of flavors and quantity and display the
products remaining in the stock, until the stock is exhausted or the user signals
that the program should end. Finally, the user’s cart should be displayed as shown
below
Chocolate 3
Strawberry 1
Raspberry 1
*/


#include <iostream>
#include <iomanip>
#include <limits>

constexpr int VARIATIONS = 5;

void makeChoice(const std::string flavors[], int nFlavors, int quantity[], int& choice);

void showOffer(const std::string flavors[], int nFlavors, const int quantity[]);

int main( ) {
    std::string flavors[VARIATIONS] = {"Chocolate", "Vanilla", "Strawberry", "Raspberry", "Butterscotch"};
    int quantity[VARIATIONS] = {20, 15, 15, 20, 20};
    int choice;
    do {
        makeChoice(flavors, VARIATIONS, quantity, choice);
    } while (choice != -1);

    showOffer(flavors, VARIATIONS, quantity);

    std::cout << "\n";
    return 0;
}

void makeChoice(const std::string flavors[], const int nFlavors, int quantity[], int& choice) {
    int itemChosen, qtyChosen;
    while (true) {
        showOffer(flavors, nFlavors, quantity);
        std::cout << "\nEnter item and quantity (separated by space).\n"
                     "To exit, press `-1` :\n";
        if (!(std::cin >> itemChosen >> qtyChosen)) {
            std::cout << "Not a valid choice. Retry\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // consume remaining input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // exit
        if (itemChosen == -1) {
            choice = itemChosen;
            return;
        }
        // correct for array bound
        --itemChosen;

        if ((itemChosen < nFlavors) && (itemChosen >= 0) &&
            (qtyChosen >= 0) && (qtyChosen <= quantity[itemChosen]) ) {

            quantity[itemChosen] -= qtyChosen;
            break;
        }

        std::cout << "Product not available. Retry\n";
    }
}

void showOffer(const std::string flavors[], const int nFlavors, const int quantity[]) {
    std::cout << std::setw(10)  << "Code"
              << std::setw(15) << "Flavor"
              << std::setw(8)  << "Q.ty\n";

    for (int idx = 0; idx < nFlavors; ++idx)
        std::cout << std::setw(10)  << idx + 1
                  << std::setw(15) << flavors[idx]
                  << std::setw(8)  << quantity[idx] << "\n";
}

