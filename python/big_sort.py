# arnaud
import string
import os

nbFile = 100
f = open("test.txt", "rb")
for i in range(nbFile):
    a = f.read(99999990)
    b = [a[j:j+18] for j in range(0, len(a), 18)]
    b.sort()
    # print '\n'.join(':'.join(x.encode('hex') for x in r) for r in b)
    g = open("temp0"+str(i),"wb")
    g.write(bytearray("".join(b)))
    g.close()
f.close()

i = 0
while nbFile > 1:
    for j in range(0, nbFile / 2 * 2, 2):
        f = open("temp" + str(i) + str(j), "rb")
        g = open("temp" + str(i) + str(j + 1),"rb")
        h = open("temp" + str(i + 1) + str(j / 2), "wb")
        a = f.read(18)
        b = g.read(18)
        while True:
            if not a and not b:
                break
            elif not a:
                h.write(bytearray(b))
                h.write(bytearray(g.read()))
                break
            elif not b:
                h.write(bytearray(a))
                h.write(bytearray(f.read()))
                break
            elif a < b:
                h.write(bytearray(a))
                a = f.read(18)
            else:
                h.write(bytearray(b))
                b = g.read(18)
        f.close()
        g.close()
        h.close()
        os.remove("temp" + str(i) + str(j))
        os.remove("temp" + str(i) + str(j + 1))
    if nbFile % 2 > 0:
        os.rename("temp" + str(i) + str(nbFile - 1), "temp" + str(i + 1) + str(nbFile / 2))
        nbFile = nbFile / 2 + 1
    else:
        nbFile = nbFile / 2
    i += 1
