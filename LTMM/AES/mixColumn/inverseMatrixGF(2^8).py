import numpy as np

def multiplicationGF256(x1, x2):
    temp = np.zeros(8,dtype=np.uint8)
    sum = 0x0
    temp[0] = x1
    for i in range(1,8):
        temp[i] = temp[i-1] << 1
        if temp[i-1] & 0x80:
            temp[i] = temp[i] ^ 0x1b
    for i in range(8):
        if(x2 & 0x1):
            sum = sum ^ temp[i]
        x2 = x2 >> 1
    return sum

def DET(mat):
    if mat.shape == (2,2):
        return (multiplicationGF256(mat[0,0],mat[1,1]) ^ multiplicationGF256(mat[0,1],mat[1,0]))
    else:
        print(mat[0].shape[0])
        for x in range(len(mat[0])):
            sum = 0x0
            if x == 0:
                left = 1
                right = len(mat[0])-1
            else:
                left = x + 1
                right = x - len(mat[0])
            sum = sum + multiplicationGF256(x,DET(mat[1:][left,right]))
            return sum

print(hex(multiplicationGF256(0x26, 0x9e)))
matrix = np.array([[0x2,0x3,0x1,0x1],[0x1,0x2,0x3,0x1],[0x1,0x1,0x2,0x3],[0x3,0x1,0x1,0x2]], dtype=np.uint8)
print(DET(matrix))