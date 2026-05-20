from user_interface.consola_v1 import show_oferte
from services.servicii import *
from user_interface.meniuri import *


def method_adaug(oferte,undo_list,list_arg):
    """Functia de adaugare in lista de oferte a unui pachet extras din list_arg

    input:
        oferte (list): lista de oferte
        undo_list (list): lista de undo
        list_arg (list): lista de argumente pachete(pachet.zip)
    output:
        - daca s-a efectuat cu succes
    """
    if len(list_arg)<5:
        print("Nu ai destule specificatii pentru un pachet de calatorii valid!!!")
        return
    try:
        id_pachet=int(list_arg[0])
    except ValueError:
        print("Id numeric invalid!")
        return
    data_inceput=list_arg[1].split("/")
    try:
        an=int(data_inceput[0])
        luna=int(data_inceput[1])
        zi=int(data_inceput[2])
        data_i=datetime.date(an,luna,zi)
    except ValueError:
        print("Data de inceput invalida!!!")
        return
    data_sfarsit=list_arg[2].split("/")
    try:
        an=int(data_sfarsit[0])
        luna=int(data_sfarsit[1])
        zi=int(data_sfarsit[2])
        data_s=datetime.date(an,luna,zi)
    except ValueError:
        print("Data de sfarsit invalida!!!")
        return
    destinatie=str(list_arg[3]).lower()
    try:
        pret=float(list_arg[4])
    except ValueError:
        print("Pret numeric invalid!!!")
        return
    try:
        creaza_valideaza_adauga(id_pachet,data_i,data_s,destinatie,pret,oferte,undo_list)
        print("Oferta adaugata cu succes!")
    except ValueError as msg:
        print(str(msg))
        return
def method_stergere(oferte,undo_list,list_arg):
    """Functia de stergere pachet din lista de oferte pe baza unui id_pachet

    input:
        oferte (list): lista de oferte
        undo_list (list): lista de undo
        list_arg (list): lista argumente pachete(destinatie)
    """
    if len(list_arg)<1:
        print("Nu ai destule specificatii pentru stergere!!!")
        return
    dest=str(list_arg[0]).lower()
    try:
        sterge_pachete_dest(oferte,dest,undo_list)
        print("Oferte sterse cu succes")
    except ValueError as msg:
        print(str(msg))
        
def method_cautare(oferte,list_arg):
    """Functia de cautare in lista de oferte a pachetelor cu destinatie data

    input:
        oferte (list): lista de oferte
        list_arg (list): lista de argumente pachete(destinatie+pret)
    """
    if len(list_arg)<2:
        print("Nu ai destule specificatii pentru cautare!!!")
        return
    dest=str(list_arg[0]).lower()
    try:
        pret=float(list_arg[1])
    except ValueError:
        print("Pret numeric invalid!!!")
        return
    new_offers=pachete_ieftine_destinatie_data(oferte,dest,pret)
    show_oferte(new_offers,undo_list=None)
    
def method_raport(oferte,list_arg):
    """Functia de rapoart numar de oferte pentru o destinatie data
    printeaza numarul ofertelor cu o anumita destinatie

    input:
        oferte (list): lista de oferte
        list_arg (list): lista argumente(destinatie)
    """
    if len(list_arg)<1:
        print("Nu ai destule specificatii pentru raport!!!")
        return
    dest=str(list_arg[0]).lower()
    solutie=raport_destinatie_data(oferte,dest)
    if solutie==0:
        print("Nu avem asa ceva!")
    else: print("Pentru locatia "+str(dest)+" avem exact "+str(solutie)+" oferte")
def method_filtrare(oferte,list_arg):
    """Functia de filtrare oferte in functie de luna
    Functia omite din lista de oferte ofertele care presupun un sejur intr-o anumita luna

    input:
        oferte (list): lista de oferte
        list_arg (list): lista de argumente(luna)
    """
    if len(list_arg)<1:
        print("Nu ai destule specificatii pentru filtrare!!!")
        return
    try:
        luna=int(list_arg[0])
    except ValueError:
        print("Luna invalida!!!")
        return
    if luna<1 and luna>12:
        print("Luna invalida!!!")
        return
    solutie=filtru_2(oferte,luna)
    show_oferte(solutie,undo_list=None)
    
def method_undo(oferte,undo_list):
    """FUNctia care face undo

    input:
        oferte (list): lista de oferte
        undo_list (list): lista de undo
    """
    try:
        oferte=undo(oferte,undo_list)
        print("UNDO realizat cu succes")
    except ValueError as msg:
        print(str(msg))
def run_v2():
    undo_list=[]
    oferte=[]
    meniu_bine_ai_venit_new()
    command={"adauga":method_adaug, #merge
             "afisare":show_oferte, #merge
             "stergere":method_stergere, #merge
             "cautare":method_cautare, #merge
             "raport":method_raport, #merge
             "filtrare":method_filtrare, #merge
             "undo":method_undo #se vrea sa mearga
             }
    while True:
        cmd=input(">>>")
        comanda_extinsa=cmd.split(" ")
        comanda=comanda_extinsa[0]
        if comanda in ["iesire", "out", "exit", "iesi_afara", "BAU","mersi_frumos"]:
            break
        list_arg=comanda_extinsa[1:]
        if comanda in command:
            if comanda in ["raport","cautare","filtrare"]:
                command[comanda](oferte,list_arg)
            elif comanda in ["afisare", "undo"]:
                command[comanda](oferte,undo_list)
            else: command[comanda](oferte,undo_list,list_arg)
        else: print("Comanda invalida!!!")