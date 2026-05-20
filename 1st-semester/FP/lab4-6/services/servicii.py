from repository.repo_pachete import *
#==========================Functionalitatea 1* cerinta 3========================
def sejur_interval_dat(oferte,data_inceput, data_final):
    """
    Functia care returneaza o lista cu toate ofertele care presupun un sejur intr-un anumit interval dat
    input:
        ofete: lista de oferte
        data_inceput: data calendaristica , inceputul intervalului de timp
        data_sfarsit: data calendaristica , sfarsitul intervalului de timp
    output:
        solutie(list): lista cu pachetele de calatorii care respecta cerinta
    """
    solutie=[]
    for i in oferte:
        data_i_pachet=get_data_inceput_pachet(i)
        data_s_pachet=get_data_sfarsit_pachet(i)
        if data_inceput>=data_i_pachet:
            if data_final<=data_s_pachet:
                solutie.append(i)
    
    return solutie
#=============================Functionalitate 2* cerinta 3================================
def pachete_ieftine_destinatie_data(oferte,destinatie,pret):
    """
    Functia care returneaza pachetele cu o destinatie ceruta care au pretul mai mic decat o suma data
    input:
        oferte (list): lista ofertelor
        destinatie (str): destinatia ceruta de utilizator
        pret (float): pretul cerut de utilizator
    output:
        solutie(list): lista cu pachetele de calatorii care respecta cerinta
    """
    solutie=[]
    marja_eroare=0.00001
    for i in oferte:
        destination=get_destinatie_pachet(i)
        if destination==destinatie:
            prise=get_pret_pachet(i)
            if pret-prise>=marja_eroare:
                solutie.append(i)
    return solutie


#=======================Functionalite 3* cerinta 3=========================
def pachete_care_se_termina(oferte,data_final):
    """Functia care returneaza o lista cu ofertele care se termina intr-o data primita de la utilizator

    input:
        oferte (list): lista de pachete de calatorii
        data_final (data calendaristica): data de sfarsit
    output:
        solutie(list): lista cu pachetele de calatorii care respecta cerinta data
    """
    solutie=[]
    for i in oferte:
        end_date=get_data_sfarsit_pachet(i)
        if end_date==data_final:
            solutie.append(i)
    return solutie



#Iteratie 2

#=======================FUNctionalitate 1* cerinta 5=====================
def filtru_1(oferte,pret,destinatie):
    """Functia de filtru care elimina ofertele care au o anumita destinatie si un pret mai mare decat unul dat

    input:
        oferte (list): lista de oferte
        pret (float): pretul de referinta
        destinatie (string): destinatia pe care vrem s-o omitem
    output:
        solutie(list): lista fara ofertele mentionate
    """
    solutie=[]
    for i in oferte:
        dest=get_destinatie_pachet(i)
        prise=get_pret_pachet(i)
        if dest==destinatie and prise<pret:
            solutie.append(i)
    return solutie


#=======================FUNctionalitate 2* cerinta 5=====================
def filtru_2(oferte,luna):
    """Functia de filtru care elimina pachetele in care sejurul presupune zile dintr-o anumita luna

    input:
        oferte (list): lista de oferte
        luna (int): luna pe care o evitam ( integer intre [1-12] )
    output:
        solutie(list) : lista fara pachetele de calatorie mentionate
    """
    solutie=[]
    for i in oferte:
        data_inceput=get_data_inceput_pachet(i)
        data_sfarsit=get_data_sfarsit_pachet(i)
        if data_inceput.month<=luna and luna<=data_sfarsit.month:
            pass
        elif data_sfarsit.year-data_inceput.year>=2:
            pass
        else:
            solutie.append(i)
    return solutie

#=======================FUNctionalitate 1* cerinta 4=====================
def raport_destinatie_data(oferte,destinatie):
    """Functia care returneaza numarul de oferte pentru o destinatie data

    input:
        oferte (list): lista de oferte
        destinatie (str): destinatia pentru care vrem sa aflam numarul de oferte
    output:
        solutie(int): numarul de oferte cu destinatia data
    """
    solutie=0
    for i in oferte:
        location=get_destinatie_pachet(i)
        if location==destinatie:
            solutie+=1
    return solutie

#=======================FUNctionalitate 2* cerinta 4=====================
def raport_perioada_data(oferte,data_inceput,data_sfarsit):
    """Functia care returneaza o lista cu toate ofertele disponibile pentru o anumita perioada de timp

    input:
        oferte (list): lista de oferte
        data_inceput(date): data de la care incepe perioada
        data_sfarsit(date): data la care se sfarseste perioada
    output:
        solutie(list): lista de oferte care se incadreaza in perioada specificata
    """
    solutie=[]
    for i in oferte:
        data_in=get_data_inceput_pachet(i)
        data_sf=get_data_sfarsit_pachet(i)
        if data_inceput<=data_in and data_sf<=data_sfarsit:
            solutie.append(i)
    return solutie
#=======================FUNctionalitate 3* cerinta 4=====================
def raport_medie_destinatie(oferte,destinatie):
    """Functia care returneaza media de pret pentru o destinatie data

    input:
        oferte (list): lista de oferte
        destinatie(str): destinatia la care vrem sa-i aflam pretul mediu
    output:
        solutie(int): media preturilor pentru destinatia data
    """
    cate=0
    suma=0
    for i in oferte:
        dest=get_destinatie_pachet(i)
        if dest==destinatie:
            cate+=1
            prise=get_pret_pachet(i)
            suma+=prise
    if cate!=0:
        solutie=suma/cate
        return solutie
    else: return -1