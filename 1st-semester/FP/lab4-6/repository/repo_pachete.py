from validator.validator import *

def set_data_inceput(pachet,new_date):
    """Functia de setare data_inceput pachet
    input:
        pachet(dictionar): pachet de calatorie
        new_date(data calendaristica): noua data de inceput
    """
    pachet["data_inceput"]=new_date
def set_data_sfarsit(pachet,new_date):
    """Functia de setare data_sfarsit pachet
    input:
        pachet(dictionar): pachet de calatorie
        new_date(data calendaristica): noua data de sfarsit
    """
    pachet["data_sfarsit"]=new_date
def set_destinatie(pachet,new_dest):
    """Functia de setare destinatie pachet
    input:
        pachet(dictionar): pachet de calatorie
        new_dest(string): noua destinatie
    """
    pachet["destinatie"]=new_dest
def set_pret(pachet,new_pret):
    """Functia de setare pret pachet
    input:
        pachet(dictionar): pachet de calatorie
        new_pret(float): noul pret
    """
    pachet["pret"]=new_pret
def adaugare_pachet(pachet,oferte,undo_list):
    """
    Functia care adauga un pachet de calatorii de tip pachet in LISTA DE OFERTE
    input:
        pachet- pachet de calatorii
    output:
        None - daca s-a adaugat pachetul cu succes
    Raises:
        Ridica eroare ValueError "ID deja existent" daca mai exista un pachet cu acelasi id_pachet
    """
    lista_idu=lista_id(oferte)
    id_pachet=get_id_pachet(pachet)
    if id_pachet in lista_idu:
        raise ValueError("ID deja existent")
    else:
        add_to_undo(undo_list,oferte)
        oferte.append(pachet)
def add_to_undo(undo_list,oferte):
    """Functia de salvare liste de oferte in lista de undo

    input:
        undo_list (list): lista de undo
        oferte (list): lista de oferte
    """
    old_oferte=[]
    for i in oferte:
        id_pachet=get_id_pachet(i)
        data_inceput=get_data_inceput_pachet(i)
        data_sfarsit=get_data_sfarsit_pachet(i)
        destinatie=get_destinatie_pachet(i)
        pret=get_pret_pachet(i)
        copie=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
        old_oferte.append(copie)
    undo_list.append(old_oferte)
def modifica_pachet_data_i(oferte,id_pachet, new_data_i,undo_list):
    """Functia pentru modificare data de inceput pachet de calatorii din lista de oferte
    input:
        oferte(list): lista de oferte
        id_pachet(int): id-ul pachetului pe care il modifici
        new_data_i(date): noua data de inceput a pachetului
        undo_list(list): lista de undo
    output:
        oferte , daca se modifica cu succes
    Raises:
        Ridica eroare de tipul ValueError daca modificarile sunt ilegale(neconforme):
                -"Data de inceput invalida\n" daca data este eronata (zile inexistente pentru anumite luni, luni inexistente)
                
    """
    for i in oferte:
        if get_id_pachet(i)==id_pachet:
            data_sfarsit=get_data_sfarsit_pachet(i)
            if new_data_i>data_sfarsit:
                raise ValueError("Data de inceput invalida\n")
            else:
            #pt list
            #pachet[1]=new_data_i
            #pt dictionary
                add_to_undo(undo_list,oferte)
                set_data_inceput(i,new_data_i)
            break
        else: pass
    return oferte
def modifica_pachet_data_s(oferte,id_pachet, new_data_s,undo_list):
    """Functia pentru modificare data de sfarsit pachet de calatorii din lista de oferte
    input:
        oferte(list): lista de oferte
        id_pachet(int): id-ul pachetului pe care il modifici
        undo_list(list): lista de undo
        new_data_s(date): noua data de sfarsit a pachetului
    output:
        oferte , daca se modifica cu succes
    Raises:
        Ridica eroare de tipul ValueError daca modificarile sunt ilegale(neconforme):
                -"Data de sfarsit invalida\n" daca data este eronata (zile inexistente pentru anumite luni, luni inexistente), sau 
                                                in cazul in care data_sfarsit are loc inainte de data_inceput
    """
    for i in oferte:
        if get_id_pachet(i)==id_pachet:
            data_inceput=get_data_inceput_pachet(i)
            if new_data_s<data_inceput:
                raise ValueError("Data de sfarsit invalida\n")
            else:
                #pachet[2]=new_data_s
                #pt dictionary
                add_to_undo(undo_list,oferte)
                set_data_sfarsit(i,new_data_s)
                break
        else: pass
    return oferte
def modifica_pachet_dest(oferte,id_pachet, new_dest,undo_list):
    """Functia pentru modificare destinatie pachet de calatorii din lista de oferte
    input:
        oferte(list): lista de oferte
        id_pachet(int): id-ul pachetului pe care il modifici
        undo_list(list): lista de undo
        new_dest(str): locatia noua a pachetului de calatorii
    output:
        oferte , daca se modifica cu succes
    Raises:
        Ridica eroare de tipul ValueError daca modificarile sunt ilegale(neconforme):
                -"Destinatie invalida\n" daca destinatie este str null
    """
    if new_dest=='':
        raise ValueError("Destinatie invalida\n")
    else:
        #pachet[3]=new_dest
        #pt dictionary
        for i in oferte:
            if id_pachet==get_id_pachet(i):
                add_to_undo(undo_list,oferte)
                set_destinatie(i,new_dest)
                break
        return oferte
