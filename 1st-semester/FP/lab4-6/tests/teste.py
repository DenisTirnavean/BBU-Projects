from services.servicii import *
from validator.validator import *
#iteratia 1
def test_creare_pachet():
    """
    Functia de test pentru creare_pachet()
    """
    id_pachet=1
    data_inceput=datetime.date(2024,7,27)
    data_sfarsit=datetime.date(2025,1,10)
    destinatie='Tokyo'
    pret=999.0
    #pt list si pentru dictionary
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    assert(get_id_pachet(pachet)==id_pachet)
    assert(get_data_inceput_pachet(pachet)==data_inceput)
    assert(get_data_sfarsit_pachet(pachet)==data_sfarsit)
    assert(get_destinatie_pachet(pachet)==destinatie)
    assert(get_pret_pachet(pachet)==pret)
    

def test_validare_pachet():
    """
    Functia de test pentru validare_pachet()
    """
    id_pachet=1
    data_inceput=datetime.date(2024,7,27)
    data_sfarsit=datetime.date(2025,1,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    validare_pachet(pachet)
    id_eronat=-68
    data_i_eronata=datetime.date(2024,7,27)
    data_s_eronata=datetime.date(2023,7,27)
    destinatie_eronata=""
    pret_eronat=-13.0
    pachet_invalid=creare_pachet(id_eronat,data_i_eronata,data_s_eronata,destinatie_eronata,pret_eronat)
    try :
        validare_pachet(pachet_invalid)
        assert(False)
    except ValueError as ve:
        assert(str(ve) in ("ID invalid\nData de inceput invalida\nData de sfarsit invalida\nDestinatie invalida\nPret invalid\n"))


def test_adaugare_pachet():
    """
    Functia de test pentru adaugare_pachet(pachet,oferte)
    """
    undo=[]
    id_pachet=1
    data_inceput=datetime.date(2024,7,27)
    data_sfarsit=datetime.date(2025,1,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    oferte=[]
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=1
    data_inceput=datetime.date(2025,7,27)
    data_sfarsit=datetime.date(2026,1,10)
    destinatie='Chinteni'
    pret=10000.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    try:
        adaugare_pachet(pachet,oferte,undo)
        assert(False)
    except ValueError as msg:
        assert(str(msg)=="ID deja existent")
        
        
def test_sejur_interval_dat():
    """
    Functia de test pentru sejur_interval_dat
    """
    oferte=[]
    undo=[]
    id_pachet=1
    data_inceput=datetime.date(2024,7,27)
    data_sfarsit=datetime.date(2025,1,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=2
    data_inceput=datetime.date(2022,4,27)
    data_sfarsit=datetime.date(2022,7,30)
    destinatie='Torrino'
    pret=9999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=3
    data_inceput=datetime.date(2028,7,27)
    data_sfarsit=datetime.date(2029,1,10)
    destinatie='Columbia'
    pret=10
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    data_inceput=datetime.date(2022,6,30)
    data_sfarsit=datetime.date(2022,7,30)
    solutie=sejur_interval_dat(oferte,data_inceput,data_sfarsit)
    #pt list
    #assert(solutie==[[2, datetime.date(2022, 7, 27), datetime.date(2022, 9, 10), 'Torrino', 9999]])
    #pt dictionary
    assert(solutie==[{"id_pachet":2,"data_inceput":datetime.date(2022, 4, 27),"data_sfarsit":datetime.date(2022, 7, 30),"destinatie":'Torrino',"pret": 9999.0}])

def test_get_duration():
    """Functie de test pentru get_duration()
    """
    id_pachet=1
    data_inceput=datetime.date(2024,7,27)
    data_sfarsit=datetime.date(2025,1,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    durata=get_duration(pachet)
    assert durata==167

def test_pachete_ieftine_destinatie_data():
    """
    Functia de test pentru pachete_ieftine_destinatie_data()
    """
    oferte=[]
    undo=[]
    id_pachet=1
    data_inceput=datetime.date(2024,7,27)
    data_sfarsit=datetime.date(2025,1,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=2
    data_inceput=datetime.date(2022,7,27)
    data_sfarsit=datetime.date(2022,9,10)
    destinatie='Torrino'
    pret=9999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=3
    data_inceput=datetime.date(2028,7,27)
    data_sfarsit=datetime.date(2029,1,10)
    destinatie='Columbia'
    pret=10.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    destinatie="Torrino"
    pret=10000.0
    solutie=pachete_ieftine_destinatie_data(oferte,destinatie,pret)
    #pt list
    #assert(solutie==[[2, datetime.date(2022, 7, 27), datetime.date(2022, 9, 10), 'Torrino', 9999.0]])
    #pt dictionary
    assert(solutie==[{"id_pachet":2,"data_inceput":datetime.date(2022, 7, 27),"data_sfarsit":datetime.date(2022, 9, 10),"destinatie":'Torrino',"pret": 9999.0}])
def test_pachete_care_se_termina():
    """Functia de test pentru pachete_care_se_termina()
    """
    oferte=[]
    undo=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2022,9,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=2
    data_inceput=datetime.date(2022,7,27)
    data_sfarsit=datetime.date(2022,9,10)
    destinatie='Torrino'
    pret=9999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=3
    data_inceput=datetime.date(2028,7,27)
    data_sfarsit=datetime.date(2029,1,10)
    destinatie='Columbia'
    pret=10.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    data_sfarsit=datetime.date(2020,1,1)
    solutie=pachete_care_se_termina(oferte,data_sfarsit)
    assert(solutie==[])
    data_sfarsit=datetime.date(2029,1,10)
    solutie=pachete_care_se_termina(oferte,data_sfarsit)
    #pt list
    #assert(solutie==[[3,datetime.date(2028,7,27),datetime.date(2029,1,10),'Columbia',10.0]])
    #pt dictioanry
    assert(solutie==[{"id_pachet":3,"data_inceput":datetime.date(2028,7,27),"data_sfarsit":datetime.date(2029,1,10),"destinatie":'Columbia',"pret":10.0}])
    data_sfarsit=datetime.date(2022,9,10)
    solutie=pachete_care_se_termina(oferte,data_sfarsit)
    #pt list
    #assert(solutie==[[1,datetime.date(2021,7,27),datetime.date(2022,9,10),'Tokyo',999.0],[2,datetime.date(2022,7,27),datetime.date(2022,9,10),'Torrino',9999.0]])
    #pt dictionary
    assert(solutie==[{"id_pachet":1,"data_inceput":datetime.date(2021,7,27),"data_sfarsit":datetime.date(2022,9,10),"destinatie":'Tokyo',"pret":999.0},{"id_pachet":2,"data_inceput":datetime.date(2022,7,27),"data_sfarsit":datetime.date(2022,9,10),"destinatie":'Torrino',"pret":9999.0}])

def test_modifica_pachet_data_i():
    """functia de test pentru modifica_pachet_data_i()
    """
    oferte=[]
    undo_list=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2022,9,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo_list)
    new_data_i=datetime.date(2020,7,12)
    oferte=modifica_pachet_data_i(oferte,id_pachet,new_data_i,undo_list)
    #pt list
    #assert(pachet==[1,datetime.date(2020,7,12),datetime.date(2022,9,10),'Tokyo',999.0])
    #pt dictionary
    assert(oferte==[{"id_pachet":1,"data_inceput":datetime.date(2020,7,12),"data_sfarsit":datetime.date(2022,9,10),"destinatie":'Tokyo',"pret":999.0}])
    new_data_i=datetime.date(2026,7,12)
    try:
        oferte=modifica_pachet_data_i(oferte,id_pachet,new_data_i,undo_list)
        assert(False)
    except ValueError as msg:
        assert(str(msg)=="Data de inceput invalida\n")
def test_modifica_pachet_data_s():
    """functia de test pentru modifica_pachet_data_s()
    """
    oferte=[]
    undo_list=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2022,9,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo_list)
    new_data_s=datetime.date(2023,7,12)
    id_pachet=1
    oferte=modifica_pachet_data_s(oferte,id_pachet,new_data_s,undo_list)
    #pt list
    #assert(pachet==[1,datetime.date(2021,7,27),datetime.date(2023,7,12),'Tokyo',999.0])
    #pt dictionary
    assert(oferte==[{"id_pachet":1,"data_inceput":datetime.date(2021,7,27),"data_sfarsit":datetime.date(2023,7,12),"destinatie":'Tokyo',"pret":999.0}])
    new_data_s=datetime.date(2020,7,12)
    id_pachet=1
    try:
        oferte=modifica_pachet_data_s(oferte,id_pachet,new_data_s,undo_list)
        assert(False)
    except ValueError as msg:
        assert(str(msg)=="Data de sfarsit invalida\n")
def test_modifica_pachet_dest():
    """functia de test pentru modifica_pachet_dest()
    """
    oferte=[]
    undo_list=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2022,9,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo_list)
    id_pachet=1
    new_dest="Bucharest"
    pachet=modifica_pachet_dest(oferte,id_pachet,new_dest,undo_list)
    #pt list
    #assert(pachet==[1,datetime.date(2021,7,27),datetime.date(2022,9,10),'Bucharest',999.0])
    #pt dictionary
    assert(oferte==[{"id_pachet":1,"data_inceput":datetime.date(2021,7,27),"data_sfarsit":datetime.date(2022,9,10),"destinatie":'Bucharest',"pret":999.0}])
    new_dest=''
    try:
        oferte=modifica_pachet_dest(oferte,id_pachet,new_dest,undo_list)
        assert(False)
    except ValueError as msg:
        assert(str(msg)=="Destinatie invalida\n")
def test_modifica_pachet_pret(): 
    """functia de test pentru modifica_pachet_pret()
    """
    undo_list=[]
    oferte=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2022,9,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo_list)
    new_pret=10.0
    oferte=modifica_pachet_pret(oferte,id_pachet,new_pret,undo_list)
    #pt list
    #assert(pachet==[1,datetime.date(2021,7,27),datetime.date(2022,9,10),'Tokyo',10.0])
    #pt dictionary
    assert(oferte==[{"id_pachet":1,"data_inceput":datetime.date(2021,7,27),"data_sfarsit":datetime.date(2022,9,10),"destinatie":'Tokyo',"pret":10.0}])
    new_pret=-21
    try:
        oferte=modifica_pachet_pret(oferte,id_pachet,new_pret,undo_list)
        assert(False)
    except ValueError as msg:
        assert(str(msg)=="Pret invalid\n")
#iteratia 2
def test_filtru_1():
    """functia de test pentru filtru_1()
    """
    oferte=[]
    undo=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2022,9,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=2
    data_inceput=datetime.date(2022,7,27)
    data_sfarsit=datetime.date(2022,9,10)
    destinatie='Torrino'
    pret=9999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=3
    data_inceput=datetime.date(2028,7,27)
    data_sfarsit=datetime.date(2029,1,10)
    destinatie='Columbia'
    pret=10.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    pret=5.0
    destinatie="Columbia"
    solutie=filtru_1(oferte,pret,destinatie)
    assert(solutie==[])
    oferte=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2022,9,10)
    destinatie='Tokyo'
    pret=998.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=2
    data_inceput=datetime.date(2022,7,27)
    data_sfarsit=datetime.date(2022,9,10)
    destinatie='Nebraska'
    pret=9999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=3
    data_inceput=datetime.date(2028,7,27)
    data_sfarsit=datetime.date(2029,1,10)
    destinatie='Columbia'
    pret=10.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    pret=999.0
    destinatie="Tokyo"
    solutie=filtru_1(oferte,pret,destinatie)
    #pt list
    #assert(solutie==[[1,datetime.date(2021,7,27),datetime.date(2022,9,10),'Tokyo',998.0]])
    #pt dictionary
    assert(solutie==[{"id_pachet":1,"data_inceput":datetime.date(2021,7,27),"data_sfarsit":datetime.date(2022,9,10),"destinatie":'Tokyo',"pret":998.0}])
