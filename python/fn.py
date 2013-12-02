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

def test(n):
    for i in range(1, n):
        if f(i) == i:
            print i
