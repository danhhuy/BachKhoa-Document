#include <iostream>
using namespace std;

int GF(int a, int b,int xn2,int yn2,int xn1,int yn1){
    if(b==0) return yn2;
    return GF(b, a%b,xn1,yn1,xn2-(int)(a/b)*xn1,yn2-(int)(a/b)*yn1);
}

int main(){
    int a = 26, b = 19;       //a > b
    // nghich dao nhan b^-1 cua b trong GF(a)
    cout << GF(a,b,1,0,0,1);
    return 0;
}