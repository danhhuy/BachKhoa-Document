from matplotlib import pyplot as plt
from matplotlib.ticker import NullFormatter
import math

pi = 3.14159265358979323846
t = 0
t_run = 0
w1 = 0.5*pi
chuKy = (2*pi)/w1
t_thuan = 7 * chuKy /3
t_nguoc =  chuKy /3
t_quet = t_thuan + t_nguoc
y_thuan = []
y_nguoc = []
t_th = []
t_ng = [] 
def fx(x):
    return 2*math.cos(w1*x + pi/3)

for i in range(0,1000000):
    t += 0.0001
    t_run += 0.0001
    if t > t_quet:
        t = 0
    if t <= t_thuan:
        y_thuan.append(fx(t_run))
        t_th.append(t)
    elif (t > t_thuan) & (t <= t_quet):
        y_nguoc.append(fx(t_run))  
        t_ng.append(t_thuan-(t_thuan/t_nguoc)*(t-t_thuan))
plt.figure()
plt.scatter(t_th,y_thuan,marker='.',c='blue', label='first')
plt.scatter(t_ng,y_nguoc,marker='.',c='red', label='second', alpha=0.3)
plt.grid(True)
plt.show()  