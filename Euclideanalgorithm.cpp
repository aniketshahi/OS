#include<iostream>
#include<conio.h>
using namespace std;
int Euclideanalgorithm (int a, int b)
{
int r;
while (b != 0)
{
r = a % b;
a = b;
b = r;
}
return a;
}
int main()
{
int a, b;
cout<<"Enter the first number: ";
cin>>a;
cout<<"Enter the second number: ";
cin>>b;
cout<<"The GCD of "<<a<<" and "<<b<<" is "<<Euclideanalgorithm(a, b)<<endl;
getch();
return 0;
}
