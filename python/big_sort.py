import string
import re

f=open("test.txt", "r")
a=f.read(500000000)
b=[a[i:i+18] for i in range(0, len(a), 18)]
b.sort()
g=open("temp","w")
g.write(bytearray("".join(b)))
g.close()
f.close()
# for i in b:
#     print ':'.join(j.encode('hex') for j in i)

# print ':'.join(x.encode('hex') for x in a)