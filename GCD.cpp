#include <iostream>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int main() {
    int choice, num1, num2, result;
    while (true) {
        cout << "\n1. Find GCD\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter first number: ";
                cin >> num1;
                cout << "Enter second number: ";
                cin >> num2;
                result = gcd(num1, num2);
                cout << "GCD of " << num1 << " and " << num2 << " is " << result << endl;
                break;
            case 2:
                return 0;
            default:
                cout << "Invalid choice. Please select from the menu.\n";
        }
    }
    return 0;
}
