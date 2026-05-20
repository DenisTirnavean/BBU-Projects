from math import sin
print(sin(30))
def sinus(n,precision):
    factorial=2*precision+1
    Taylor=0
    power=n
    if precision%2: semn=1
    else: semn=-1
    #power
    index=factorial
    while index:
        power*=power
        index-=1
    #factorial
    index=factorial
    while index:
        factorial*=index
        index-=1
    Taylor=(semn/factorial)*power
    return Taylor
x=30
precizie=100
for iteratie in range(precizie):
    sinnus=sinus(x,iteratie)
print(sinnus)