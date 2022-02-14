from aes import AES, matrix2HexString, hexString2Matrix
import numpy as np

aes = AES(mode='ecb', input_type='hex', iv='000102030405060708090A0B0C0D0E0F')
key = '000102030405060708090a0b0c0d0e0f'

print('Enter your text:')
plaintext = input()
print('The text you enter:', plaintext)
temp = ''
cyphertext = []

chunk_size = 8
dataset = [plaintext[y-chunk_size:y] for y in range(chunk_size, len(plaintext)+chunk_size,chunk_size)]
for data in dataset:
    cyphertext.append(aes.encryption(data, key))

print('After encrypting:')
cyph = ''
for cypher in cyphertext:
    cyph += cypher
print(cyph)

plain = ''
for data in cyphertext:
    plain += aes.decryption(data, key)
    
print('After decrypting:',plain)
