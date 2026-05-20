
#cerinta 1
#calculati suma a n numere naturale
def sum_of_n()->None:
    n = int(input("Numarul n="))
    sum = 0
    for index in range(n):
        print(f"Al {index+1}-lea numar = ",end="")
        sum+=int(input())
        print()
    print(sum)

#cerinta 2
#verificati daca un numar citit este prim
def is_prime(n: int)->bool:
    if n%2==0 and n!=2:
        return False
    if n<2: 
        return False
    i = 3
    while(i*i<=n):
        if(n%i):
            return False
        else:
            i+=2
    return True

#cerinta 3
#calculati cel mai mare divizor al doua numere
def gcd(number1: int, number2:int)->bool:
    remain = number1%number2
    while(remain!=0):
        number1 = number2
        number2 = remain
        remain = number1%number2
    return number2

#cazuri de testare
assert(is_prime(5) == True)
assert(is_prime(10) == False)
assert(is_prime(2)==True)
assert(is_prime(1)==False)
assert(gcd(10,5)==5)
assert(gcd(9,2)==1)
assert(gcd(100,25)==25)