def test_filtru_2():
    """functie de test pentru filtru_2()
    """
    oferte=[]
    undo=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2021,9,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=2
    data_inceput=datetime.date(2022,9,27)
    data_sfarsit=datetime.date(2022,10,10)
    destinatie='Torrino'
    pret=9999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=3
    data_inceput=datetime.date(2023,7,27)
    data_sfarsit=datetime.date(2023,10,10)
    destinatie='Columbia'
    pret=10.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    luna=8
    solutie=filtru_2(oferte,luna)
    #pt list
    #assert(solutie==[[2,datetime.date(2022,9,27),datetime.date(2022,10,10),'Torrino',9999.0]])
    #pt dictionary
    assert(solutie==[{"id_pachet":2,"data_inceput":datetime.date(2022,9,27),"data_sfarsit":datetime.date(2022,10,10),"destinatie":'Torrino',"pret":9999.0}])

def test_raport_destinatie_data():
    """fuunctia de test pentru raport_destinatie_data
    """
    oferte=[]
    undo=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2021,9,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=2
    data_inceput=datetime.date(2022,9,27)
    data_sfarsit=datetime.date(2022,10,10)
    destinatie='Torrino'
    pret=9999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=3
    data_inceput=datetime.date(2023,7,27)
    data_sfarsit=datetime.date(2023,10,10)
    destinatie='Columbia'
    pret=10.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    destinatie='Torrino'
    solutie=raport_destinatie_data(oferte,destinatie)
    assert(solutie==1)
    oferte=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2021,9,10)
    destinatie='Torrino'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=2
    data_inceput=datetime.date(2022,9,27)
    data_sfarsit=datetime.date(2022,10,10)
    destinatie='Torrino'
    pret=9999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=3
    data_inceput=datetime.date(2023,7,27)
    data_sfarsit=datetime.date(2023,10,10)
    destinatie='Torrino'
    pret=10.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    destinatie='Torrino'
    solutie=raport_destinatie_data(oferte,destinatie)
    assert(solutie==3)
