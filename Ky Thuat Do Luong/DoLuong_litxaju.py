from matplotlib import pyplot as plt
from matplotlib.ticker import NullFormatter
import math

pi = 3.14159265358979323846
t = 0
w1 = 2*pi
w2 = pi
x = []
y = []
for i in range(0,100000):
    t += 0.0001
    x.append(2*math.cos(w1*t + 11*pi/4))

t = 0
for i in range(0,100000):
    t += 0.0001
    y.append(2*math.cos(w2*t - 3*pi/2))

plt.figure()
plt.scatter(x,y, marker='.')
plt.grid(True)
plt.show()    


