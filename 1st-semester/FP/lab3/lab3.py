#cod 7y150101
#cerinte 10,14
#10. secventa maxima cu p=1 sau diferentele (x[j+1]-x[j]) si (x[j+2]-x[j+1])
#au semne contrare pentru j=i..i+p-2
#14.oricare doua el. consecutive au cel putin 2 cifre distincte comune
#15.secventa sub forma de munte
x=[]
import os
import time
import math
def show_list():
    """
    Afiseaza elementele din lista
    """
    print(x)
def adauga():
    """
    Adauga elemente noi in lista
    Afiseaza elementele curente din lista, inainte si dupa adaugarea elementelor noi
    """
    print()
    print("Elemente curente: ",end="")
    show_list()
    n=int(input("Cate numere vrei sa adaugi? "))
    if n!=0:
        for i in range(n):
            x.append(int(input()))
    else: pass
    show_list()
    time.sleep(1)

def doua_cf(a,b):
    #a,b doua numere naturale
    #returneaza True daca numere au cel putin doua cifre distincte comune,
    #False caz contrar
    x={0:0, 1:0, 2:0, 3:0, 4:0, 5:0, 6:0, 7:0, 8:0, 9:0}
    a=abs(a)
    b=abs(b)
    while a!=0:
        x[a%10]=x[a%10]+1
        a=a//10
    cate_ccomune=0
    while b!=0:
        if x[b%10]!=0:
            cate_ccomune=cate_ccomune+1
            x[b%10]=0
        b=b//10
    if cate_ccomune>=2:
        return True
    else: return False

def semn_contra(a,b):
    return a*b<0

def secventa_max_10():
    """
    Functia pentru gasirea secventei cu lungime maxima care verifica prop 10
    """
    n=len(x)
    if(n<3):
        return []
    secvm=[]
    secv=[]
    for i in range(n-2):
        dif1=x[i+1]-x[i]
        dif2=x[i+2]-x[i+1]
        if semn_contra(dif1,dif2):
            if not secv:
               secv=[x[i],x[i+1],x[i+2]]
            else:
                secv.append(x[i+2])
        else:
            if len(secv)>len(secvm):
                secvm=secv
            secv=[]
    
    if len(secv)>len(secvm):
        secvm=secv
    if len(secvm)<2:
        secvm=[]
    print(secvm)
    time.sleep(5)
        
def secventa_max_14():
    """
    Functia pentru gasirea secventei cu lungime maxima care verifica prop 14
    """
    n=len(x)
    if n==0:
        return []
    secvm=[]
    secv=[x[0]]
    for i in range(1,n):
        if doua_cf(x[i-1],x[i]):
            secv.append(x[i])
        else:
            if len(secv)>len(secvm):
                secvm=secv
            secv=[x[i]]
    if len(secv)>len(secvm):
        secvm=secv
    if len(secvm)<2:
        secvm=[]
    print(secvm)
    time.sleep(5)
def munte(x):
    """Functie care verifica daca o secventa x este munte
    """
    n=len(x)
    if n<3:
        return False
    i=0
    while i<n-1 and x[i]<x[i + 1]:
        i=i+1
    if i==0 or i==n-1:
        return False
    while i<n - 1 and x[i]>x[i + 1]:
        i=i+1
    return i==n - 1
def secventa_max_15():
    """
    Functia pentru gasirea secventei cu lungime maxima care verifica prop 15
    """
    n=len(x)
    lung_max = 0
    start= -1
    for i in range(n):
        for j in range(i + 2, n + 1): 
            if munte(x[i:j]):
                lung=j-i
                if lung>lung_max:
                    lung_max=lung
                    start=i
    if lung_max>0:
        print(x[start : start+lung_max])
    else:
        print([])
    time.sleep(3)
            
def comenzi():
    """
    Functia pentru efectuare comenzi pe lista
    Utilizatorul tasteaza 1,2 sau 3 in functie de nevoi
    Se efectueaza operatiile cerute de utilizator pana in momentul cererii comenzii (3)Iesire din program
    """
    while True:
        os.system('cls')
        time.sleep(1)
        print("Operatia pe care doresti sa o efectuezi: ")
        print("1.Adaugare elemente in lista")
        print("2.Cautare secventa cu lungime maxima in care fiecare doua elemente alaturate au cel putin doua cifre distincte comune")
        print("3.Cautare secventa cu lunigme maxima in care diferentele perechilor de elemente distincte au semne contrare")
        print("4.Cautare secventa cu lunigme maxima sub forma de munte")
        print("5.Iesire din program")
        nr_com=('1','2','3','4','5')
        while True:
            n=input("Numarul comenzii: ")
            if n in nr_com:
                break
            elif n=="" or n not in nr_com:
                print("Nu exista commanda ceruta!!! Alege o comanda prestabilita(1,2,3)")
       
        if n=='1':
            os.system('cls')
            adauga()
        elif n=='2':
            os.system('cls')
            print("Secventa cu lungime maxima care verifica conditia ceruta este:", end="")
            secventa_max_14()
        elif n=='3':
            os.system('cls')
            print("Secventa cu lungime maxima care verifica conditia ceruta este:", end="")
            secventa_max_10()
        elif n=='4':
            os.system('cls')
            print("Secventa cu lungime maxima care verifica conditia ceruta este:",end="")
            secventa_max_15()
        elif n=='5':
            break
#functia pentru ui
def interf():
    """
    Interfata utilizator
    Se apeleaza fara parametri
    Creaza un meniu tip consola in care user-ul are optiunea de a alege comenzi
    """
    print()
    print("Bine ai venit!")
    time.sleep(1)
    comenzi()
#pornire aplicatie
interf()





    


