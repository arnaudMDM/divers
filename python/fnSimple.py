def digit(n):
    res = []
    while True:
        res.append(n % 10)
        n = n / 10
        if n == 0:
            break
    return res

def f(n):
    res=0
    for i in range(n):
        listDigit = digit(i)
        for j in listDigit:
            if j == 1:
                res += 1
        if i == res:
            print i
            
f(100000000)