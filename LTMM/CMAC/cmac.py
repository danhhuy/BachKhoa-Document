import numpy as np
from aes import AES, gmul, MSB

aes = AES(mode='ecb', input_type='hex', iv='0f1571c947d9e8590cb7add6af7f6798')
Key = '0f1571c947d9e8590cb7add6af7f6798'
hexKey = int(Key, 16)
K1 = gmul(hexKey, 2)
K2 = gmul(hexKey, 3)

K  = 0x0
chunkSize = 32
addTemp = "ffffffffffffffffffffffffffffffff"

M = '0000000000000000000000000000000000000000000000000000000000000000'
Mset = [M[y-chunkSize:y] for y in range(chunkSize, len(M)+chunkSize,chunkSize)]
for i in range(len(Mset)):
    if i == len(Mset)-1:
        addTemp = int(Mset[i], 16) ^ int(addTemp, 16) ^ K1
    else:
        addTemp = int(Mset[i], 16) ^ int(addTemp, 16)
    addTemp = aes.encryption(hex(addTemp)[2:].zfill(32), Key)
    print(addTemp)
print("origTag:",addTemp)
Tag = MSB(addTemp, 32)
print("MSB Tag:", Tag)

#K = '0f1571c947d9e8590cb7add6af7f6798'
#aes = AES(mode='ecb', input_type='hex')
#cyphertext = aes.encryption(, str(K2))
#print(cyphertext)

print('Enter your text:')
M = input()
print('The text you enter:', M)
M = M.encode('utf-8')
M = M.hex()

if (len(M)%32) == 0:
    K = K1
else:
    K = K2
    while (len(M)%32) != 0:
        M = M + '0'

Mset = [M[y-chunkSize:y] for y in range(chunkSize, len(M)+chunkSize,chunkSize)]
#print(Mset)
for Mi in Mset:
    
    if Mi == Mset[-1]:
        addTemp = int(Mi, 16) ^ int(addTemp, 16) ^ K
    else:
        addTemp = int(Mi, 16) ^ int(addTemp, 16)
    addTemp = aes.encryption(hex(addTemp)[2:].zfill(32), Key)

print("origTag:",addTemp)
Tag = MSB(addTemp, 18)
print("MSB Tag:", Tag)