def test_raport_perioada_data():
    """functia de test pentru raport_perioada_data
    """
    oferte=[]
    undo=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2021,9,10)
    destinatie='Tokyo'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=2
    data_inceput=datetime.date(2022,5,27)
    data_sfarsit=datetime.date(2022,10,10)
    destinatie='Torrino'
    pret=9999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=3
    data_inceput=datetime.date(2023,7,27)
    data_sfarsit=datetime.date(2023,10,10)
    destinatie='Columbia'
    pret=10.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    data_inceput=datetime.date(2022,5,12)
    data_sfarsit=datetime.date(2023,5,12)
    solutie=raport_perioada_data(oferte,data_inceput,data_sfarsit)
    #pt list
    #assert(solutie==[[2,datetime.date(2022,5,27),datetime.date(2022,10,10),'Torrino',9999.0]])
    #pt dictionary
    assert(solutie==[{"id_pachet":2,"data_inceput":datetime.date(2022,5,27),"data_sfarsit":datetime.date(2022,10,10),"destinatie":'Torrino',"pret":9999.0}])

def test_raport_medie_destinatie():
    """functia de test pentru raport_medie_destinatie()
    """
    oferte=[]
    undo=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2021,9,10)
    destinatie='Columbia'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=2
    data_inceput=datetime.date(2022,5,27)
    data_sfarsit=datetime.date(2022,10,10)
    destinatie='Columbia'
    pret=9999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=3
    data_inceput=datetime.date(2023,7,27)
    data_sfarsit=datetime.date(2023,10,10)
    destinatie='Columbia'
    pret=10.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    destinatie='Columbia'
    solutie=raport_medie_destinatie(oferte,destinatie)
    marja_eroare=0.0001
    media=(999.0+9999.0+10.0)/3
    assert(abs(solutie-media)<marja_eroare)