def modifica_pachet_pret(oferte,id_pachet, new_pret,undo_list):
    """Functia pentru modificare pret pachet de calatorii din lista de oferte
    input:
        new_pret(float): pretul nou
        oferte(list): lista de oferte
        id_pachet(int): id-ul pachetului pe care il modifici
        undo_list(list): lista de undo
    output:
        oferte , daca se modifica cu succes
    Raises:
        Ridica eroare de tipul ValueError daca modificarile sunt ilegale(neconforme):
                -"Pret invalid" daca pret este float<=0
    """
    if new_pret<0:
        raise ValueError("Pret invalid\n")
    else:
        #pachet[4]=new_pret
        #pt dictionary
        for i in oferte:
            if id_pachet==get_id_pachet(i):
                add_to_undo(undo_list,oferte)
                set_pret(i,new_pret)
                break
        return oferte

            
def creaza_valideaza_adauga(id_pachet,data_inceput, data_sfarsit, destinatie, pret,oferte,undo_list):
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    validare_pachet(pachet)
    adaugare_pachet(pachet,oferte,undo_list)
def sterge_pachete_dest(oferte,destinatie,undo_list):
    """Functia care sterge pachetele din lista de oferte cu o destinatie data din lista de oferte

    input:
        oferte (list): lista de oferte
        destinatie (string): destinatia pachetului de calatorii
        undo_list(list): lista de undo
    output:
        - , daca s-au eliminat ofertele cu destinatia data cu succes
    raises:
        Ridica eroare de tip ValueError cu mesajul:
            "Lista goala!\n", daca lista de oferte e goala
            "Nu exista oferte cu destinatia data!\n"
            daca nu exista nicio oferta cu destinatia destinatie
    """
    if len(oferte)==0:
        raise ValueError("Lista goala!\n")
    okay=False
    i=0
    while i<len(oferte):
        dest=get_destinatie_pachet(oferte[i])
        if dest==destinatie:
            add_to_undo(undo_list,oferte)
            oferte.remove(oferte[i])
            okay=True
        else: i+=1
    if okay is False:
        raise ValueError("Nu exista oferte cu destinatia data!\n")
#====================Functionalitate 2* cerinta 2=======================
def sterge_pachete_durata(oferte,duration,undo_list):
    """Functia care sterge toate pachetele din lista de oferte care au o durata mai mica de timp decat duration
    input:
        oferte(list): lista de oferte
        duration(int): durata de timp
        undo_list(list):lista de undo
    output:
        -,  daca s-a efectuat stergerea cu succes
    raises
        Ridica eroare de tip ValueError cu mesajul:
            "Lista goala!\n" daca lista de oferte este vida
            "Nu exista oferte cu durata mai mica decat cea specificata! \n"
    """
    if len(oferte)==0:
        raise ValueError("Lista goala!\n")
    okay=False
    i=0
    while i<len(oferte):
        durata=get_duration(oferte[i])
        if durata<duration:
            add_to_undo(undo_list,oferte)
            oferte.remove(oferte[i])
            okay=True
        else: i+=1
    if okay==False:
        raise ValueError("Nu exista oferte cu durata mai mica decat cea specificata! \n")
#====================Functionalitate 3* cerinta 2=======================
def sterge_pachete_pret(oferte,cost,undo_list):
    """Functia care sterge toate pachetele din lista de oferte care au un pret mai mare decat cost

    input:
        oferte (list): lista de oferte
        cost (float): pretul fata de care eliminam pachete
        undo_list(list): lista de undo
    output:
        - , daca s-au eliminat ofertele cu pretul mai mare decat cost
    raises:
        Ridica eroare tip ValueError cu mesajul:
            "Lista goala!\n"
            "Nu exista oferte cu pretul mai mare decat cel dat!\n"
    """
    if len(oferte)==0:
        raise ValueError("Lista goala!\n")
    okay=False
    i=0
    while i<len(oferte):
        pret=get_pret_pachet(oferte[i])
        if pret>=cost:
            add_to_undo(undo_list,oferte)
            oferte.remove(oferte[i])
            okay=True
        else: i+=1
    if okay is False:
        raise ValueError("Nu exista oferte cu pretul mai mare decat cel dat!\n")
        
#====================Functionalitate UNDO cerinta 6=======================
#doamne ajuta si da bine
def undo(oferte,undo_list):
    """Functia care reface ultima operatie efectuata(undo basically)

    input:
        oferte (list): lista de oferte
        undo_list (list): lista de undo
    output:
        new_offers, lista de oferte anterioara modificarii daca s-a efectuat undo cu succes( cu accent pe daca)
    raises:
        ValueError cu mesajul
            "Nu exista operatie de refacut!\n", daca lista de undo e goala
    """
    if len(undo_list)>0:
        oferte[:]=undo_list[-1]
        undo_list.pop()
        return oferte
    else: raise ValueError("Nu exista operatie de refacut!\n")
    
