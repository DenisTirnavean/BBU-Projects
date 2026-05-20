#Functii de sortari
#selecteaza minimul si interschimba cu primul element nesortat
def selection_sort(list,*, key=lambda x: x,reversed=False):
    """Implementare a algoritmului de sortare prin selectie
    Sortare in-place a listei dupa key
    Args:
        list (list): o lista
        key (functie): criteriul de sortare
        reversed (bool, optional): Ordinea in care se ordoneaza lista(True=Descrescator/ False=Crescator)
    """
    for i in range(0,len(list)-1):
        first=i
        for j in range(i+1,len(list)):
           if key(list[j])<key(list[first]):
               first=j
        if i<first:
            list[i],list[first]=list[first],list[i] 
    if reversed==True:
        list.reverse()
#bubble sort care parcurge lista both ways :(
def shake_sort(list,*,key=lambda x: x,reversed=False):
    """Implementare a algoritmul de shake sort
    Sortare in-place a listei dupa key

    Args:
        list (list): o lista
        key (functie): criteriul de sortare
        reversed (bool, optional): Ordinea in care se ordoneaza lista(True=Descrescator/ False=Crescator)
    """
    i=0
    lenght=len(list)
    while i<lenght:
        for j in range(i+1,len(list)):
            if key(list[j])<key(list[j-1]):
                list[j],list[j-1]=list[j-1],list[j]
        lenght-=1
        for k in range(lenght-1,i,-1):
            if key(list[k])<key(list[k-1]):
                list[k],list[k-1]=list[k-1],list[k]
        i+=1
    if reversed==True:
        list.reverse()
        
#teste sortari
def test_selection():
    lista=[10,9,8,12,3,2,1]
    selection_sort(lista)
    for i in range(1,len(lista)):
        assert lista[i]>lista[i-1]
    oameni=[
        {"nume": "Ionica" , "varsta" : 18},
        {"nume": "Gigel" , "varsta" : 15},
        {"nume": "Andrei" , "varsta" : 98},
        {"nume": "Vasile" , "varsta" : 19},
        {"nume": "Gheorghe" , "varsta" : 12},
        {"nume": "Florin" , "varsta" : 21}
    ]
    selection_sort(oameni,key=lambda x: x["nume"])
    assert oameni==[
        {"nume": "Andrei" , "varsta" : 98},
        {"nume": "Florin" , "varsta" : 21},
        {"nume": "Gheorghe" , "varsta" : 12},
        {"nume": "Gigel" , "varsta" : 15},
        {"nume": "Ionica" , "varsta" : 18},
        {"nume": "Vasile" , "varsta" : 19},
    ]
    selection_sort(oameni,key=lambda x: x['varsta'])
    assert oameni==[
        {"nume": "Gheorghe" , "varsta" : 12},
        {"nume": "Gigel" , "varsta" : 15},
        {"nume": "Ionica" , "varsta" : 18},
        {"nume": "Vasile" , "varsta" : 19},
        {"nume": "Florin" , "varsta" : 21},
        {"nume": "Andrei" , "varsta" : 98},
    ]
    selection_sort(oameni,key=lambda x: x['varsta'],reversed=True)
    assert oameni==[
        {"nume": "Andrei" , "varsta" : 98},
        {"nume": "Florin" , "varsta" : 21},
        {"nume": "Vasile" , "varsta" : 19},
        {"nume": "Ionica" , "varsta" : 18},
        {"nume": "Gigel" , "varsta" : 15},
        {"nume": "Gheorghe" , "varsta" : 12}
    ]

    
def test_shake():
    lista=[10,9,8,12,3,2,1,999,0]
    shake_sort(lista)
    for i in range(1,len(lista)):
        assert lista[i]>lista[i-1]
    lista=[10,9,8,12,3,2,1,999,0]
    shake_sort(lista,reversed=True)
    for i in range(1,len(lista)):
        assert lista[i]<lista[i-1]
    oameni=[
        {"nume": "Ionica" , "varsta" : 18},
        {"nume": "Gigel" , "varsta" : 15},
        {"nume": "Andrei" , "varsta" : 98},
        {"nume": "Vasile" , "varsta" : 19},
        {"nume": "Gheorghe" , "varsta" : 12},
        {"nume": "Florin" , "varsta" : 21}
    ]
    shake_sort(oameni,key=lambda x: x["nume"])
    assert oameni==[
        {"nume": "Andrei" , "varsta" : 98},
        {"nume": "Florin" , "varsta" : 21},
        {"nume": "Gheorghe" , "varsta" : 12},
        {"nume": "Gigel" , "varsta" : 15},
        {"nume": "Ionica" , "varsta" : 18},
        {"nume": "Vasile" , "varsta" : 19},
    ]
    shake_sort(oameni,key=lambda x: x['varsta'])
    assert oameni==[
        {"nume": "Gheorghe" , "varsta" : 12},
        {"nume": "Gigel" , "varsta" : 15},
        {"nume": "Ionica" , "varsta" : 18},
        {"nume": "Vasile" , "varsta" : 19},
        {"nume": "Florin" , "varsta" : 21},
        {"nume": "Andrei" , "varsta" : 98},
    ]
    selection_sort(oameni,key=lambda x: x['varsta'],reversed=True)
    assert oameni==[
        {"nume": "Andrei" , "varsta" : 98},
        {"nume": "Florin" , "varsta" : 21},
        {"nume": "Vasile" , "varsta" : 19},
        {"nume": "Ionica" , "varsta" : 18},
        {"nume": "Gigel" , "varsta" : 15},
        {"nume": "Gheorghe" , "varsta" : 12}
    ]
    shake_sort(oameni,key=lambda x: x['varsta'],reversed=True)
    assert oameni==[
        {"nume": "Andrei" , "varsta" : 98},
        {"nume": "Florin" , "varsta" : 21},
        {"nume": "Vasile" , "varsta" : 19},
        {"nume": "Ionica" , "varsta" : 18},
        {"nume": "Gigel" , "varsta" : 15},
        {"nume": "Gheorghe" , "varsta" : 12}
    ]

test_selection()
test_shake()

