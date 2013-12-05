
def digit(n):
    res = []
    while True:
        res.append(n % 10)
        n = n / 10
        if n == 0:
            break
    return res

def f(n,value, n2):
    res=value
    for i in range(n, n2,-1):
        listDigit = digit(i)
        for j in listDigit:
            if j == 1:
                res -= 1
        if i-1 == res:
            print i-1

# min=199981 max=200001 moy=10 (6 digits) maxHigh=1 coef premiere courbe=0.5000450040503646
# min=1599981 max=2600001 moy=500010 (7 digits) maxHigh=200001 coef premiere courbe=0.6000054000486005
# min=13199998 max=35200001 moy=11000001.5 (8 digits) maxHigh=4200001 and 1 coef premiere courbe=0.6000004500003375
# 1111111110 peut etre le dernier