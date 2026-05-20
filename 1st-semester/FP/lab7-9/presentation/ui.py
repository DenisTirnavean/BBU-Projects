from services.service_eveniment import *
import os
class Meniu:
    def __init__(self):
        pass
    def meniu_0(self):
        print("Bine ai venit!")
        print("Ce doresti sa faci?")
        print("1.Gestionare Evenimente")
        print("2.Gestionare persoane")
        print("3.Gestionare inscrieri")
        print("x.EXIT")
    def meniu_1(self):
        print("GESTIONAREA Evenimente")
        print("======================")
        print("Operatii disponibile:")
        print("1.Adauga Eveniment")
        print("2.Sterge Eveniment")
        print("3.Modifica Eveniment")
        print("4.Afisare Evenimente")
        print("5.Cautare Eveniment")
        print("6.Generare Evenimente")
        print("x.Go back")
        print("Ce operatie doresti sa realizezi? ( 1 / 2 / 3 / 4 )")
    def meniu_2(self):
        print("GESTIONAREA PERSOANE")
        print("======================")
        print("Operatii disponibile:")
        print("1.Adauga Persoana")
        print("2.Sterge Persoana")
        print("3.Modifica Persoana")
        print("4.Afisare persoane")
        print("5.Cauta persoana")
        print("6.Generare persoane")
        print("x.Go back")
        print("Ce operatie doresti sa realizezi? ( 1 / 2 / 3 / 4 )")
    def meniu_update_event(self):
        print("1.Modifica data evenimentului")
        print("2.Modifica durata evenimentului")
        print("3.Modidica descrierea evenimentului")
    def meniu_update_person(self):
        print("1.Modifica numele persoanei")
        print("2.Modifica adresa persoanei")
    def meniu_inscrieri(self):
        print("INSCRIERI")
        print("==========")
        print("1.Inscrie o persoana la un eveniment")
        print("2.Afiseaza inscrierile")
        print("3.Inscrierile unei anumite persoane")
        print("4.Persoanele care participa la cele mai multe evenimente")
        print("5.Top 20% evenimente cu cei mai multi participanti")
        print("6.Generare inscrieri random")
        print("x. Go back")
