
from services.service_eveniment import *

import unittest

class Test_Event:
    """Clasa de teste Evenimente
    """
    def test_creare_eveniment(self):
        """Functia de test pentru crearea unui obiect din clasa Eveniment
        """
        iD=1
        data=datetime.date(2020,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        assert event.get_identificator()==iD
        assert event.get_data()==data
        assert event.get_timp()==timp
        assert event.get_descriere()==descriere
    def test_valideaza(self):
        """Functia de test pentru valideaza_Eveniment()
        """
        iD=1
        data=datetime.date(2025,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        vali=Validator()
        vali.valideaza_eveniment(event)
        iD_invalid=-1
        data_invalid=datetime.date(2020,2,12)
        timp_invalid=-19
        descriere_invalida=""
        try:
            event_naspa= Eveniment(iD_invalid,data_invalid,timp_invalid,descriere_invalida)
            vali.valideaza_eveniment(event_naspa)
            assert False
        except ValidationError as msg:
            assert str(msg) =="ID numeric invalid!\nData invalida! Data evenimentului trebuie sa fie in viitor\nTimp invalid!\nDescriere invalida!\n"
       
    def test_adauga_eveniment(self):
        """Functia de test pentru adauga_Eveniment()
        """
        repo=Repository_Eveniment()
        assert repo.get_events()==[]
        iD=1
        data=datetime.date(2020,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        repo.adauga_eveniment(event)
        list=[]
        list.append(event)
        assert repo.get_events()==list
        iD=1
        data=datetime.date(2020,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        try:
            repo.adauga_eveniment(event)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Id deja existent!\n"
        
    def test_stergere_eveniment(self):
        """Functia de test pentru stergere_Eveniment
        """
        repo=Repository_Eveniment()
        assert repo.get_events()==[]
        iD=1
        data=datetime.date(2020,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        repo.adauga_eveniment(event)
        assert len(repo.get_events())==1
        repo.sterge_eveniment(iD)
        assert repo.get_events()==[]
        try:
            repo.sterge_eveniment(iD)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Nu exista ce vrei sa elimini!\n"
    def test_update_data(self):
        """Functia de test pentru update_event_data()
        """
        repo=Repository_Eveniment()
        assert repo.get_events()==[]
        iD=1
        data=datetime.date(2020,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        repo.adauga_eveniment(event)
        new_data=datetime.date(2027,7,12)
        repo.update_event_data(new_data,event)
        assert event.get_data()==new_data
        new_data=datetime.date(2020,7,19)
        try:
            repo.update_event_data(new_data,event)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Noua data invalida!\n"
    def test_update_timp(self):
        """Functia de test pentru update_event_timp()
        """
        repo=Repository_Eveniment()
        assert repo.get_events()==[]
        iD=1
        data=datetime.date(2020,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        repo.adauga_eveniment(event)
        new_timp=5.9
        repo.update_event_timp(new_timp,event)
        assert event.get_timp()==new_timp
        new_timp=-11
        try:
            repo.update_event_timp(new_timp,event)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Timp nou invalid!\n"
    def test_update_descriere(self):
        """Functia de test pentru update_event_descriere
        """
        repo=Repository_Eveniment()
        assert repo.get_events()==[]
        iD=1
        data=datetime.date(2020,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        repo.adauga_eveniment(event)
        new_descriere="o sa fie naspa"
        repo.update_event_descriere(new_descriere,event)
        assert event.get_descriere()==new_descriere
        new_descriere=""
        try:
            repo.update_event_descriere(new_descriere,event)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Descriere vida!\n"
    def run_all_event_test(self):
        self.test_creare_eveniment()
        self.test_adauga_eveniment()
        self.test_valideaza()
        self.test_stergere_eveniment()
        self.test_update_data()
        self.test_update_timp()
        self.test_update_descriere()
class Test_Persoana:
    """Clasa de teste pentru Persoana
    """
    def test_creaza_persoana(self):
        """Functia de test creaza_Persoana
        """
        personID=2
        nume="Adrian"
        adresa="Calea Turzii"
        person=Persoana(personID,nume,adresa)
        assert personID==person.get_identificator()
        assert nume==person.get_nume()
        assert adresa==person.get_adresa()
    def test_valideaza_persoana(self):
        """Functia de test pentru validare Persoana
        """
        personID=2
        nume="Adrian"
        adresa="Calea Turzii"
        person=Persoana(personID,nume,adresa)
        vali=Validator()
        vali.valideaza_persoana(person)
        id_invalid=-12
        nume_invalid=""
        adresa_invalida=""
        try:
            person_invalid=Persoana(id_invalid,nume_invalid,adresa_invalida)
            vali.valideaza_persoana(person_invalid)
        except ValidationError as msg:
            assert str(msg)=="ID numeric invalid!\nNume invalid!\nAdresa invalida!\n"
    def test_adauga_persoana(self):
        """Functia de test pentru adauga_Persoana()
        """
        repo=Repository_Persoana()
        assert repo.get_persoane()==[]
        personID=2
        nume="Adrian"
        adresa="Calea Turzii"
        person=Persoana(personID,nume,adresa)
        repo.adauga_persoana(person)
        assert len(repo.get_persoane())==1
        try:
            repo.adauga_persoana(person)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Id deja existent!\n"
            
    def test_sterge_persoana(self):
        """Functia de test pentru sterge_Persoana()
        """
        repo=Repository_Persoana()
        assert repo.get_persoane()==[]
        personID=2
        nume="Adrian"
        adresa="Calea Turzii"
        person=Persoana(personID,nume,adresa)
        #caz repo gol
        try:
            repo.sterge_persoana(personID)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Nu exista ce vrei sa elimini!\n"
        repo.adauga_persoana(person)
        personID=13
        nume="Alexandru"
        adresa="undeva"
        new_person=Persoana(personID,nume,adresa)
        #caz stergere ceva ce nu se gaseste in repo
        try:
            repo.sterge_persoana(personID)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Nu exista ce vrei sa elimini!\n"
        repo.adauga_persoana(new_person)
        repo.sterge_persoana(personID)
        assert len(repo.get_persoane())==1
    def test_update_Persoana_nume(self):
        """Functia de test pentru update_nume_Persoana()
        """
        repo=Repository_Persoana()
        assert repo.get_persoane()==[]
        iD=1
        nume="ion"
        adresa="aici"
        person=Persoana(iD,nume,adresa)
        repo.adauga_persoana(person)
        new_name="Johnathan"
        repo.update_nume_persoana(new_name,person)
        assert person.get_nume()==new_name
        new_name=""
        try:
            repo.update_nume_persoana(new_name,person)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Noul nume invalid!\n"
    def test_update_Persoana_adresa(self):
        """Functia de test pentru update_adresa_Persoana()
        """
        repo=Repository_Persoana()
        assert repo.get_persoane()==[]
        iD=1
        nume="ion"
        adresa="aici"
        person=Persoana(iD,nume,adresa)
        repo.adauga_persoana(person)
        new_adresa="acolo"
        repo.update_adresa_persoana(new_adresa,person)
        assert person.get_adresa()==new_adresa
        new_adresa=""
        try:
            repo.update_adresa_persoana(new_adresa)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Noua adresa invalida!\n"
    def run_all_person_tests(self):
        self.test_creaza_persoana()
        self.test_valideaza_persoana()
        self.test_adauga_persoana()
        self.test_sterge_persoana()
        self.test_update_Persoana_nume()
        self.test_update_Persoana_adresa()
class Teste_Participari:
    def test_creare_participare(self):
        persoana=Persoana(1,"Denis","acolo")
        eveniment=Eveniment(1,datetime.date(2025,7,27),24.0,"bines")
        partikip=Inscriere(eveniment,persoana)
        assert partikip.get_eveniment().get_identificator()==1
        assert partikip.get_persoana().get_identificator()==1
        assert partikip.get_eveniment()==eveniment
        assert partikip.get_persoana()==persoana
    def run_all_p_tests(self):
        self.test_creare_participare()
      

class Teste_rmd:
    """Clasa de teste pentru entitati generate 'aleatoriu'
    """
    def __init__(self):
        self.rando=Randomiser()
    def rmd_test_creare_event(self):
        """Functie de test pentru creare Eveniment
        """
        seed=5
        data_l=datetime.date(2020,7,19)
        data_h=datetime.date(2800,12,12)
        eveniment=self.rando.creaza_eveniment_random(seed,1,1000,data_l,data_h)
        id=self.rando.creaza_id_random(seed,1,1000)
        data=self.rando.creaza_data_random(seed,data_l,data_h)
        timp=self.rando.creaza_timp_random(seed)
        descriere=self.rando.creaza_descriere_random(seed)
        assert eveniment.get_identificator()==id
        assert eveniment.get_data()==data
        assert eveniment.get_timp()==timp
        assert eveniment.get_descriere()==descriere
    def rmd_test_creare_persoana(self):
        seed=10
        persoana=self.rando.creaza_persoana_random(seed,1,1000)
        id=self.rando.creaza_id_random(seed,1,1000)
        nume=self.rando.creaza_nume_random(seed)
        ceva=self.rando.pick_random_int(seed)
        adresa=self.rando.creaza_adresa_random(seed+ceva)
        assert persoana.get_identificator()==id
        assert persoana.get_nume()==nume
        assert persoana.get_adresa()==adresa
    def rmd_test_validare_event(self):
        seed=101
        data_l=datetime.date(2020,7,19)
        data_h=datetime.date(2800,12,12)
        eveniment=self.rando.creaza_eveniment_random(seed,1,1000,data_l,data_h)
        validator_eveniment=Validator()
        validator_eveniment.valideaza_eveniment(eveniment)
        new_event=self.rando.creaza_eveniment_random(seed,-1000,0,data_l,data_h)
        try:
            validator_eveniment.valideaza_eveniment(new_event)
            assert False
        except ValidationError as msg:
            assert str(msg)=="ID numeric invalid!\n"
        data_l=datetime.date(1000,10,10)
        data_h=datetime.date(2024,1,1)
        new_event=self.rando.creaza_eveniment_random(seed,-1000,0,data_l,data_h)
        try:
            validator_eveniment.valideaza_eveniment(new_event)
            assert False
        except ValidationError as msg:
            assert str(msg)=="ID numeric invalid!\nData invalida! Data evenimentului trebuie sa fie in viitor\n"
    def rmd_test_validare_persoana(self):
        seed=18
        persoana=self.rando.creaza_persoana_random(seed,1,1000)
        validator_persoana=Validator()
        validator_persoana.valideaza_persoana(persoana)
        seed=420
        persoana=self.rando.creaza_persoana_random(seed,1,1000)
        try:
            validator_persoana.valideaza_persoana(persoana)
            assert False
        except ValidationError as msg:
            assert str(msg)=="Nume invalid!\nAdresa invalida!\n"
        seed=420
        persoana=self.rando.creaza_persoana_random(seed,-1000,0)
        try:
            validator_persoana.valideaza_persoana(persoana)
            assert False
        except ValidationError as msg:
            assert str(msg)=="ID numeric invalid!\nNume invalid!\nAdresa invalida!\n"
    def run_teste_rmd(self):
        self.rmd_test_creare_event()   
        self.rmd_test_creare_persoana()
        self.rmd_test_validare_event()
        self.rmd_test_validare_persoana()
class MainTester():
    def __init__(self):
        self.__test1=Test_Event()
        self.__test2=Test_Persoana()
        self.__test3=Teste_Participari()
        self.__test4=Teste_rmd()
    def run_test(self):
        self.__test1.run_all_event_test()
        self.__test2.run_all_person_tests()
        self.__test3.run_all_p_tests()
        self.__test4.run_teste_rmd()