#include <iostream>
using namespace std;
void mode(int a, int b)
{
    int c;
    float d;
    c = a / b;
    d = a -( b*c);
    cout<<"Remainder is :"<<d;
}
int main()
{
    int a, b;
    cout << "Enter number 1:";
    cin >> a;
    cout << "Enter number 2:";
    cin >> b;
    mode(a,b);
    return 0;
}