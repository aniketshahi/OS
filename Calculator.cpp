#include <iostream>
using namespace std;
void add(float a, float b)
{
    float c;
    c = a + b;
    cout << "Sum of a and b is:" << c;
}
void sub(float a, float b)
{
    float c;
    c = a - b;
    cout << "Sum of a and b is:"<< c;
}
void mul(float a, float b)
{
    float c;
    c = a * b;
    cout << "Sum of a and b is:" << c;
}
void divi(float a, float b)
{
    float c;
    c = a / b;
    cout << "Sum of a and b is:" << c;
}
int main()
{
    float a, b;
    int c;
    cout << "Enter number 1:";
    cin >> a;
    cout << "Enter number 2:";
    cin >> b;
    cout << "1.Addition "
         << "2.Substraction "
         << "3.Addition "
         << "4.Substraction" << endl
         << "Enter your choice:";
    cin >> c;
    switch (c)
    {
    case 1:
        add(a, b);
        break;
    case 2:
        sub(a, b);
        break;
    case 3:
        mul(a, b);
        break;
    case 4:
        divi(a, b);
        break;

    default:
        break;
    }
    return 0;
}