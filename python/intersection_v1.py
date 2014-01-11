import string

nbIntersection = 0

f = open("question.txt", "r")
liste = string.split(f.read(),",")
f.close()
dic = {int(liste[i]): i for i in range(len(liste))}
liste2 = []
length = 0
for i in range(1, len(liste) + 1):
    n = dic[i]
    index = length / 2
    lenthIter = index
    fin = False
    if lenthIter == 0:
        lenthIter = 1
    down = False
    up = False
    while True:
        if lenthIter > 1:
            lenthIter /= 2

        if index == length:
            liste2.append(n)
            break
        elif index < 0:
            liste2.insert(0, n)
            nbIntersection += length
            break
        elif liste2[index] < n:
            if lenthIter == 1 and down:
                liste2.insert(index + 1, n)
                nbIntersection += length - index + 1
                break
            index += lenthIter
            down = False
            up = True
        else:
            if lenthIter == 1 and up:
                liste2.insert(index + 1, n)
                nbIntersection += length - index
                break
            index -= lenthIter
            down = True
            up = False
    length += 1

print nbIntersection