#include <iostream>

using namespace std;

int extended_euclidean_algorithm(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        int gcd = extended_euclidean_algorithm(b, a % b, y, x);
        y -= (a / b) * x;
        return gcd;
    }
}

int main() {
    int choice;
    int a, b, x, y, gcd;

    do {
        cout << "Menu:\n";
        cout << "1. Find GCD and coefficients\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter two integers: ";
                cin >> a >> b;
                gcd = extended_euclidean_algorithm(a, b, x, y);
                cout << "GCD of " << a << " and " << b << " is " << gcd << endl;
                cout << "Coefficients: " << x << ", " << y << endl;
                break;
            case 2:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 2);

    return 0;
}