def test_sterge_pachete_dest():
    """functie de test pentru sterge_pachete_dest()
    """
    oferte=[]
    undo=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2021,9,10)
    destinatie='Columbia'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    assert(len(oferte)==1)
    sterge_pachete_dest(oferte,destinatie,undo)
    assert(len(oferte)==0)
    try:
        sterge_pachete_dest(oferte,destinatie,undo)
        assert False
    except ValueError as msg:
        assert(str(msg)=="Lista goala!\n")
    oferte=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2021,9,10)
    destinatie='Columbia'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    destinatie="Kiev"
    try:
        sterge_pachete_dest(oferte,destinatie,undo)
        assert False
    except ValueError as msg:
        assert(str(msg)=="Nu exista oferte cu destinatia data!\n")
def test_sterge_pachete_pret():
    """functie de test pentru sterge_pachete_pret()
    """
    oferte=[]
    undo=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2021,9,10)
    destinatie='Columbia'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    assert(len(oferte)==1)
    sterge_pachete_pret(oferte,pret,undo)
    assert(len(oferte)==0)
    try:
        sterge_pachete_pret(oferte,pret,undo)
        assert(False)
    except ValueError as msg:
        assert(str(msg)=="Lista goala!\n")
    oferte=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2021,9,10)
    destinatie='Columbia'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    pret=1000.0
    try:
        sterge_pachete_pret(oferte,pret,undo)
        assert False
    except ValueError as msg:
        assert str(msg)=="Nu exista oferte cu pretul mai mare decat cel dat!\n"
