DIGIT_LIMIT = 6

"""
return the value of f(n) which represents the number of 1 in the numbers between 0 and n. n belongs to the Natural
"""
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

"""
nb check the equation. We check if there is number next to nb which check also the equation
"""
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

"""
search one number verifying the equation between 10^(digit-1) and nb
"""
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

def checkNoMore(digit, nbMin, nbMax):
    global DIGIT_LIMIT
    digitIndex = DIGIT_LIMIT
    maxDigit = 10 ** digit
    nb = nbMin
    nbAdd = 10 ** (digitIndex - 1)
    while True:
        if digitIndex >= digit:
            return True
        nb = nbMin / 10 / nbAdd * nbAdd * 10 + nbAdd
        for i in range(digitIndex - 1):
            nb = nb + 9 * 10 ** i
        if nb < nbMin:
            nb = nb + (nbAdd * 10)
            if nb >= maxDigit:
                return True
        if nb >= nbMax:
            return True
        if f(nb) - nb >= 0:
            print nb, digitIndex
            return False
        nbAdd *= 10
        digitIndex += 1

"""
check if the n number verifying the equation is betwween 10^(digit-1) and 10^(digit)
"""
def getLastInStep(digit, n):
    nb = 0
    nbFound = 0
    for i in range(digit):
        nb += 9 * 10 ** i
    maxDigit = 10 ** (digit - 1)
    nbSoustract = maxDigit
    digitIndex = 1
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
            # print nb
            if not checkNoMore(digit, nb2 + nbFound2, nb):
                raise Exception("algorithm not completed")

            if nbFound == n or nbFound == 0:
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
            if f(nb1) - nb1 <= 0:
                nb3,nbFound2 = findFromLastSimple(True, nb2, temp, n - nbFound)
                nbFound += nbFound2
                if nbFound == n or nb2 / maxDigit == 1:
                    return nb3, nbFound
                else:
                    nb = nb3 - 1
                    digitIndex = 1
                    plus = False
            else:
                digitIndex += 1

"""
main function which return the n greatest number checking f(x) = x where f(x) is equal of the number of 1 in the numbers between 0 and x. x belongs to the Natural
"""
def getLast(n):
    nbFound = 0
    for i in range(10, 0, -1): # all with more than 10 digits do not check the equation
        nb,nbFound2 = getLastInStep(i,n - nbFound)
        nbFound += nbFound2
        if nbFound == n:
            return nb

def test():
    print getLastInStep(9, 1)

print getLast(2)