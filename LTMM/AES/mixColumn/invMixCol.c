#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef uint8_t state_t[4][4]; //[row][column]

void toHex(uint8_t input, uint8_t bin[16], char hex[16]) {
	for (int i = 0; i < 16; i++) {
		if (((input >> 4) ^ bin[i]) == 0) {
			printf("%c", hex[i]);
			break;
		}
	}
	for (int i = 0; i < 16; i++) {
		if (((input & 0x0f) ^ bin[i]) == 0) {
			printf("%c", hex[i]);
			break;
		}
	}
}

void AddRoundKey(state_t* state, state_t* RoundKey)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			(*state)[i][j] ^= (*RoundKey)[i][j];
		}
	}
}

uint8_t xtime(uint8_t x) {
	return (x & 0x80) ? ((x << 1) ^ 0x1b) : (x << 1);
}

uint8_t Multiply(uint8_t x, uint8_t y) {
	return (((y & 1) * x) ^
		((y >> 1 & 1) * xtime(x)) ^
		((y >> 2 & 1) * xtime(xtime(x))) ^
		((y >> 3 & 1) * xtime(xtime(xtime(x)))));
}

void InvMixColumns(state_t* state) {
	int i;
	uint8_t a, b, c, d;
	for (i = 0; i < 4; ++i)
	{
		a = (*state)[0][i];
		b = (*state)[1][i];
		c = (*state)[2][i];
		d = (*state)[3][i];

		(*state)[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
		(*state)[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
		(*state)[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
		(*state)[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
	}
}

int main() {

	int round = 1;

	uint8_t bin[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
	char hex[16] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };

	uint8_t key[176] = {0x0f, 0x15, 0x71, 0xc9, 0x47, 0xd9, 0xe8, 0x59, 0x0c, 0xb7, 0xad, 0x00, 0xaf, 0x7f, 0x67, 0x98,
						0xdc, 0x90, 0x37, 0xb0, 0x9b, 0x49, 0xdf, 0xe9, 0x97, 0xfe, 0x72, 0x3f, 0x38, 0x81, 0x15, 0xa7,
						0xd2, 0xc9, 0x6b, 0xb7, 0x49, 0x80, 0xb4, 0x5e, 0xde, 0x7e, 0xc6, 0x61, 0xe6, 0xff, 0xd3, 0xc6,
						0xc0, 0xaf, 0xdf, 0x39, 0x89, 0x2f, 0x6b, 0x67, 0x57, 0x51, 0xad, 0x06, 0xb1, 0xae, 0x7e, 0xc0,
						0x2c, 0x5c, 0x65, 0xf1, 0xa5, 0x73, 0x0e, 0x96, 0xf2, 0x22, 0xa3, 0x90, 0x43, 0x8c, 0xdd, 0x50,
						0x58, 0x9d, 0x36, 0xeb, 0xfd, 0xee, 0x38, 0x7d, 0x0f, 0xcc, 0x9b, 0xed, 0x4c, 0x40, 0x46, 0xbd,
						0x71, 0xc7, 0x4c, 0xc2, 0x8c, 0x29, 0x74, 0xbf, 0x83, 0xe5, 0xef, 0x52, 0xcf, 0xa5, 0xa9, 0xef,
						0x37, 0x14, 0x93, 0x48, 0xbb, 0x3d, 0xe7, 0xf7, 0x38, 0xd8, 0x08, 0xa5, 0xf7, 0x7d, 0xa1, 0x4a,
						0x48, 0x26, 0x45, 0x20, 0xf3, 0x1b, 0xa2, 0xd7, 0xcb, 0xc3, 0xaa, 0x72, 0x3c, 0xbe, 0x0b, 0x03,
						0xfd, 0x0d, 0x42, 0xcb, 0x0e, 0x16, 0xe0, 0x1c, 0xc5, 0xd5, 0x4a, 0x6e, 0xf9, 0x6b, 0x41, 0x56,
						0xb4, 0x8e, 0xf3, 0x52, 0xba, 0x98, 0x13, 0x4e, 0x7f, 0x4d, 0x59, 0x20, 0x86, 0x26, 0x18, 0x76 };

	uint8_t state[4][4] = { 0x4b, 0xb2, 0x16, 0xe2,
							0x32, 0x85, 0xcb, 0x79,
							0xf2, 0x97, 0x77, 0xac,
							0x32, 0x63, 0xcf, 0x18 };

	// printf("%d", Multiply((uint8_t)0x63, (uint8_t)0x0e));

	int in = 0;
	state_t roundKey[11];

	for (int z = 10; z >= 0; z--) {
		// round key
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				(roundKey[i][j])[z] = key[in++];
			}
		}
	}

	AddRoundKey(state, roundKey[round]);
	InvMixColumns(state);

	// print output state
	printf("\nDang HEX: ");
	for (int i = 0; i < 4; i++) {
		printf("\n");
		for (int j = 0; j < 4; j++) {
			toHex(state[i][j], bin, hex);
			printf("\t");
		}
	}

	printf("\n\nDang DEC: ");
	for (int i = 0; i < 4; i++) {
		printf("\n");
		for (int j = 0; j < 4; j++) {
			printf("%d\t", (int)state[i][j]);
		}
	}
	printf_s("\n");
	return 0;
}