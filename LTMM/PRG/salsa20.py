class Salsa:
    def __init__(self,r=20):
        assert r >= 0
        self._r = r # number of rounds
        self._mask = 0xffffffff # 32-bit mask

    def __call__(self,key=[0]*32,nonce=[0]*8,block_counter=[0]*8):
        assert len(key) == 32
        assert len(nonce) == 8
        assert len(block_counter) == 8
        
        # init state
        k = [self._littleendian(key[4*i:4*i+4]) for i in range(8)]
        n = [self._littleendian(nonce[4*i:4*i+4]) for i in range(2)]
        b = [self._littleendian(block_counter[4*i:4*i+4]) for i in range(2)]
        c = [0x61707865, 0x3320646e, 0x79622d32, 0x6b206574]

        s = [c[0], k[0], k[1], k[2], 
            k[3], c[1], n[0], n[1],
            b[0], b[1], c[2], k[4], 
            k[5], k[6], k[7], c[3]]

        # the state
        self._s = s[:]

        for i in range(self._r):
            self._round()

        # add initial state to the final one
        self._s = [(self._s[i] + s[i]) & self._mask for i in range(16)]

        return self._s

    def _littleendian(self,b):
        assert len(b) == 4
        return b[0] ^ (b[1] << 8) ^ (b[2] << 16) ^ (b[3] << 24)

    def _round(self):

        # quarterround 1
        self._s[ 4] ^= self._rotl32((self._s[ 0] + self._s[12]) & self._mask, 7)
        self._s[ 8] ^= self._rotl32((self._s[ 0] + self._s[ 4]) & self._mask, 9)
        self._s[12] ^= self._rotl32((self._s[ 4] + self._s[ 8]) & self._mask,13)
        self._s[ 0] ^= self._rotl32((self._s[ 8] + self._s[12]) & self._mask,18)

        # quarterround 2
        self._s[ 9] ^= self._rotl32((self._s[ 1] + self._s[ 5]) & self._mask, 7)
        self._s[13] ^= self._rotl32((self._s[ 5] + self._s[ 9]) & self._mask, 9)
        self._s[ 1] ^= self._rotl32((self._s[ 9] + self._s[13]) & self._mask,13)
        self._s[ 5] ^= self._rotl32((self._s[ 1] + self._s[13]) & self._mask,18)

        # quarterround 3
        self._s[14] ^= self._rotl32((self._s[ 6] + self._s[10]) & self._mask, 7)
        self._s[ 2] ^= self._rotl32((self._s[10] + self._s[14]) & self._mask, 9)
        self._s[ 6] ^= self._rotl32((self._s[ 2] + self._s[14]) & self._mask,13)
        self._s[10] ^= self._rotl32((self._s[ 2] + self._s[ 6]) & self._mask,18)

        # quarterround 4
        self._s[ 3] ^= self._rotl32((self._s[11] + self._s[15]) & self._mask, 7)
        self._s[ 7] ^= self._rotl32((self._s[ 3] + self._s[15]) & self._mask, 9)
        self._s[11] ^= self._rotl32((self._s[ 3] + self._s[ 7]) & self._mask,13)
        self._s[15] ^= self._rotl32((self._s[ 7] + self._s[11]) & self._mask,18)

        # transpose
        self._s = [self._s[ 0], self._s[ 4], self._s[ 8], self._s[12],
                self._s[ 1], self._s[ 5], self._s[ 9], self._s[13],
                self._s[ 2], self._s[ 6], self._s[10], self._s[14],
                self._s[ 3], self._s[ 7], self._s[11], self._s[15]]

    def _rotl32(self,w,r):
        # rotate left for 32-bits
        return ( ( ( w << r ) & self._mask) | ( w >> ( 32 - r ) ) ) 

def print_state(s):
    assert len(s) == 16
    for i in range(4):
        print ("{:08x} {:08x} {:08x} {:08x}".format(s[4*i],s[4*i+1],s[4*i+2],s[4*i+3]))

if __name__ == '__main__':
    salsa20 = Salsa()

    key = [0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0]
    print_state(salsa20(key, [0,0,0,0,0,0,0,0], [0,0,0,0,0,0,0,0]))
    
    #vectors = [ 
    #    [ range(1,33), [3,1,4,1,5,9,2,6], [7,0,0,0,0,0,0,0], 
    #    [ 0xb9a205a3,0x0695e150,0xaa94881a,0xadb7b12c,
    #    0x798942d4,0x26107016,0x64edb1a4,0x2d27173f,
    #    0xb1c7f1fa,0x62066edc,0xe035fa23,0xc4496f04,
    #    0x2131e6b3,0x810bde28,0xf62cb407,0x6bdede3d ] ] ]
    #for i in range(len(vectors)):
    #    v = vectors[i]
    #    s =  salsa20(v[0],v[1],v[2]) 
    #    print_state(s)
    #    assert s == v[3]
    #print ("All tests passed!")