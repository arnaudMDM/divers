import string
from time import time

nbIntersection = 0
t0 = 0
t1 = 0
t2 = 0
t3 = 0

f = open("question.txt", "r")
liste = string.split(f.read(),",")
f.close()
dic = {int(liste[i]): i for i in range(len(liste))}
liste2 = []
for i in range(1, len(liste) / 10 + 1):
    temp = time()
    # print i
    nb = len(liste2)
    n = dic[i]
    t0 += time() - temp
    temp = time()
    for i in liste2:
        if n < i:
            nbIntersection += nb
            print len(liste2) - nb
            break
        nb -= 1
    t1 += time() - temp
    temp = time()
    liste2.insert(len(liste2) - nb, n)
    t2 += time() - temp

print "t0: ", t0
print "t1: ", t1
print "t2: ", t2
print nbIntersection