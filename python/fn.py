
def digit(n):
    res = []
    while True:
        res.append(n % 10)
        n = n / 10
        if n == 0:
            break
    return res

def printMax(listHaut, listBas, positif):
    if listHaut != [] or listBas != []:
        if positif:
            print "MAX: ", max(listHaut)
        else:
            print "MIN: ", min(listBas)

def f(n):
    listBas = []
    listHaut = []
    res = 0
    plus = False
    positif = False
    maxValue = 0
    for i in range(1, n + 1):
        listDigit = digit(i)
        for j in listDigit:
            if j == 1:
                res += 1
        if i == res:
            print "equal: ", i
            printMax(listHaut,listBas,positif)
            listHaut=[]
            listBas=[]
        elif plus:
            if (res - i > 0 and not positif) or (res - i < 0 and positif):
                printMax(listHaut,listBas,positif)
                positif = not positif
                listHaut = []
                listBas = []

            if res - i < maxValue:
                # print "haut: ", i-1
                listHaut.append(i-1)
                plus = False
        elif not plus:
            if (res - i > 0 and not positif) or (res - i < 0 and positif):
                printMax(listHaut,listBas,positif)
                positif = not positif
                listHaut = []
                listBas = []

            if res - i > maxValue:
                # print "bas: ", i-1
                listBas.append(i-1)
                plus = True
        maxValue = res - i