def test_stergere_pachete_durata():
    """Functia de test pentru stergere_pachete_durata
    """
    oferte=[]
    undo=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2021,9,10)
    destinatie='Columbia'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=2
    data_inceput=datetime.date(2022,5,27)
    data_sfarsit=datetime.date(2022,10,10)
    destinatie='Columbia'
    pret=9999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=3
    data_inceput=datetime.date(2023,7,27)
    data_sfarsit=datetime.date(2023,10,10)
    destinatie='Columbia'
    pret=10.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    durata=200
    sterge_pachete_durata(oferte,durata,undo)
    assert oferte==[]
    try:
        sterge_pachete_durata(oferte,durata,undo)
        assert False
    except ValueError as msg:
        assert str(msg)=="Lista goala!\n"
    oferte=[]
    id_pachet=1
    data_inceput=datetime.date(2021,7,27)
    data_sfarsit=datetime.date(2021,9,10)
    destinatie='Columbia'
    pret=999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=2
    data_inceput=datetime.date(2022,5,27)
    data_sfarsit=datetime.date(2022,10,10)
    destinatie='Columbia'
    pret=9999.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    id_pachet=3
    data_inceput=datetime.date(2023,7,27)
    data_sfarsit=datetime.date(2024,10,10)
    destinatie='Columbia'
    pret=10.0
    pachet=creare_pachet(id_pachet,data_inceput,data_sfarsit,destinatie,pret)
    adaugare_pachet(pachet,oferte,undo)
    durata=150
    sterge_pachete_durata(oferte,durata,undo)
    assert oferte==[{"id_pachet":3,"data_inceput":datetime.date(2023,7,27),"data_sfarsit":datetime.date(2024,10,10),"destinatie":'Columbia',"pret":10.0}]
    durata=150
    try:
        sterge_pachete_durata(oferte,durata,undo)
        assert False
    except ValueError as msg:
        assert str(msg)=="Nu exista oferte cu durata mai mica decat cea specificata! \n"
def test_add_to_undo():
    """Functia de test pentru add_to_undo()
    """
    pass

