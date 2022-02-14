// Including dependancies
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
// Array to hold 16 keys
string round_keys[16];
// String to hold the plain text
string pt;
// Function to convert a number in decimal to binary
string convertDecimalToBinary(int decimal)
{
	string binary;
    while(decimal != 0) {
		binary = (decimal % 2 == 0 ? "0" : "1") + binary; 
		decimal = decimal/2;
	}
	while(binary.length() < 4){
		binary = "0" + binary;
	}
    return binary;
}
// Function to convert a number in binary to decimal
unsigned long long int convertBinaryToDecimal(string binary)
{
    unsigned long long int decimal = 0;
	unsigned long long int counter = 0;
	unsigned long long int size = binary.length();
	for(int i = size-1; i >= 0; i--)
	{
    	if(binary[i] == '1'){
        	decimal += pow(2, counter);
    	}
    counter++;
	}
	return decimal;
}

string IP(string pt){
    int initial_permutation[64] = { 
	58,50,42,34,26,18,10,2, 
	60,52,44,36,28,20,12,4, 
	62,54,46,38,30,22,14,6, 
	64,56,48,40,32,24,16,8, 
	57,49,41,33,25,17,9,1, 
	59,51,43,35,27,19,11,3, 
	61,53,45,37,29,21,13,5, 
	63,55,47,39,31,23,15,7 
	};
    string perm = ""; 
	for(int i = 0; i < 64; i++){ 
		perm += pt[initial_permutation[i]-1]; 
	}
    return perm;
}

string invIP(string ct){
    int inverse_permutation[64]= { 
	40,8,48,16,56,24,64,32, 
	39,7,47,15,55,23,63,31, 
	38,6,46,14,54,22,62,30, 
	37,5,45,13,53,21,61,29, 
	36,4,44,12,52,20,60,28, 
	35,3,43,11,51,19,59,27, 
	34,2,42,10,50,18,58,26, 
	33,1,41,9,49,17,57,25 
	};
    string perm = ""; 
	for(int i = 0; i < 64; i++){ 
		perm += pt[inverse_permutation[i]-1]; 
	}
    return perm;
}
int main(){ 
	// A 64 bit key  
	pt = "0000000000000000100000001000000000000000000000001000000010000000";
    cout << "Plain text: " <<  pt << endl;
    // string tmp =  IP(pt);
    // cout << "After Ip: " << tmp << endl;
    cout << "After invIP: " << invIP(pt) << endl;
} 