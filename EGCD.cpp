#include <iostream>

using namespace std;

// Function to find the GCD of two numbers and the coefficients that can be used to express that GCD as a linear combination of the two numbers
// The coefficients are returned as references to x and y
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
    int a = 10, b = 6, x, y;
    int gcd = extended_euclidean_algorithm(a, b, x, y);
    cout << "GCD of " << a << " and " << b << " is " << gcd << endl;
    cout << "Coefficients: " << x << ", " << y << endl;

    a = 17, b = 12;
    gcd = extended_euclidean_algorithm(a, b, x, y);
    cout << "GCD of " << a << " and " << b << " is " << gcd << endl;
    cout << "Coefficients: " << x << ", " << y << endl;

    a = 121, b = 44;
    gcd = extended_euclidean_algorithm(a, b, x, y);
    cout << "GCD of " << a << " and " << b << " is " << gcd << endl;
    cout << "Coefficients: " << x << ", " << y << endl;

    return 0;
}
