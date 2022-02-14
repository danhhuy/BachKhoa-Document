#include <iostream>
#include <cstdint>
#include <string>
#include <sstream>

using namespace std;

int mbox[4][4] = {
    {2,3,1,1},
    {1,2,3,1},
    {1,1,2,3},
    {3,1,1,2}
};
string to_hex_string( const unsigned int i ) {
    stringstream s;
    s << std::hex << i;
    return s.str();
}
void addRoundKey(uint8_t arr1[4][4], uint8_t arr2[4][4], uint8_t temp[4][4])
{
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            temp[i][j] = (arr1[i][j] ^ arr2[i][j]);
        }   
    }
}
uint8_t mixSingleColumn(uint8_t r, int x) {
    if(x==1) return r;
    else if(x==2){
        uint8_t y, z;
        y = r << 1;
        z = r&(0x80);
        if(z==0x80){
            y = y ^ (0x1b);
        }
        return y;
    }
    else if(x==3){
        uint8_t x1 = r, z;
        uint8_t x2 = r << 1;
        z = r&(0x80);
        if(z==0x80){
            x2 = x2 ^ (0x1b);
        }
        return (x1 ^ x2);
    }
    return 0;
}

void mixColumns(uint8_t arr1[4][4], uint8_t temp[4][4]){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            temp[i][j] = (((mixSingleColumn(arr1[0][j],mbox[i][0]) ^ mixSingleColumn(arr1[1][j],mbox[i][1])) ^ mixSingleColumn(arr1[2][j],mbox[i][2])) ^ mixSingleColumn(arr1[3][j],mbox[i][3]));
        }
    }
}

int main()
{
    uint8_t a1[4][4] = {{0x7c,0x6b,0x01,0xd7},{0xf2,0x30,0xfe,0x63},{0x2b,0x76,0x7b,0xc5},{0xab,0x77,0x6f,0x67}};
    //uint8_t a2[4][4] = {{0x23,0x23,0x13,0x23},{0x23,0x23,0x23,0x23},{0x23,0x13,0x23,0x23},{0x23,0x23,0x23,0x23}};
    uint8_t temp[4][4];
    //addRoundKey(a1, a2, temp);
    mixColumns(a1, temp);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            cout.setf(ios::hex, ios::basefield);
            cout << to_hex_string(temp[i][j]) << " ";
        }
        cout << "\n";
    }
}