class Consola:
    
    def __init__(self):
        self.servicii_evenim=Service_Eveniment(Repository_Eveniment())
        self.servicii_pers=Service_Persoana(Repository_Persoana())
        self.servicii_inscrieri=Service_inscriere(self.servicii_pers,self.servicii_evenim)
        self.__meniu=Meniu()
    def __ui_adauga_even(self):
        print("ADAUGARE Eveniment")
        print("==================")
        try:
            id=int(input("Id:"))
            zi=int(input("Zi:"))
            luna=int(input("Luna:"))
            an=int(input("Anul:"))
        except ValueError:
            print("Tip numeric invalid!!!")
            return
        data=datetime.date(an,luna,zi)
        timp=float(input("Durata:"))
        desc=input("Descriere:")
        self.servicii_evenim.creaza_valideaza_adauga(id,data,timp,desc)
        print("Eveniment adaugat cu succes!")
    def __ui_modific_data(self,id):
        try:
            zi=int(input("Noua zi:"))
            luna=int(input("Noua luna:"))
            an=int(input("Noul an:"))
            data=datetime.date(an,luna,zi)
        except ValueError:
            print("Data invalida")
            return
        self.servicii_evenim.modifica_event_data(id,data)
        print("Eveniment modificat cu succes!")

    def __ui_modific_timp(self,id):
        try:
            timp=float(input("Noua durata:"))
        except ValueError:
            print("Valoare numerica invalida!!")
            return
        self.servicii_evenim.modifica_event_timp(id,timp)
        print("Eveniment modificat cu succes!")
    def __ui_modific_desc(self,id):
        desc=input("Noua descriere:")
        self.servicii_evenim.modifica_event_descriere(id,desc)
        print("Eveniment modificat cu succes!")

    def __ui_modifica_even(self):
        print("MODIFICA Eveniment")
        print("==================")
        comenzi={
            "1":self.__ui_modific_data,
            "2":self.__ui_modific_timp,
            "3":self.__ui_modific_desc
        }
        print("Evenimente disponibile: ")
        self.__ui_afisare_even()
        id=int(input("Ce eveniment doresti sa modifici? Id="))
        os.system('cls')
        self.__meniu.meniu_update_event()
        cmd=input("Ce anume doresti sa modifici? ( 1 / 2 / 3 ): ")
        if cmd in comenzi:
            comenzi[cmd](id)
        else:
            print("Comanda invalida!!")
            return
    def __ui_sterge_even(self):
        print("STERGE Eveniment")
        print("==================")
        print("Evenimente disponibile: ")
        self.__ui_afisare_even()
        id=int(input("Id-ul evenimentului pe care doresti sa-l stergi: "))
        self.servicii_evenim.sterge_event(id)
        print("Eveniment sters cu succes!!!")
    def __ui_afisare_even(self):

        lista=self.servicii_evenim.get_all()
        if len(lista)==0:
            print("Lista goala!!!!")
            return
        else: 
            for i in lista:
                print(i)
        
    def __ui_cauta_even(self):
        os.system('cls')
        id=int(input("Id-ul evenimentului cautat: "))
        eveniment=self.servicii_evenim.cauta_eveniment(id)
        print(eveniment)
    def __ui_random_even(self):
        os.system('cls')
        try:
            cate=int(input("Cate evenimente doresti sa generezi: "))
            numar=self.servicii_evenim.creaza_evenimente_random(cate)
            print("S-au generat cu succes "+str(numar)+" evenimente!")
        except GenerationError as msg:
            print(msg)
    def __ui_Eveniment(self):
        os.system('cls')
        self.__meniu.meniu_1()
        dic_1={
            "1":self.__ui_adauga_even,
            "2":self.__ui_sterge_even,
            "3":self.__ui_modifica_even,
            "4":self.__ui_afisare_even,
            "5":self.__ui_cauta_even,
            "6":self.__ui_random_even
        }
        cmd=input()
        cmd=cmd.strip()
        if cmd in ['X','x']:
            return
        if cmd not in dic_1:
            print("Comanda invalida!!!")
            input("Apasa orice pentru a continua")
            return
        else:
            dic_1[cmd]()
    def __ui_adauga_pers(self):
        print("ADAUGARE Persoana")
        print("==================")
        try:
            id=int(input("Id:"))
        except ValueError:
            print("Id numeric invalid!!!")
            return
        nume=input("Nume:")
        adresa=input("Adresa:")
        self.servicii_pers.creaza_valideaza_adauga(id,nume,adresa)
        print("Persoana adaugata cu succes!")
    def __ui_sterge_pers(self):
        print("STERGE Persoana")
        print("==================")
        print("Persoane disponibile: ")
        self.__ui_afisare_pers()
        try:
            id=int(input("Id-ul persoanei pe care doresti sa o stergi: "))
        except ValueError:
            print("Id numeric invalid!!!")
            return
        self.servicii_pers.sterge_persoana(id)
        print("Persoana stearsa cu succes!!")
    def __ui_afisare_pers(self):
        lista=self.servicii_pers.get_all()
        if len(lista)==0:
            print("Lista e goala!!!")
            return
        for i in lista:
            print(i)
    def __ui_cauta_pers(self):
        os.system('cls')
        id=int(input("Id-ul persoanei cautate:"))
        persoana=self.servicii_pers.cauta_persoana(id)
        print(persoana)
    def __ui_random_pers(self):
        os.system('cls')
        try:
            cate=int(input("Cate persoane doresti sa generezi: "))
            numar=self.servicii_pers.creaza_persoane_random(cate)
            print("S-au generat cu succes "+str(numar)+" persoane")
        except GenerationError as msg:
            print(msg)
    def __ui_Persoana(self):
        os.system('cls')
        self.__meniu.meniu_2()
        dic_2={
            "1":self.__ui_adauga_pers,
            "2":self.__ui_sterge_pers,
            "3":self.__ui_modifica_pers,
            "4":self.__ui_afisare_pers,
            "5":self.__ui_cauta_pers,
            "6":self.__ui_random_pers
        }
        cmd=input()
        cmd=cmd.strip()
        if cmd in ['X','x']:
            return
        if cmd not in dic_2:
            print("Comanda invalida!!!")
            input("Apasa orice pentru a continua")
            return
        else:
            os.system('cls')
            dic_2[cmd]()
    def __ui_modifica_nume(self,id):
        nume=input("Noul nume:")
        self.servicii_pers.modifica_nume(id,nume)
        print("Persoana modificata cu succes!")

    def __ui_modifica_adresa(self,id):
        adresa=input("Adresa noua:")
        self.servicii_pers.modifica_adresa(id,adresa)
        print("Persoana modificata cu succes!")

    def __ui_modifica_pers(self):
        print("MODIFICARE persoana")
        print("====================")
        comenzi={
            "1":self.__ui_modifica_nume,
            "2":self.__ui_modifica_adresa
        }
        print("Persoane disponibile:")
        self.__ui_afisare_pers()
        id=int(input("Informatiile carei persoane doresti sa modifici? Id:"))
        os.system('cls')
        self.__meniu.meniu_update_person()
        cmd=input("Ce anume doresti sa modifici? ( 1 / 2 ):")
        if cmd in comenzi:
            comenzi[cmd](id)
        else:
            print("Comanda invalida!!")
            return
    def __ui_adauga_inscr(self):
        id_persoana=int(input("Id-ul persoanei pe care doresti s-o inscri la un eveniment:"))
        id_eveniment=int(input("Id-ul evenimentului la care se inscrie persoana:"))
        self.servicii_inscrieri.creaza_valideaza_adauga(id_persoana,id_eveniment)
        print("Inscriere realizata cu succes!")
    def __ui_afisare_inscr(self):
        lista=self.servicii_inscrieri.get_all()
        if len(lista)==0:
            print("Lista goala!!!")
            return
        print("Inscrierile sunt: ")
        for inscriere in lista:
            print(inscriere)
    def __ui_inscrierile_unei_persoane(self):
        os.system('cls')
        print("Inscrierile unei anumite persoane")
        print("=================================")
        print("Persoane disponibile:")
        lista=self.servicii_pers.get_all()
        for i in lista:
            print(i)
        id_pers=int(input("Persoana care va intereseaza (id-ul numeric) : "))
        lista=self.servicii_inscrieri.evenimente_la_care_participa_persoana(id_pers)
        persoana=self.servicii_pers.cauta_persoana(id_pers)
        print(str(persoana.get_nume())+" participa la evenimentele: ",end="")
        for inscriere in lista:
            print(inscriere.get_eveniment().get_descriere(),end=", ")
        print("")
    def __ui_cele_mai_inscrise_pers(self):
        os.system('cls')
        print("Cele mai inscrise persoane")
        print("==========================")
        lista=self.servicii_inscrieri.cele_mai_inscrise_pers()
        if len(lista)==0:
            print("Nu exista persoane inscrise!!!")
            return
        i=0
        nume=lista[i].get_nume()
        nr=lista[i].get_nr_participari()
        print(str(nume)+" a participat la "+str(nr)+" evenimente")
        while i+1<len(lista):
            if lista[i].get_nr_participari()==lista[i+1].get_nr_participari():
                nume=lista[i+1].get_nume()
                nr=lista[i+1].get_nr_participari()
                print(str(nume)+" a participat la "+str(nr)+" evenimente")
            else: break
            i+=1
            
    def __ui_top20(self):
        print("Top 20% evenimente cu cei mai multi participanti")
        print("===============================================")
        lista=self.servicii_inscrieri.top20()
        if len(lista)==0:
            print("Nu exista inscrieri!!!")
            return   
        else:
            contor=1
            for eveniment in lista:
                descriere=eveniment.get_descriere()
                nr_participanti=eveniment.get_nr_participanti()
                print(str(contor)+". "+str(descriere)+" are "+str(nr_participanti)+" participanti")
                contor+=1
    def __ui_inscriere_random(self):
        """Functia de generare a unei inscrierii random
        """
        os.system('cls')
        try:
            cate=int(input("Cate inscrieri doresti sa generezi: "))
            numar=self.servicii_inscrieri.creare_inscriere_random(cate)
            print("S-au generat cu succes "+str(numar)+" inscrieri")
        except GenerationError as msg:
            print(msg)        
    def __ui_inscriere(self):
        os.system('cls')
        self.__meniu.meniu_inscrieri()
        dic_comenzi={
            "1":self.__ui_adauga_inscr,
            "2":self.__ui_afisare_inscr,
            "3":self.__ui_inscrierile_unei_persoane,
            "4":self.__ui_cele_mai_inscrise_pers,
            "5":self.__ui_top20,
            "6":self.__ui_inscriere_random
        }
        cmd=input("Ce doresti sa faci? ( 1 / 2 / 3 / 4 / 5 / x )")
        cmd=cmd.strip()
        if cmd=='x' or cmd=='X':
            return
        elif cmd in dic_comenzi:
            dic_comenzi[cmd]()
        else:
            print("Comanda invalida!!!")
            return
    def run(self):
        dic_comenzi={
            "1": self.__ui_Eveniment,
            "2": self.__ui_Persoana,
            "3": self.__ui_inscriere
        }

        while True:
            os.system('cls')
            self.__meniu.meniu_0()
            cmd=input("Ce operatie doresti sa executi? ( 1 / 2 / 3 / x )")
            cmd=cmd.strip()
            if cmd=='':
                continue
            if cmd in ['x','X','BAU']:
                break
            if cmd in dic_comenzi:
                try:
                    dic_comenzi[cmd]()
                except ValueError as msg:
                    print(f"Tip invalid de date: {msg}")
                except ValidationError as msg:
                    print(f"Eroare de validare: {msg}")
                except RepositoryError as msg:
                    print(f"Eroare de stocare: {msg}")
                finally: input("Apasa orice pentru a continua")
            else:
                print("Comanda invalida!")
                input("Apasa orice pentru a continua")

class ConsolaFile(Consola):
    def __init__(self,cale_catre_fisier_eveniment,cale_catre_fisier_persoana,cale_catre_fisier_inscrieri):
        super().__init__()
        self.servicii_evenim=Service_Eveniment(File_Repository_Eveniment(cale_catre_fisier_eveniment))
        self.servicii_pers=Service_Persoana(File_Repository_Persoana(cale_catre_fisier_persoana))
        self.servicii_inscrieri=Service_Inscriere_file(self.servicii_pers,self.servicii_evenim,cale_catre_fisier_inscrieri)
    
        