def isBlumInteger(n):
     
    prime = [True]*(n + 1)
 
    # to store prime numbers from 2 to n
    i = 2
    while (i * i <= n):
 
        # If prime[i] is not
        # changed, then it is a prime
        if (prime[i] == True) :
 
            # Update all multiples of p
            for j in range(i * 2, n + 1, i):
                prime[j] = False
        i = i + 1
     
    # to check if the given odd integer
    # is Blum Integer or not
    for i in range(2, n + 1) :
        if (prime[i]) :
            # checking the factors
            # are of 4t+3 form or not
            if ((n % i == 0) and
                        ((i - 3) % 4) == 0):
                q = int(n / i)
                return (q != i and prime[q]
                       and (q - 3) % 4 == 0)
    return False

for x in range(9900,10000,1):
    if (isBlumInteger(x)):
        print(x)