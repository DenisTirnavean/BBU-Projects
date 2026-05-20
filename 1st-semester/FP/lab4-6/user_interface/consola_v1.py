from user_interface.meniuri import *
from tests.teste import *
import os
from time import sleep
def ui_adauga_pachet_oferta(oferte,undo_list):
    """Functia care citeste un pachet de calatorii cu id_pachet int, data_i data calendaristica, data_s data calendaristica, destinatie string si pret float si adauga in lista de oferte

    input:
        oferte (list): lista de oferte
    output:
        -, daca s-a efectuat adaugarea cu succes
    raises:
        ridica eroare tip ValueError cu mesajul:
            "Id numeric invalid!\n", daca id-ul nu se poate parsa in int
            "Data de inceput invalida!\n", daca data_i nu se poate parsa in tip de date datetime
            "Data de sfarsit invalida!\n", daca data_s nu se poate parsa in tip de date datetime
            "Destinatie invalida!\n", daca destinatie nu se poate parsa in string
            "Pret numeric invalid!\n"
        ridica eroare tip ValueError cu mesajul:
                -"ID invalid\n" daca id_pachet <=0 
                -"Data de inceput invalida\n" daca data este eronata (zile inexistente pentru anumite luni, luni inexistente)
                -"Data de sfarsit invalida\n" daca data este eronata (zile inexistente pentru anumite luni, luni inexistente), sau 
                                                in cazul in care data_sfarsit are loc inainte de data_inceput
                -"Destinatie invalida\n" daca destinatie este str null
                -"Pret invalid" daca pret este float<=0
            "ID deja existent", daca deja exista pachet cu id-ul citit in lista de oferte 
    """
    lista=lista_id(oferte)

    try:
        id_pachet = int(input("Id pachet: "))
        if id_pachet in lista: 
            print("ID deja existent,boss!!!")
            return
    except ValueError:
        print("Id numeric invalid!\n")
        return
    try:
        print("Data de inceput: ")
        zi=int(input("ZI: "))
        luna=int(input("LUNA: "))
        an=int(input("ANUL: "))
        data_i=datetime.date(an,luna,zi)
    except ValueError:
        print("Data de inceput invalida!\n")
        return
    try:
        print("Data de sfarsit: ")
        zi=int(input("ZI: "))
        luna=int(input("LUNA: "))
        an=int(input("ANUL: "))
        data_s=datetime.date(an,luna,zi)
    except ValueError:
        print("Data de sfarsit invalida!\n")
        return
    try:
        destinatie = str(input("Destinatie: "))
    except ValueError:
        print("Destinatie invalida!")
        return
    try:
        pret=float(input("Pretul: "))
    except ValueError:
        print("Pret numeric invalid!\n")
        return
    try:
        creaza_valideaza_adauga(id_pachet,data_i,data_s,destinatie,pret,oferte,undo_list)
        print("Pachet adaugat cu succes")
    except ValueError as msg:
        print(str(msg))
    

def show_oferte(oferte,undo_list):
    """Functie care tipareste continutul listei de oferte
    input:
        oferte(list): lista de oferte
    output:
        -
    """
    if len(oferte)!=0:
        print("Lista de oferte este: ")
        for i in oferte:
            tipareste(i)
    else:
        print("Lista este goala!\n")
def ui_modifica(oferte,undo_list):
    """Functia care modifica data_inceput, data_sfarsit, destinatia sau pretul unui pachet cu un id id_pachet din lista de oferte

    input:
        oferte (list): lista de oferte
    output:
        -
    raises:
        ridica eroare tip ValueError cu mesajul:
            -"Data de inceput invalida\n" daca data este eronata (zile inexistente pentru anumite luni, luni inexistente)"
            -"Data de sfarsit invalida\n" daca data este eronata (zile inexistente pentru anumite luni, luni inexistente), sau 
                                                in cazul in care data_sfarsit are loc inainte de data_inceput
            -"Destinatie invalida\n" daca destinatie este str vid
            -"Pret invalid" daca pret este float<=0
    """
    for i in oferte:
        tipareste(i)
    lista_iduri=lista_id(oferte)
    print("Id-uri disponibile: ",lista_iduri)
    try:
        id_pachet=int(input("Ce pachet doresti sa modifici? Scrie id-ul pachetului dorit: "))
    except ValueError:
        print("Id invalid!\n")
        return
    if id_pachet not in lista_iduri:
        print("Nu exista pachet cu id-ul dat!")
        return
    else:
        meniu={
            "1":meniu_modifica_pachet_data_i,
            "2":meniu_modifica_pachet_data_s,
            "3":meniu_modifica_pachet_dest,
            "4":meniu_modifica_pachet_pret
        }
        meniu_modificari()
        while True:
            comanda=input("Numarul comenzii pe  care doresti sa o executi? ")
            if comanda not in meniu:
                print("Nu exista comanda ceruta!")
            else: break
        add_to_undo(undo_list,oferte)
        meniu[comanda](oferte,id_pachet,undo_list)
    
