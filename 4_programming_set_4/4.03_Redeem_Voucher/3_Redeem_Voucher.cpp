/*
You have a voucher for a bakery, which you redeem to buy baked goods of your
choice. The value of the voucher is fixed and the total bill of the items selected
should not exceed the voucher value. If the voucher has any value left after the
purchase, then it cannot be utilized again. Write a program that displays 4 items
and their prices as a menu and then reads the value of the voucher.
Write a function, with parameters itemCode and voucherValue passed by reference,
that deducts the price of an item from the voucher’s value only if the item’s
value is less that or equal to the voucher value. Use a loop to invoke the above
function as many times as required until the value of the voucher is less than or
equal to the cheapest item on the menu.
Finally, display the calculated sum of the prices of the items selected, and the unutilized
balance on the voucher after purchase.
*/

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <limits>
#include <cassert>
using std::vector;
using std::cin;
using std::cout;
using std::string;
using std::pair;
using std::numeric_limits;
using std::streamsize;
using std::endl;
using std::swap;

constexpr int ITEMS = 4;

void addVoucherValue(double& voucherValue);

void addItem(vector<pair<string, double>>& items);

void sortItem(vector<pair<string, double>>& items);

void showItem(const vector<pair<string, double>>& items);

void useVoucher(vector<pair<string, double>>&items, double& voucherValue, double& total);

int main( ) {
    vector<pair<string, double>> items;
    double voucherValue, total = 0;

    addVoucherValue(voucherValue);
    for (int idx = 0; idx < ITEMS; idx++)
        addItem(items);

    assert(items.size() == ITEMS);
    sortItem(items);

    showItem(items);

    useVoucher(items, voucherValue, total);

    return 0;
}


void addVoucherValue(double& voucherValue) {
    while (true) {
        cout << "Enter the value of voucher:";
        while (!(cin >> voucherValue)) {
            cout << "Invalid Input. Enter a number:";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        // discard extra tokens
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (voucherValue >= 0)
            break;
        cout << "Invalid amount. ";
    }
    cout << "Voucher value: " << voucherValue << endl;
}

void addItem(vector<pair<string, double> >& items) {
    string name;
    double price;

    while (true) {
        cout << "Enter the name and price of item:";
        while (!(cin >> name >> price)) {
            cout << "Invalid input. Enter valid name and price:";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }

        // discard extra tokens
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (price >= 0) {
            items.emplace_back(name, price);
            break;
        }
        cout << "Invalid price.\n";
    }
    cout << "Item " << items.back().first << " added"
         << " (p: " << items.back().second << ")\n";
}

void sortItem(vector<pair<string, double> >& items) {
    for (int i = 0; i < items.size(); i++) {
        int idxMaxValue = i;

        for (int j = i + 1; j < items.size(); j++)
            if (items[i].second > items[j].second)
                idxMaxValue = j;

        if (idxMaxValue != i)
            swap(items[i], items[idxMaxValue]);
    }
}

void showItem(const vector<pair<string, double>>& items) {
    for (const pair<string, double>& item : items)
        cout << item.first << " price: " << item.second << "\n-----\n";
}

void useVoucher(vector<pair<string, double> >& items, double& voucherValue, double& total) {

}
