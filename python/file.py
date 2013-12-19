import random
import os

random.seed()

#os.remove("C:\\users\\arnaud\\test.txt")
fo = open("C:\\users\\arnaud\\test.txt", "r+b")
fo.seek(16,2)
byte = bytearray(18)
byte[16] = 13
byte[17] = 10
for i in range (257254902):
    for j in range(16):
        byte[j] = random.randrange(16)
    fo.write(byte)
fo.close()
