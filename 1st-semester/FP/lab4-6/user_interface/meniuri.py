from services.servicii import *
def meniu_bine_ai_venit():
    print("Bine ai venit in aplicatia de management agentie de turism!")
    print("Operatii pe care le poti efectua: ")
    print("1.1 *Adauga pachet de calatorie ")
    print("1.2 *Afisare lista de oferte ")
    print("1.3 *Modifica pachet de calatorie ")
    print("2    *Stergere anumite pachete de calatorie din lista de oferte")
    print("3    *Cautare in lista de oferte")
    print("4    *Rapoarte in legatura cu lista de oferte")
    print("5    *Filtrare lista de oferte")
    print("6    *Undo- Reface ultima operatie efectuata")
    print("x    *Exit")
def meniu_bine_ai_venit_new():
    print("Bine ai venit in aplicatia de management agentie de turism!")
    print("Operatii pe care le poti efectua: ")
    print("adauga [id_pachet] [data_inceput] [data_sfarsit] [destinatie] [pret]")
    print("afisare")
    print("stergere [destinatie]")
    print("cautare [destinatie] [pret maxim]")
    print("raport [destinatie]")
    print("filtrare [luna]")
    print("undo")
    print("exit")
    print("Datele calendaristice se vor scrie sub forma AAAA/LL/ZI")

    
    
def meniu_modificari():
    """Functie care tipareste meniul pentru modificari
    """
    print("Optiuni de modificare: ")
    print("1.Modifica data de inceput")
    print("2.Modifica data de sfarsit")
    print("3.Modifica destinatia")
    print("4.Modifica pretul")

def meniu_stergere():
    """Functie care tipareste meniul pentru stergeri
    """
    print("Optiuni pentru stergere: ")
    print("1.Sterge toate pachetele disponibile pentru o anumita destinatie")
    print("2.Sterge toate pachetele care au o durata mai scurta de timp decat un anumit nr de zile")
    print("3.Sterge toate pachetele care au pretul mai mare decat o anumita suma")

def meniu_stergere_dest(oferte,undo_list):
    """Functia pentru stergere pachete cu o anumita destinatie

    input:
        oferte (list): lista de oferte
    output:
        -
    raises:
        Ridica eroare tip ValueError cu mesajul:
            "Lista goala!\n", daca lista de oferte e goala
            "Nu exista oferte cu destinatia data!\n", daca nu exista nicio oferta cu destinatia destinatie
    """
    destinatie=input("Destinatia pe care doresti sa o elimini din lista de oferte: ")
    try:
        sterge_pachete_dest(oferte,destinatie,undo_list)
        print("Pachete eliminate cu succes!")
    except ValueError as msg:
        print(msg)
def meniu_stergere_perio(oferte,undo_list):
    """Functia pentru stergere pachete cu o perioada mai mica decat una data

    input:
        oferte (list): lista de oferte
    output:
        -
    raises:
        Ridica eroare tip ValueError cu mesajul:
            "Lista goala!\n" daca lista de oferte este vida
            "Nu exista oferte cu durata mai mica decat cea specificata! \n"
    """
    try:
        durata=int(input("Sterge pachetele cu o durata(in zile) mai scurta de: "))
    except ValueError:
        print("Durata invalida!")
        return
    try:
        sterge_pachete_durata(oferte,durata,undo_list)
        print("Pachete eliminate cu succes")
    except ValueError as msg:
        print(msg)
def meniu_stergere_pret(oferte,undo_list):
    """Functia de stergere pachete de calatorii cu un pret mai mare decat unul dat de user

    input:
        oferte (list): lista de oferte
    output:
        -  
    raises:
        Ridica eroare tip ValueError cu mesajul:
            "Lista goala!\n"
            "Nu exista oferte cu pretul mai mare decat cel dat!\n"
            
    """
    try:
        pret=float(input("Sterge pachetele cu pretul mai mare decat: "))
    except ValueError:
        print("Pret invalid!")
        return
    try:
        sterge_pachete_pret(oferte,pret,undo_list)
        print("Pachete eliminate cu succes!")
    except ValueError as msg:
        print(msg)
