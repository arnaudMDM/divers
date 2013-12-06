from __future__ import division
from pylab import *
import matplotlib.pyplot as plt
# import numpy as np

def digit(n):
    res = []
    while True:
        res.append(n % 10)
        n = n // 10
        if n == 0:
            break
    return res 

def f(n):
    res = 0
    tab = []
    for i in range(n):
        listDigit = digit(i)
        for j in listDigit:
            if j == 1:
                res += 1
        tab.append((res - i) / (10 ** (len(listDigit) - 1)))
    return tab
            
nbLimit = 10000000

fig = plt.figure()
ax = fig.add_subplot(1,1,1)

p1, = ax.plot([1,nbLimit] ,[0,0], 'r-')
p2, = ax.plot(f(nbLimit), color='blue', lw=2, label = r'$g(a_na_{n-1}...a_0) = \frac{a_n * 10^n + a_{n-1} * 10^{n-1} + ... + a_0}{10^n}$')
# legend([p2],[r'$g(a_na_{n-1}...a_0) = \frac{a_n * 10^n + a_{n-1} * 10^{n-1} + ... + a_0}{10^n}$'])
legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2, mode="expand", borderaxespad=0.)
plt.xlabel('log(n)')

ax.set_xscale('log')

show()
