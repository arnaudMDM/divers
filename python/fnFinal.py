DIGIT_LIMIT = 6

def f(n):
    if n == 0:
        return 0

    nbDigit = 0
    temp = n / 10
    lastDigit = 0
    while temp != 0:
        nbDigit += 1
        lastDigit = temp % 10
        temp = temp / 10

    if lastDigit == 0:
        return 1

    res = nbDigit * 10 ** (nbDigit - 1)
    num = 10 ** nbDigit

    if lastDigit > 1:
        res = res * lastDigit + num + f(n - (num * lastDigit)) 
    else:
        res = res + n - num + 1 + f(n - num)
    return res

def findMaxDigit():
    index = 0
    while True:
        nb = 0
        for i in range(index + 1):
            nb += 9 * 10 ** i
        if f(nb) - nb >= 0:
            return index + 1
        index += 1

def getAllNear(nb, n):
    nbFound = 1
    while True:
        if nbFound == n:
            return nb, nbFound
        nb -= 1
        if f(nb) - nb != 0:
            break
        else:
            nbFound += 1
    return nb + 1, nbFound

def findFromLastSimple(sign,nb,nbSoustract,n):
    if sign:
        check = lambda x: f(x) - x <= 0 
    else:
        check = lambda x: f(x) - x >= 0
    nbFound = 0
    nb2 = 0
    while True:
        nb -= nbSoustract
        if check(nb):
            nb += nbSoustract
            nbSoustract /= 10
            if nbSoustract == 0: # it means that we have found one solution because there is no more digit below
                nb -= 1
                if f(nb) - nb != 0: # just in case the algo is wrong
                    raise Exception("algorithm not working")
                nb2, nbFound2 = getAllNear(nb, n - nbFound)
                nbFound += nbFound2
                if nbFound == n:
                    return nb2, nbFound
                else:
                    nb = nb2 - 1
                    return nb2, nbFound
        elif nb / nbSoustract == 1: 
            return nb2, nbFound

def getLastInStep(digit, n):
    nb = 0
    nb2 = 0
    nbFound = 0
    for i in range(digit):
        nb += 9 * 10 ** i
    nbSoustract = 10 ** (digit - 1)
    global DIGIT_LIMIT
    digitIndex = DIGIT_LIMIT
    plus = False

    if f(nb) - nb == 0:
        nb2, nbFound = getAllNear(nb, n)
        if nb2 != -1:
            return nb2, nbFound
        else:
            nb -= nbFound
            plus = True
    elif f(nb) - nb > 0:
        plus = True
        nb = nb % nbSoustract + nbSoustract + 1

    while True:
        if not plus:
            nb2,nbFound2 = findFromLastSimple(False, nb, nbSoustract, n - nbFound)
            nbFound += nbFound2
            if nbFound == n:
                return nb2, nbFound
            else:
                nb = nb2 - 1
                plus = True
        else:
            if digitIndex > digit:
                return -1, nbFound
            temp = 10 ** (digitIndex - 1)
            nb1 = nb / 10 / temp * temp * 10
            nb2 = nb / 10 / temp * temp *10 + temp
            for i in range(digitIndex - 1):
                nb1 = nb1 + 9 * 10 ** i
                nb2 = nb2 + 9 * 10 ** i
            if f(nb1) - nb1 < 0:
                nb2,nbFound2 = findFromLastSimple(True, nb2, temp, n - nbFound)
                nbFound += nbFound2
                if nbFound == n or nb1 / temp == 0:
                    return nb2, nbFound
                else:
                    nb = nb2 - 1
                    digitIndex = DIGIT_LIMIT
                    plus = False
            else:
                digitIndex += 1

def getLast(n):
    digit = findMaxDigit()
    nbFound = 0
    for i in range(digit, 0, -1):
        nb,nbFound2 = getLastInStep(i,n - nbFound)
        nbFound += nbFound2
        if nbFound == n:
            print nb
            break
