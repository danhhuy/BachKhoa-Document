#include <iostream>
#include <stdint.h>
using namespace std;

int gcd(int n1, int n2)
{
    if (n2 != 0)
        return gcd(n2, n1 % n2);
    else 
        return n1;
}
int GF(int a, int b,int xn2,int yn2,int xn1,int yn1){
    if(b==0) return yn2;
    return GF(b, a%b,xn1,yn1,xn2-(int)(a/b)*xn1,yn2-(int)(a/b)*yn1);
}

int main(){
    // Chon 2 so la 11 va 17. Sau do tinh n = (p-1)*(q-1)
    int n = 440;
    int m = 0;
    int count = 0;
    for(int i=1; i<n; i++){
        if(gcd(i, n) == 1){
            m = GF(n,i,1,0,0,1);
            count++;
            if(m>0){
                cout << i << ":" << m << "  ";
            }
            else cout << i << ":" << m + n << "  ";
        }
    }
    cout << endl << "So cap: "  <<  count << endl;
}