def test_undo():
    """Functia de test pentru undo
    """
    #caz undo_list vida
    undo_list=[]
    oferte=[]
    try:
        undo(oferte,undo_list)
        assert False
    except ValueError as msg:
        assert str(msg)=="Nu exista operatie de refacut!\n"
    #caz avem doar o operatie facuta si trebuie sa eliberam lista de oferte
    id_pachet=1
    data_i=datetime.date(2020,12,12)
    data_s=datetime.date(2021,12,12)
    dest="New York"
    pret=68.9
    creaza_valideaza_adauga(id_pachet,data_i,data_s,dest,pret,oferte,undo_list)
    assert oferte==[{"id_pachet":1,"data_inceput":datetime.date(2020,12,12),"data_sfarsit":datetime.date(2021,12,12),"destinatie":"New York","pret":68.9}]
    oferte=undo(oferte,undo_list)
    assert oferte==[]
    #caz pentru undo dupa mai multe adaugari
    id_pachet=1
    data_i=datetime.date(2020,12,12)
    data_s=datetime.date(2021,12,12)
    dest="New York"
    pret=68.9
    creaza_valideaza_adauga(id_pachet,data_i,data_s,dest,pret,oferte,undo_list)
    id_pachet=2
    data_i=datetime.date(2020,12,12)
    data_s=datetime.date(2021,12,12)
    dest="New York"
    pret=68.9
    creaza_valideaza_adauga(id_pachet,data_i,data_s,dest,pret,oferte,undo_list)
    id_pachet=3
    data_i=datetime.date(2020,12,12)
    data_s=datetime.date(2021,12,12)
    dest="New York"
    pret=68.9
    creaza_valideaza_adauga(id_pachet,data_i,data_s,dest,pret,oferte,undo_list)
    assert oferte==[{"id_pachet":1,"data_inceput":datetime.date(2020,12,12),"data_sfarsit":datetime.date(2021,12,12),"destinatie":"New York","pret":68.9},{"id_pachet":2,"data_inceput":datetime.date(2020,12,12),"data_sfarsit":datetime.date(2021,12,12),"destinatie":"New York","pret":68.9},{"id_pachet":3,"data_inceput":datetime.date(2020,12,12),"data_sfarsit":datetime.date(2021,12,12),"destinatie":"New York","pret":68.9}]
    oferte=undo(oferte,undo_list)
    assert oferte==[{"id_pachet":1,"data_inceput":datetime.date(2020,12,12),"data_sfarsit":datetime.date(2021,12,12),"destinatie":"New York","pret":68.9},{"id_pachet":2,"data_inceput":datetime.date(2020,12,12),"data_sfarsit":datetime.date(2021,12,12),"destinatie":"New York","pret":68.9}]
    oferte=undo(oferte,undo_list)
    assert oferte==[{"id_pachet":1,"data_inceput":datetime.date(2020,12,12),"data_sfarsit":datetime.date(2021,12,12),"destinatie":"New York","pret":68.9}]
    #caz pentru modificare continut lista
    new_data=datetime.date(2021,1,1)
    id_pachet=1
    modifica_pachet_data_i(oferte,id_pachet,new_data,undo_list)
    assert oferte==[{"id_pachet":1,"data_inceput":datetime.date(2021,1,1),"data_sfarsit":datetime.date(2021,12,12),"destinatie":"New York","pret":68.9}]
    oferte=undo(oferte,undo_list)
    assert oferte==[{"id_pachet":1,"data_inceput":datetime.date(2020,12,12),"data_sfarsit":datetime.date(2021,12,12),"destinatie":"New York","pret":68.9}]
    #caz pentru stergere din lista
    destinatie="New York"
    sterge_pachete_dest(oferte,destinatie,undo_list)
    assert oferte==[]
    oferte=undo(oferte,undo_list)
    assert oferte==[{"id_pachet":1,"data_inceput":datetime.date(2020,12,12),"data_sfarsit":datetime.date(2021,12,12),"destinatie":"New York","pret":68.9}]

def run_all_tests():
    test_get_duration()
    test_creare_pachet()
    test_validare_pachet()
    test_adaugare_pachet()
    test_sejur_interval_dat()
    test_pachete_ieftine_destinatie_data()
    test_pachete_care_se_termina()
    test_modifica_pachet_data_i()
    test_modifica_pachet_data_s()
    test_modifica_pachet_dest()
    test_modifica_pachet_pret()
    #iteratie 2
    test_filtru_1()
    test_filtru_2()
    test_raport_destinatie_data()
    test_raport_perioada_data()
    test_raport_medie_destinatie()
    #iteratie 3
    test_sterge_pachete_dest()
    test_sterge_pachete_pret()
    test_stergere_pachete_durata()
    test_undo()
run_all_tests()
