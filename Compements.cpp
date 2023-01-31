#include <iostream>
#include <cmath>
using namespace std;
int onesComplement(int n)
{
    int bitcount = floor(log2(n)) + 1;
    int ones = ((1 << bitcount) - 1);
    return ones ^ n;
}
int main()
{ 
    int a;
    cout << "Enter number:";
    cin >> a;
    cout << "One's Complement of " << a << " is: " << onesComplement(a);
}