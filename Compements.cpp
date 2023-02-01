#include <iostream>
#include <string>

using namespace std;

void onesComplement(string binary, string &result) {
    int length = binary.length();
    for (int i = 0; i < length; i++) {
        if (binary[i] == '0')
            result[i] = '1';
        else
            result[i] = '0';
    }
}

void twosComplement(string binary, string &result) {
    int length = binary.length();
    onesComplement(binary, result);
    int carry = 1;
    for (int i = length - 1; i >= 0; i--) {
        if (result[i] == '0' && carry == 1) {
            result[i] = '1';
            carry = 0;
        } else if (result[i] == '1' && carry == 1) {
            result[i] = '0';
            carry = 1;
        }
    }
}

int main() {
    string binary, onesComp, twosComp;
    cout << "Enter a binary number: ";
    cin >> binary;
    onesComp = binary;
    twosComp = binary;
    onesComplement(binary, onesComp);
    twosComplement(binary, twosComp);
    cout << "1's complement: " << onesComp << endl;
    cout << "2's complement: " << twosComp << endl;
    return 0;
}
