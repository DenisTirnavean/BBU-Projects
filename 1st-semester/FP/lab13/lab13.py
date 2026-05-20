from math import sqrt,floor,ceil,factorial
 
#===============================================================
#problema 13
#===============================================================
"""Se da o lista de numere intregi a1,...,an. Generati toate permutarile listei pentru care
numerele au forma de munte(cresc pana la un punct de unde descresc). ex: 10, 16, 27, 18, 14, 7
"""
"""
    domeniul de definitie: elementele listei de numere numerele intregi {a1,...,an}
    spatiul de cautare: setul tututor permutarilor
    canditat: sub-lista a listei de numere cu elemente distincte {x1,...xm} m<=len(lista_numere) oricare ar fi i,j xi!=xj
    consistent: daca este ordonat strict crescator(si are posibilitatea sa scada dintr-un punct viitor)
                sau daca are deja forma de munte(are varf); xi<xi+1 or exista j astfel incat xj-1<xj>xj+1
    conditia solutie:Candidatul trebuie sa indeplineasca toate conditiile simultan pentru a fi solutie:
                        1)candidatul este o permutare a listei de numere(implicit len(candidat)==len(lista)) 
                        2)candidat consistent   
                        3)creste pana intr-un loc dupa aceea scade(are forma de munte)

"""
#recursiv
def is_munte(solutie):
    #returns true daca solutia este secventa munte
    lungime=len(solutie)
    if lungime<3:
        return False
    pozitie=0
    #cautam pozitia elementului varf
    while pozitie<lungime-1 and solutie[pozitie]<solutie[pozitie + 1]:
        pozitie+=1
    #verificam daca varful e primul sau ultimul din lista caz in care secventa nu e munte
    if pozitie==0 or pozitie==lungime-1:
        return False
    while pozitie<lungime - 1 and solutie[pozitie]>solutie[pozitie + 1]:
        #verificam daca elementele incepand de la varf pana la final strict descrescatoare 
        pozitie+=1
    return pozitie==lungime - 1 #daca am parcurs toate elementele inseamna ca avem munte
def consistent_munte(solutie):
    #return True daca solutia candidat poate deveni secventa munte
    index=0
    #la fel ca algoritmul is_munte dar verificam doar conditiile de strict cresc pana intr-un punct si strict descresc din acel punct incolo
    
    while index < len(solutie)-1 and solutie[index]<solutie[index+1]:
       index+=1
    while index < len(solutie)-1 and solutie[index]>solutie[index+1]:
        index+=1
    return index == len(solutie)-1
def is_solutie(solutie):
    #return true daca candidatul este consistent si daca respecta conditia de secventa munte
    if is_munte(solutie) and len(solutie)==len(set(solutie)):
        return True
    return False
def backtrack(solutie,lista_numere):
    #generare permutari lista_numere care au forma de munte
    pass
    solutie.append(-1)
    for item in lista_numere:
        solutie[-1]=item
        if consistent_munte(solutie):
            if is_solutie(solutie) and len(solutie)==len(lista_numere):
                print(solutie)
            else: backtrack(solutie,lista_numere)
    solutie.pop()
def secvente_munte(lista_numere):
    #Functia genereaza toate permutarile listei lista_numere care au  forma de munte
    solutie=[]
    backtrack(solutie,lista_numere)

#iterativ
from itertools import permutations

def secvente_munte_iterativ(lista_numere):
    permutari_posibile=permutations(lista_numere)
    for permutare in permutari_posibile:
        if is_solutie(permutare):
            print(permutare)

#verificare
lista_numere= [10, 16, 27, 18, 14, 7]
secvente_munte(lista_numere)