from aes import AES, matrix2HexString, hexString2Matrix
import cv2
import numpy as np

aes = AES(mode='ecb', input_type='hex', iv='000102030405060708090A0B0C0D0E0F')

key = '000102030405060708090a0b0c0d0e0f'
origImg = cv2.imread('./encryptImg/testImg1.jpg', 0)
height, width = origImg.shape[0], origImg.shape[1]
encpImg = np.zeros((height,width), np.uint8)
decpImg = np.zeros((height,width), np.uint8)
for i in range(0, height, 4):
    if(i+4)>height:
        continue
    for j in range(0, width, 4):
        if(j+4)>width:
            continue
        data = matrix2HexString(origImg[i:i+4,j:j+4])
        cyphertext = aes.encryption(data, key)
        #print(cyphertext)
        encpImg[i:i+4,j:j+4] = hexString2Matrix([cyphertext], tag=0)

for i in range(0, height, 4):
    if(i+4)>height:
        continue
    for j in range(0, width, 4):
        if(j+4)>width:
            continue
        data = str(matrix2HexString(encpImg[i:i+4,j:j+4]))
        plaintext = aes.decryption(data, key)
        #print(plaintext)
        decpImg[i:i+4,j:j+4] = hexString2Matrix(plaintext, tag=1)

cv2.imshow('origImg', origImg)
cv2.imshow('encryptImg', encpImg)
cv2.imshow('decryptImg', decpImg)
cv2.waitKey(0)