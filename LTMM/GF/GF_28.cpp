// bai nay em tu code dua vao tai lieu cua co, em chua test het duoc cac case, co test cho em voi a, em cam on co !
#include <iostream>

using namespace std;

static int countDivision = 0;

class Galois{
    private:
        bool element[8];
    public: 
        Galois(){
            for(int i=0; i<8; i++) this->element[i] = 0;
        }
        Galois(bool *arr){
            for(int i=7; i>=0; i--){
                this->element[i] = *arr;
                arr+=1;
            }
        }
        friend ostream& operator<<(ostream& os, Galois g);
        Galois operator=(const Galois& g);
        Galois operator+(const Galois& g);
        Galois operator<<(int n);
        Galois operator%(const Galois& g);
        Galois operator*(const Galois& g);
        Galois operator/(const Galois& g);
        Galois operator/=(const Galois& g);
        int checkIndexMSB();
        bool isZero();
};
Galois Galois::operator=(const Galois& g){
    for(int i=0; i<8; i++){
        (this->element[i]) = g.element[i];
    }
    return *this;
}
ostream& operator<<(ostream& os, Galois g){
    os << g.element[7] << g.element[6] << g.element[5] << g.element[4] << g.element[3] << g.element[2] << g.element[1] << g.element[0];
    return os;
}
Galois Galois::operator+(const Galois& g){
    Galois a;
    for(int i=7; i>=0; i--){
        a.element[i] = (this->element[i]) ^ g.element[i];
    }
    return a;
}
Galois Galois::operator<<(int n){
    for(int j=0; j<n; j++){
        for(int i=0; i<7; i++){
            this->element[7-i] = (this->element[6-i]);
        }
        this->element[0] = 0;
    }
    
    return *this;
}
Galois Galois::operator%(const Galois& g){
    Galois a = *this;
    if((this->element[7])){
        a = (a << 1);
        for(int i=7; i>=0; i--){
            a.element[i] = (a.element[i]) ^ g.element[i];
        }
    }
    else{
        a = (a<<1);
    }
    return a;
}
Galois Galois::operator*(const Galois& g){
    bool m1[8]={0,0,0,1,1,0,1,1};
    Galois *p = new Galois[8], m(m1), temp, sum;
    *p = g;
    temp = *p;
    for(int i=1; i<8; i++){
        p+=1;
        *p = (temp%m);
        temp = *p;
    }
    p-=7;
    for(int i=0; i<8; i++){
        if(this->element[i]){
            p+=i;
            sum = sum + *p;
            p-=i;
        }
    }
    return sum;
}

int Galois::checkIndexMSB(){
    int index=0;
    for(int i=7; i>=0; i--){
        if(this->element[i]){
            index = i+1;
            break;
        }
    }
    return index;
}
bool Galois::isZero(){
    for(int i=0; i<8;i++){
        if((this->element[i])) return false;
    }
    return true;
}
Galois Galois::operator/(const Galois& g){
    Galois dividend = *this, divisor = g, results;
    int count = 0, ratio = 0;
    int degreeDividend = dividend.checkIndexMSB(), degreeDivisor = divisor.checkIndexMSB();
    do{
        if(degreeDividend < degreeDivisor){
            if(count==0){
                countDivision++;
                return dividend;
            } 
            else{
                countDivision++;
                return results;
            } 
        }
        else{
            degreeDividend = dividend.checkIndexMSB();
            ratio = degreeDividend - degreeDivisor;
            divisor = (divisor<<ratio);
            dividend = (dividend+divisor);
            results.element[ratio] = 1;
            count++;
            degreeDividend = dividend.checkIndexMSB();
            divisor = g;
        }
    }while(true);
}
Galois Galois::operator/=(const Galois& g){
    bool gx[8] = {0,0,0,1,1,0,1,1};
    Galois dividend(gx), divisor = g, results;
    int count = 0, ratio = 0;
    int degreeDividend = 9, degreeDivisor = divisor.checkIndexMSB();
    do{
        if(degreeDividend < degreeDivisor){
            if(count==0){
                countDivision++;
                return dividend;
            } 
            else{
                countDivision++;
                return results;
            } 
        }
        else{
            ratio = degreeDividend - degreeDivisor;
            divisor = (divisor<<ratio);
            dividend = (dividend+divisor);
            results.element[ratio] = 1;
            count++;
            degreeDividend = dividend.checkIndexMSB();
            divisor = g;
        }
    }while(true);
}
Galois GF(Galois a,Galois b,Galois xn2,Galois yn2,Galois xn1,Galois yn1){
    cout << "Day la test: " << a << " " << b << " " << xn2 << " " << yn2 << " " <<  xn1 << " " << yn1 << endl;
    if(b.isZero()){
        countDivision = 0;
        return yn2;
    }
    else if(countDivision==0){
        Galois q = (a/=b), r = ((q*b));
        return GF(b, r, xn1, yn1, (xn2+(q*xn1)), (yn2+(q*yn1)));
    }
    else return GF(b, (((a/b)*b)+a),xn1,yn1,xn2+((a/b)*xn1),yn2+((a/b)*yn1));
}

int main(){
    bool arrXn1[8] = {0,0,0,0,0,0,0,1};
    bool arrXn0[8] = {0,0,0,0,0,0,0,0};
    bool arrYn1[8] = {0,0,0,0,0,0,0,0};
    bool arrYn0[8] = {0,0,0,0,0,0,0,1};
    bool arr1[8]   = {0,0,0,1,1,0,1,1};
    bool arr2[8]   = {0,0,1,0,0,0,0,0};
    Galois g1(arr1), g2(arr2), gXn1(arrXn1), gXn0(arrXn0), gYn1(arrYn1), gYn0(arrYn0);
    Galois g3;
    // nghich dao nhan g2^-1 cua g2 trong GF(g1)
    g3 = GF(g1, g2, gXn1, gYn1, gXn0, gYn0);
    cout << "U(x)= " << g3 << " la nghich dao cua " << g2 << " mod(1" << g1 << ")" << endl;
    
    // Phep nhan trong GF
    bool arr4[8] = {0,0,1,0,0,1,1,0};
    bool arr5[8] = {1,0,0,1,1,1,1,0};
    Galois g4(arr4), g5(arr5);
    cout << g4*g5 << endl;

    // Phep chia trong truong GF
    // Tim nghich dao roi nhan
    cout << g1*g3 << endl;

    //GF4
    // bool arr6[8] = {0,0,0,1,0,0,1,1};
    // bool arr7[8] = {0,0,0,0,0,1,0,1};
    // Galois g6(arr6), g7(arr7);
    // g3 = GF(g6, g7, gXn1, gYn1, gXn0, gYn0);
    // cout << "U(x)= " << g3 << " la nghich dao cua " << g7 << " mod(1" << g6 << ")" << endl;
    return 0;
}

