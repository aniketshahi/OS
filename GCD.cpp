#include <iostream>
using namespace std;
int gcd(int a,int b){
       if(b==0)
       return a;
      return gcd(a,a%b);

}
int main()
{
      int a,b;
      cout<<"Enter number 1:" ;
      cin>>a;
      cout<<"Enter number 2:" ;
      cin>>b;
      cout<<gcd(a,b);

return 0;
}