def meniu_filtru():
    """Functie care tipareste meniul pentru filtru
    """
    print("Optiuni pentru filtrare: ")
    print("1.Afiseaza lista fara ofertele care au un pret mai mare decat o anumita suma si destinatia diferita decat cea ce ceri")
    print("2.Afiseaza lista fara ofertele care presupun un sejur intr-o anumita luna")
def meniu_modifica_pachet_data_i(oferte,id_pachet,undo_list):
    """Functie pentru meniul de modificari data_inceput
    """
    print("Noua data de inceput este: ",end="")
    try:
        zi=int(input("ZI: "))
        luna=int(input("LUNA: "))
        an=int(input("ANUL: "))
    except ValueError:
        print("Data invalida!")
        return
    try:
        new_data_i=datetime.date(an,luna,zi)
        oferte=modifica_pachet_data_i(oferte,id_pachet,new_data_i,undo_list)
        print("Data de sfarsit modificata cu succes")
    except ValueError:
        print("Data invalida!")
        return
def meniu_modifica_pachet_data_s(oferte,id_pachet,undo_list):
    """Functie pentru meniul de modificari data_sfarsit
    """
    print("Noua data de sfarsit este: ")
    try:
        zi=int(input("ZI: "))
        luna=int(input("LUNA: "))
        an=int(input("ANUL: "))
    except ValueError:
        print("Data invalida!")
        return
    try:
        new_data_s=datetime.date(an,luna,zi)
        oferte=modifica_pachet_data_s(oferte,id_pachet,new_data_s,undo_list)
        print("Data de sfarsit modificata cu succes")
    except ValueError:
        print("Data invalida!")
        return
    
def meniu_modifica_pachet_dest(oferte,id_pachet,undo_list):
    """Functie pentru meniul de modificari destinatie
    """
    new_dest=input("Noua destinatie este: ")
    try:
        oferte=modifica_pachet_dest(oferte,id_pachet,new_dest,undo_list)
        print("Destinatie modificata cu succes!")
    except ValueError as msg:
        print(msg)
def meniu_modifica_pachet_pret(oferte,id_pachet,undo_list):
    """Functie pentru meniul de modificari pret
    """
    try:
        new_pret=float(input("Noul pret: "))
        oferte=modifica_pachet_pret(oferte,id_pachet,new_pret,undo_list)
        print("Pret modificat cu succes!")
    except ValueError:
        print("Pret numeric invalid!")
def meniu_filtru_1(oferte):
    """Functia pentru filtrarea tip_1 a listei de oferte 

    input:
        oferte (list): lista de oferte
    """
    try:
        pret=float(input("Pretul maxim pe care doresti sa-l vezi: "))
    except ValueError:
        print("Pret invalid!")
        return
    destinatie=input("Destinitia pe care doresti sa o vezi: ")
    solutie=filtru_1(oferte,pret,destinatie)
    if len(solutie):
        for i in solutie:
            tipareste(i)
    else:
        print("Lista goala!")
    
def meniu_filtru_2(oferte):
    """Functia pentru filtrarea tip_2 a listei de oferte 


    input:
        oferte (list): lista de oferte
    """
    try:
        luna=int(input("Luna pe care doresti sa o eviti(1-12): "))
    except ValueError:
        print("Luna invalida!")
    if luna<1 or luna>12:
        print("Luna invalida!")
        return
    solutie=filtru_2(oferte,luna)
    if len(solutie):
        for i in solutie:
            tipareste(i)
    else:
        print("Lista goala!")
def meniu_rapoarte():
    """Functie care tipareste meniul pentru rapoarte
    """
    print("Optiuni pentru rapoarte: ")
    print("1.Tiparirea numarului de oferte pentru o anumita destinatie")
    print("2.Tiparirea tuturor pachetelor disponibile intr-o anumita perioada")
    print("3.Tiparirea mediei de pret pentru o anumita destinatie")
def meniu_rap_nr(oferte):
    """Functie pentru tiparirirea numarului de oferte pentru o anumita destinatie

    input:
        oferte (list): lista de oferte
    """
    destinatie=input("Destinatia pentru care doresti raportul: ")
    raport=raport_destinatie_data(oferte,destinatie)
    if raport!=0:
        print("Pentru destinatia ceruta exista ["+str(raport)+"] pachete de calatorii")
    else:
        print("Nu exista nicio oferta pentru destinatia data!")
