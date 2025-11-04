#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

int main( ) {
    int vehicleClass;
    double toll;
    string test = "hello";

    if (test == "hello")
        cout << "yes";

    cin >> vehicleClass;

    switch (vehicleClass) {
        case 1:
            cout << "Passenger car";
            toll = 0.50;
            break;
        case 2:
            cout << "Bus";
            toll = 1.50;
            break;
        case 3:
            cout << "Truck";
            toll = 2.00;
            break;
        default:
            cout << "Unknown vehicle class";
            break;
    }
    return 0;
}