def ui_stergere(oferte,undo_list):
    """Functia de stergere pachete din lista de oferte

    input:
        oferte (list): lista de oferte
    output:
        -, daca s-a efectuat cu succes
    raises
        ridica erori tip ValueError cu mesaj:
            "Nu exista pachetul pe care incerci sa-l stergi!\n", daca id_ul citit nu corespunde niciunui pachet de calatorii din lista de oferte
    """
    meniu_stergere()
    meniu={
        "1":meniu_stergere_dest,
        "2":meniu_stergere_perio,
        "3":meniu_stergere_pret
    }
    while True:
        comanda=input("Numarul comenzii pe care doresti sa o executi? ")
        if comanda not in meniu:
                print("Nu exista comanda ceruta!")
        else: break
    add_to_undo(undo_list,oferte)
    meniu[comanda](oferte,undo_list)
def ui_rapoarte(oferte,undo_list):
    """Functia pentru tiparire rapoarte pentru lista de oferte

    input:
        oferte (list): lista  de oferte
    output:
        -
    """
    meniu_rapoarte()
    meniu={
        "1":meniu_rap_nr,
        "2":meniu_rap_per,
        "3":meniu_rap_pret
    }
    while True:
        comanda=input("Numarul comenzii pe care doresti sa o executi: ")
        if comanda not in meniu:
            print("Nu exista comanda ceruta!")
        else: break
    meniu[comanda](oferte)
def ui_cautare(oferte,undo_list):
    """Functia pentru cautare in lista de oferte
    input:
        oferte(list): lista de oferte
    output:
        -
    """
    meniu_cautare()
    meniu={
        "1":meniu_cautare_sejur,
        "2":meniu_cautare_dest_pret,
        "3":meniu_cautare_data_s
    }
    while True:
        comanda=input("Numarul comenzii pe care doresti sa o executi: ")
        if comanda not in meniu:
            print("Nu exista comanda ceruta!")
        else: break
    meniu[comanda](oferte)
def ui_filtru(oferte,undo_list):
    """Functia de filtrare a listei de oferte

    input:
        oferte (list): lista de oferte
    output:
        -
    """
    meniu_filtru()
    meniu={
        "1":meniu_filtru_1,
        "2":meniu_filtru_2
    }
    while True:
        comanda=input("Numarul comenzii pe care doresti sa o executi: ")
        if comanda not in meniu:
            print("Nu exista comanda ceruta!")
        else: break
    meniu[comanda](oferte)
def ui_undo(oferte,undo_list):
    """Functia de refacere a ultimei operatii
    input:
        oferte(list): lista de oferte
        undo_list(list): lista de undo
    output:
        -, daca s-a efectuat undo cu succes
    raises:
        ridica eroare tip ValueError cu mesajul:
            "Nu exista operatie de refacut\n" , daca lista de undo este goala
    """
    try:
        oferte=undo(oferte,undo_list)
        print("Undo efectuat cu succes")
    except ValueError as msg:
        print(str(msg))
def run():
    
    oferte=[]
    undo_list=[]
    while True:
        meniu_bine_ai_venit()
        comenzi={
            "1.1":ui_adauga_pachet_oferta,  "1.2":show_oferte,  "1.3":ui_modifica, #bun
            "2":ui_stergere, #bun
            "3":ui_cautare,  #bun
            "4":ui_rapoarte, #bun
            "5":ui_filtru, #bun
            "6":ui_undo, #doamne ai mila de sufletul unui pacatos
         }
        comanda=str(input("Comanda: "))
        if comanda=="x":
             break
        elif comanda in comenzi:
            comenzi[comanda](oferte,undo_list)
        else:
            print("Comanda invalida!")
        continua=input("Apasa orice pentru a continua")
        os.system('cls')
     

