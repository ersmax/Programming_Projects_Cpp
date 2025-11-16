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

constexpr int VARIATIONS = 5;

void makeChoice(const std::string flavors[], int nFlavors, int quantity[],
                int& choice, int& qtyChosen);

void addChoice(int cart[], int choice, int qtyChosen);

void showOffer(const std::string flavors[], int nFlavors, const int quantity[]);

void showCart(const std::string flavors[], int nFlavors, const int cart[]);

int main( ) {
    std::string flavors[VARIATIONS] = {"Chocolate", "Vanilla", "Strawberry", "Raspberry", "Butterscotch"};
    int quantity[VARIATIONS] = {20, 15, 15, 20, 20};
    int cart[VARIATIONS] = {0};

    int choice, qtyChosen = 0;
    do {
        makeChoice(flavors, VARIATIONS, quantity, choice, qtyChosen);
        if (choice != -1)
            addChoice(cart, choice, qtyChosen);
    } while (choice != -1);

    std::cout << "Remaining stock:\n";
    showOffer(flavors, VARIATIONS, quantity);
    showCart(flavors, VARIATIONS, cart);

    std::cout << "\n";
    return 0;
}

void makeChoice(const std::string flavors[], const int nFlavors,
                int quantity[], int& choice, int& qtyChosen) {
    choice = -1;
    std::string line;
    while (true) {
        showOffer(flavors, nFlavors, quantity);
        std::cout << "\nEnter item and quantity (separated by space).\n"
                     "To exit, press `-1` :\n";

        // EOF or error
        if (!std::getline(std::cin, line)) {
            choice = -1;
            return;
        }
        std::istringstream iss(line);
        if (!(iss >> choice)) {
            std::cout << "Not a valid choice. Retry\n";
            continue;
        }
        if (choice == -1)
            return;
        if (!(iss >> qtyChosen)) {
            std::cout << "Wrong quantity. Retry\n";
            continue;
        }

        // adjust to zero-based-idx array
        --choice;
        if ((choice < nFlavors) && (choice >= 0) &&
            (qtyChosen >= 0) && (qtyChosen <= quantity[choice]) ) {
            quantity[choice] -= qtyChosen;
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

void addChoice(int cart[], int choice, int qtyChosen) {
    if (choice >= 0)
        cart[choice] += qtyChosen;
}

void showCart(const std::string flavors[], const int nFlavors, const int cart[]) {
    std::cout << "Your cart: \n";
    for (int idx = 0; idx < nFlavors; ++idx) {
        
    }
}
