###problema 8/fisier lab2
import time
# pentru un numar n gasiti numarul m - nr maxim format din cifrele lui n
# ex: n=3658, m=8653
n=int(input("Numarul n este="))
#lista cu cifrele numarului n, luam pe rand maximul, adaugam in m pe prima
#pozitie cifra maxima
#anulam maximul curent, continuam pana cand nu mai avem cifre valide
x=[]
while n!=0:
    u=n%10
    x.append(u)
    n=n//10
m=0
maxi=0
while maxi!=-1:
    maxi=-1
    for i in x:
        if i >= maxi:
            maxi=i
            pozitie=x.index(maxi)
    if(maxi!=-1):
         m=m*10+maxi
         x[pozitie]=-1
print("Numarul m cerut este: "+str(m))
time.sleep(0)
    

