import numpy as np
import galois

GF256 = galois.GF(2**8, irreducible_poly=[1,0,0,0,1,1,0,1,1])
print(GF256.properties)
GF256.display("poly")
a = GF256("x^7+x+1")
b = GF256("x^12 + 1")
print(a+b)
print(a-b)
print(a*b)
print(a/b)
print(b)
print(GF256(1)/a)
print(a ** 3)

GF16 = galois.GF(2**4)
print(GF16.properties)