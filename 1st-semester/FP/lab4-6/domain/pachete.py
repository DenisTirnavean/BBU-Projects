import datetime
def creare_pachet(id_pachet,data_inceput, data_sfarsit, destinatie, pret):
    """
    Functie care creaza un pachet de calatorii cu id-ul id_pachet, data de inceput data_inceput, data de sfarsit data_sfarsit, destinatia destinatie si pretul pret
    input:
        id: int, >0
        data_inceput: data calendarsitica -forma [AAAA,LL,ZZ], AAAA>=2024, 1<=LL<=12 , 1<=ZZ<=31
        data_sfarsit: data calendarsitica -forma [AAAA,LL,ZZ]
        destinatie: str, nenul
        pret: float, >0
    """
    #pt list
    """"
    pachet=[]
    pachet.append(id_pachet)
    pachet.append(data_inceput)
    pachet.append(data_sfarsit)
    pachet.append(destinatie)
    pachet.append(pret)
    """
    #pt dictionary
    pachet={}
    pachet.update({"id_pachet":id_pachet})
    pachet.update({"data_inceput":data_inceput})
    pachet.update({"data_sfarsit":data_sfarsit})
    pachet.update({"destinatie":destinatie})
    pachet.update({"pret":pret})
    return pachet
def get_id_pachet(pachet):
    """
    Functia care obtine id-ul intreg al pachetului de calatorii pachet
    input:
        pachet- un pachet de calatorii cu id_pachet numar intreg
    output:
        id_pachet- id-ul intreg al pachetului pachet
    """
    #pt list
    #return pachet[0]
    #pt dictionary 
    return pachet["id_pachet"]
def tipareste(pachet):
    print("Id pachet: "+str(get_id_pachet(pachet)))
    print(str(get_data_inceput_pachet(pachet))+"===>"+str(get_data_sfarsit_pachet(pachet)))
    print("Destinatia: "+str(get_destinatie_pachet(pachet)))
    print("Pretul: "+str(get_pret_pachet(pachet))+" lei")
    print()
def get_data_inceput_pachet(pachet):
    """    
    Functia care obtine data de inceput a pachetului de calatorii pachet
    input:
        pachet- un pachet de calatorii cu data de inceput valida numar intreg
    output:
        data_inceput- data de inceput a pachetului pachet, tip data calendaristica forma AAAA-LL-ZZ
    """
    #pt list
    #return pachet[1]
    #pt dictionary 
    return pachet["data_inceput"]
def get_data_sfarsit_pachet(pachet):
    """    
    Functia care obtine data de sfarsit a pachetului de calatorii pachet
    input:
        pachet- un pachet de calatorii cu data de sfarsit valida numar intreg
    output:
        data_sfarsir- data de sfarsit a pachetului pachet, tip data calendaristica forma AAAA-LL-ZZ
    """
    #pt list
    #return pachet[2]
    #pt dictionary 
    return pachet["data_sfarsit"]
def get_destinatie_pachet(pachet):
    """
    Functia care obtine destinatia destinatie a pachetului de calatorii pachet
    input:
        pachet- un pachet de calatorii cu destinatie str nenul
    output:
        destinatie- destinatia pachetului de calatorie, str nenul
    """
    #pt list
    #return pachet[3]
    #pt dictionary 
    return pachet["destinatie"]
def get_pret_pachet(pachet):
    """
    Functia care obtine pretul pret al unui pachet de calatorii pachet
    input:
        pachet- un pachet de calatorii
    output:
        pret- pretul float al pachetului de calatorii pachet
    """
    #pt list
    #return pachet[4]
    #pt dictionary 
    return pachet["pret"]
def get_duration(pachet):
    """Functie care returneaza durata unui pachet de calatorii in zile

    input:
        pachet (_dictionary): un pachet de calatorii
    output:
        duration(int): durata in zile a pachetului de calatorii
    """
    data_inceput=get_data_inceput_pachet(pachet)
    data_sfarsit=get_data_sfarsit_pachet(pachet)
    duration=(data_sfarsit-data_inceput).days
    return duration
def lista_id(oferte):
    """
    Functia returneaza lista id-urilor pachetelor de calatorie din lista de oferte
    input:
        oferte- lista de oferte
    output:
        lista_iduri- lista formata id_pachet al fiecarui pachet, integer list
    """
    lista_iduri=[]
    for i in oferte:
        id=get_id_pachet(i)
        lista_iduri.append(id)
    return lista_iduri