def meniu_rap_per(oferte):
    """Functia care tipareste toate pachetele disponibile intr-o anumita perioada

    input:
        oferte (list): lista de oferte
    """
    while True:
        try:
            print("Data de inceput a perioadei dorite: ")
            zi=int(input("ZI: "))
            luna=int(input("LUNA: "))
            an=int(input("ANUL: "))
            data_i=datetime.date(an,luna,zi)
            print("Data de sfarsit a perioadei dorite: ")
            zi=int(input("ZI: "))
            luna=int(input("LUNA: "))
            an=int(input("ANUL: "))
            data_s=datetime.date(an,luna,zi)
            break
        except ValueError:
            print("Data invalida!!!!")
    raport=raport_perioada_data(oferte,data_i,data_s)
    if raport!=0:
        for i in raport:
            tipareste(i)   
    else: print("Nu exista oferte de calatorii in intervalul de timp specificat")
def meniu_rap_pret(oferte):
    """Functia care tipareste media de pret pentru o anumita destinatie
    input:
        oferte(list): lista de oferte
    """
    destinatia=input("Destinatia pentru care doresti sa afli media de pret a ofertelor: ")
    raport=raport_medie_destinatie(oferte,destinatia)
    if raport!=-1:
        print("Media de pret pentru "+str(destinatia)+" este de "+str(raport)+" lei")
    else:
        print("Destinatia ceruta nu exista iin lista de oferte!!!")
def meniu_cautare():
    """Functia de tiparire a meniului de cautare
    """
    print("Optiuni pentru cautare: ")
    print("1.Tiparire pachete de calatorie care presupun un sejur intr-un interval de timp dat")
    print("2.Tiparirea pachetelor de calatorie cu o destinatie data si un pret mai mic decat o suma data")
    print("3.Tiparirea pachetelor de calatorie cu o anumita data de sfarsit")
def meniu_cautare_sejur(oferte):
    """Functia care tipareste pachetele de calatorie care presupun un sejur intr-un interval de timp

    input:
        oferte (list): lista de oferte
    """
    while True:
        try:
            print("Data de inceput a sejurului: ")
            zi=int(input("ZI: "))
            luna=int(input("LUNA: "))
            an=int(input("ANUL: "))
            data_i=datetime.date(an,luna,zi)
            print("Data de sfarsit a sejurului: ")
            zi=int(input("ZI: "))
            luna=int(input("LUNA: "))
            an=int(input("ANUL: "))
            data_s=datetime.date(an,luna,zi)
            break
        except ValueError:
            print("Data invalida!!!")
    if data_s<data_i:
        print("Interval de timp invalid!!!")
        return
    solutie=sejur_interval_dat(oferte,data_i,data_s)
    if len(solutie):
        print("Ofertele cu sejur in perioada data sunt: ")
        for i in solutie:
            tipareste(i)
    else:
        print("Nu exista oferte cu sejur in perioada data!")
def meniu_cautare_dest_pret(oferte):
    """Functia care tipareste pachetele de calatorie cu o destinatie data si un pret mai mic decat unul cerut
    input:
        oferte (list): lista de oferte
    """
    destinatie=input("Destinatia cautata: ")
    while True:
        try:
            pret=float(input("Pretul maxim dorit: "))
            break
        except ValueError:
            print("Pret numeric invalid!!!")
            return
    solutie=pachete_ieftine_destinatie_data(oferte,destinatie,pret)
    if len(solutie):
        print("Ofertele cerute sunt: ")
        for i in solutie:
            tipareste(i)
    else:
        print("Nu exista oferte care sa respecte criteriile!")
def meniu_cautare_data_s(oferte):
    """Functia care tipareste pachetele de calatorie cu o data de sfarsit ceruta

    input:
        oferte (list): lista de oferte
    """
    print("Data la care se termina pachetul de calatorii: ")
    while True:
        try:
            zi=int(input("ZI: "))
            luna=int(input("LUNA: "))
            an=int(input("ANUL: "))
            data_s=datetime.date(an,luna,zi)
            break
        except ValueError:
            print("Data invalida!!!")
    solutie=pachete_care_se_termina(oferte,data_s)
    if len(solutie):
        print("Ofertele cerute sunt: ")
        for i in solutie:
            tipareste(i)
    else:
        print("Nu exista oferte care sa respecte criteriile!")