import sys

p, q = map(int, input().split())

x = 0
mnX = 0

d = 1
while True :
    x -= p
    mnX = min(mnX, x)
    if p <= q * d**5 :
        break
    
    x += q * d**5
    d += 1

x = -mnX

lo = 1
hi = 42627697484524538000000000

tmp = 10**99

while lo + 1 < hi :
    mid = (lo + hi) // 2

    n5 = (2*mid**6 + 6*mid**5 + 5*mid**4 - mid**2) // 12
    v = x - mid*p + q*n5

    if v >= tmp :
        hi = mid
    else :
        lo = mid

print(x)
print(hi)
