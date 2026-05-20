from repository.repo_event import *
from repository.repo_person import *
from repository.repo_inscriere import *
from utils.sortari import *
class Randomiser:
    def pick_random_int(self,seed):
        random.seed(seed)
        return random.randint(0,20)
    def creaza_id_random(self,seed,inceput,final):
        random.seed(seed)
        return random.randint(inceput,final)
    def creaza_nume_random(self,seed):
        """Functie care returneaza un string de caractere random considerate a fi un nume

        input:
            seed (int): o valoare aleasa arbitrar

        Returns:
            nume(str): un sir de caractere cu lungime variabila
        """
        nume_len=self.pick_random_int(seed)
        nume=""
        for i in range(nume_len):
            nume+=random.choice(ascii_lowercase)
        nume=nume.capitalize()
        return nume
    def creaza_adresa_random(self,seed):
        """Functie care returneaza un string de caractere random considerate a fi o adresa

        input:
            seed (int): o valoare aleasa arbitrar

        Returns:
        adresa(str): un sir de caractere cu lungime variabila
        """
        random.seed(seed)
        adresa_len=self.pick_random_int(seed)
        adresa=""
        for i in range(adresa_len):
            adresa+=random.choice(ascii_lowercase+digits)
        return adresa
    def creaza_data_random(self,seed,data_low,data_high):
        """Functie care returneaza o lista formats din 3 numere intregi reprezentand aleatoriu o zi, o luna si un an

        Args:
            seed (int): o valoare aleasa arbitrar
        Returns:
            data(list): o data calendaristica aleatoare
        """
        data=[]
        random.seed(seed)
        delta=data_high-data_low
        cat_peste=random.randrange(delta.days)
        return data_low+datetime.timedelta(cat_peste)
    def creaza_timp_random(self,seed):
        """functie care creaza o durata de timp random

        input:
            seed (int): valoare aleasa arbitrar

        Returns:
            timp(float): numar generat pe baza argumentului seed
        """
        random.seed(seed)
        return random.random()+float(random.randint(1,20))
    def creaza_descriere_random(self,seed):
        """Functie care returneaza un string de caractere random considerate a fi o adresa

        input:
            seed (int): o valoare aleasa arbitrar

        Returns:
        adresa(str): un sir de caractere cu lungime variabila
        """
        random.seed(seed)
        desc_len=self.pick_random_int(seed)
        descriere=""
        for i in range(desc_len):
            descriere+=random.choice(ascii_lowercase)
        return descriere
    def creaza_eveniment_random(self,seed,id_low,id_high,data_low,data_high):
        """Functia de creare eveniment random

        Args:
            seed (int): numar ales arbitrar
            id_low (int): marginea inferioara  a intervalului in care doresti sa se afle id-ul generat random
            id_high (int): marginea superioara  a intervalului in care doresti sa se afle id-ul generat random
            data_low(datetime.date): marginea inferioara  a intervalului in care doresti sa se afle data generata random
            data_high(datetime.date): marginea superioara  a intervalului in care doresti sa se afle data generata random

        Returns:
            eveniment(Eveniment): obiect clasa eveniment generat aleatoriu 
        """
        random.seed(seed)
        id=self.creaza_id_random(seed,id_low,id_high)
        data=self.creaza_data_random(seed,data_low,data_high)
        timp=self.creaza_timp_random(seed)
        descriere=self.creaza_descriere_random(seed)
        eveniment=Eveniment(id,data,timp,descriere)
        return eveniment
    def creaza_persoana_random(self,seed,id_low,id_high):
        """Functia de generare aleatorie a unui obiect clasa Persoana

        input:
            seed (int): numar ales arbitrar
            id_low (int): marginea inferioara  a intervalului in care doresti sa se afle id-ul generat random
            id_high (int): marginea superioara  a intervalului in care doresti sa se afle id-ul generat random

        Returns:
            persoana(Persoana): obiect clasa Persoana
        """
        random.seed(seed)
        id=self.creaza_id_random(seed,id_low,id_high)
        nume=self.creaza_nume_random(seed)
        ceva=self.pick_random_int(seed)
        adresa=self.creaza_adresa_random(seed+ceva)
        persoana=Persoana(id,nume,adresa)
        return persoana
class Service_Eveniment:
    def __init__(self,repo_eveniment):
        self.repo_Eveniment=repo_eveniment
        self.validator = Validator()
        self.random = Randomiser()
    def creaza_valideaza_adauga(self,id,data,timp,descriere):
        """Functia de creare, validare si adaugare in repository a unui obiect din clasa Eveniment

        input:
            id (int): id-ul Evenimentului
            data (data calendaristica): data Evenimentului
            timp (float): durata Evenimentului
            descriere (string): descrierea Evenimentului
        output:
            -   
        Raises:
            Ridica erori tip RepositoryError sau ValidationError cu mesaje specifice:
            "Id deja existent!\n", daca id-ul obiectul event este deja folosit in lista de Evenimente a obiectului curent Repository_Eveniment
            "ID numeric invalid!\n" , daca ID al obiectului din clasa Eveniment <=0
            "Data invalida!\n", daca data noului Eveniment este situata in trecut
            "Timp invalid!\n", daca durata Evenimentului este nula/ mai mica ca zero
            "Descriere invalida!\n", daca descrierea este vida
        """
        event=Eveniment(id,data,timp,descriere)
        self.validator.valideaza_eveniment(event)
        self.repo_Eveniment.adauga_eveniment(event)
    def creaza_evenimente_random(self,cate):
        """Functia de generare a unui eveniment aleatoriu
        """
        ok=0
        for i in range(cate):
            seed=random.random()
            eveniment=self.random.creaza_eveniment_random(seed,1,1000,DATA_AZI(),DATA_AZI()+datetime.timedelta(1000))
            try:
                self.validator.valideaza_eveniment(eveniment)
                self.repo_Eveniment.adauga_eveniment(eveniment)
                ok+=1
            except ValidationError:
                pass
            except RepositoryError:
                pass
        if ok==0:
            raise GenerationError("Ceva nu a mers bine!!!")
        return ok
    def cauta_eveniment(self,id):
        """Functia de cautare eveniment in obiectul de clasa Repository_eveniment
        input:
            id (int): id-ul evenimentului
        returns:
            eveniment(Eveniment): evenimentul cu id-ul cerut
        """
        
        return self.repo_Eveniment.get_un_eveniment(id)
  
            
    def get_all(self):
        """Functia care returneaza o lista cu toate evenimentele
        """
        return self.repo_Eveniment.get_events()
    def sterge_event(self,id):
        """Functia de stergere eveniment repo_eveniment

        input:
            event (Eveniment): obiect clasa Eveniment pe care doresti sa-l elimini din repository
        """
        self.repo_Eveniment.sterge_eveniment(id)
    def modifica_event_data(self,id,new_date):
        """Functia de modificare data eveniment

        input:
            id (int): id-ul unui obiect clasa Eveniment din repo_evenimente
            new_data(obiect datetime): noua data de inceput a evenimentului
        """
        eveniment=self.repo_Eveniment.get_un_eveniment(id)
        self.repo_Eveniment.update_event_data(new_date,eveniment)
    def modifica_event_timp(self,id,new_timp):
        """Functia de modificare timp eveniment

        input:
            id (int): id-ul unui obiect clasa Eveniment din repo_evenimente
            new_timp(float): noua durata in ore a evenimentului
        """
        eveniment=self.repo_Eveniment.get_un_eveniment(id)
        self.repo_Eveniment.update_event_timp(new_timp,eveniment)
    def modifica_event_descriere(self,id,new_descriere):
        """Functia de modificare descriere eveniment

        input:
            id (int): id-ul unui obiect clasa Eveniment din repo_evenimente
            new_descriere(str): noua descriere a evenimentului
        """
        eveniment=self.repo_Eveniment.get_un_eveniment(id)
        self.repo_Eveniment.update_event_descriere(new_descriere,eveniment)
    def random_eveniment(self):
        """Functia de creare,validare si adaugare a unui eveniment generat aletoriu
        """
        seed=random.randint()
        lista=self.repo_Eveniment.get_lista_iduri()
        for i in range(max(lista)):
            if i not in lista:
                data_l=DATA_AZI()
                data_h=datetime.date(3000,12,31)
                eveniment=self.random.creaza_eveniment_random(seed,i,i,data_l,data_h)
                self.creaza_valideaza_adauga(eveniment)
                break
class Service_Persoana:
    def __init__(self,repo_persoana):
        self.repo_Persoana=repo_persoana
        self.validator=Validator()
        self.random=Randomiser()
    def cauta_persoana(self,id):
        """Functia de cautare persoana in obiectul de clasa Repository_persoana

        input:
            id (int): id-ul persoanei
        returns:
            persoana(Persoana): persoana cu id-ul cerut
        """
        return self.repo_Persoana.get_o_persoana(id)
    def creaza_persoane_random(self,cate):
        """Functia de generare persoane aleatorii

        input:
            cate (int): 

        Raises:
            GenerationError cu mesaj "Ceva nu a mers bine!!", daca nu s-a reusit generare niciunei persoane

        Returns:
            ok(int): numarul de persoane generate
        """
        ok=0
        for i in range(cate):
            seed=random.random()
            persoana=self.random.creaza_persoana_random(seed,1,1000)
            try:
                self.validator.valideaza_persoana(persoana)
                self.repo_Persoana.adauga_persoana(persoana)
                ok+=1
            except ValidationError:
                pass
            except RepositoryError:
                pass
        if ok==0:
            raise GenerationError("Ceva nu a mers bine!!!")
        return ok
    def creaza_valideaza_adauga(self,personID,nume,adresa):
        """Functia care creaza,valideaza si adauga un obiect de clasa Persoana in repository
        input:
            personID(int): id-ul unei persoane
            nume(string): numele unei persoane
            adresa(string): adresa unei persoane
        output:
            -
        Raises:
            Ridica erori tip RepositoryError sau ValidationError cu mesaje specifice
            "Id deja existent!\n" daca personId al obiectului person exista deja utilizat de alta Persoana in lista_persoane
            "ID numeric invalid!\n" , daca ID al obiectului din clasa Persoana <=0
            "Nume invalid!\n", daca numele este vid
            "Adresa invalida!\n", daca adresa este vida
        """
        person=Persoana(personID,nume,adresa)
        self.validator.valideaza_persoana(person)
        self.repo_Persoana.adauga_persoana(person)
    def get_all(self):
        """Functia care returneaza toate persoanele din Repository_persoana
        """
        return self.repo_Persoana.get_persoane()
    def sterge_persoana(self,id):
        """Functia de stergere persoana cu id specificat
        input:
            id(int): id-ul persoanei de clasa Persoana pe care vrei s-o stergi din obiectul clasa Repository_persoana
        """
        self.repo_Persoana.sterge_persoana(id)
    def modifica_nume(self,id,new_name):
        """Functia de modificare nume persoana

        input:
            id (int): id-ul persoanei pe care vrei sa o modifici
            new_name (str): noul nume al persoanei
        """
        persoana=self.repo_Persoana.get_o_persoana(id)
        self.repo_Persoana.update_nume_persoana(new_name,persoana)
    def modifica_adresa(self, id,new_adresa):
        """Functia de modificare adresa persoana

        input:
            id (int): id-ul persoanei pe care vrei sa o modifici
            new_adresa(str): noua adresa a persoanei
        """
        persoana=self.repo_Persoana.get_o_persoana(id)
        self.repo_Persoana.update_adresa_persoana(new_adresa,persoana)
    def random_persoana(self):
        """Functia de creare,validare si adaugare a unei persoana generata aletoriu
        """
        seed=random.randint()
        lista=self.repo_Persoana.get_lista_iduri()
        for i in range(max(lista)):
            if i not in lista:
                eveniment=self.random.creaza_persoana_random(seed,i,i)
                self.creaza_valideaza_adauga(Persoana)
                break
class Service_inscriere:
    def __init__(self,service_persoana,service_eveniment):
        self._service_eveniment=service_eveniment
        self._service_persoana=service_persoana
        self.__validator=Validator()
        self.__repo_inscriere=Repository_inscriere()
    def creaza_valideaza_adauga(self,id_pers,id_even):
        """Functia de creare,validare si adaugare inscriere noua

        input:
            id_pers (int):  id-ul unui obiect clasa Persoana
            id_even (int): id-ul unui obiect clasa Eveniment
        output:
            -
        Raises:
            Ridica erori de tip RepositoryError,ValidationError cu mesaje specifice:
                "Eveniment inexistent!!!\n", daca evenimentul cu id_even nu exista in repo_eveniment
                "Persoana inexistenta!!!\n", daca persoana cu id_pers nu exista in repo_persoana
        """
        persoana=self._service_persoana.cauta_persoana(id_pers)
        eveniment=self._service_eveniment.cauta_eveniment(id_even)
        inscriere=Inscriere(eveniment,persoana)
        self.__validator.valideaza_inscriere(inscriere)
        self.__repo_inscriere.adauga_inscriere(inscriere)
        self.__random=Randomiser()
    def creare_inscriere_random(self,cate):
        """Functia de generare inscrieri aleatorii

        input:
            cate (int): numarul maxim de inscrieri pe care doresti sa le generezi
        raises:
            Ridica erori tip GenerationError cu mesaj:
            "Ceva nu a mers bine!!", daca nu s-a reusit generare niciunei inscrieri
        """
        ok=0
        for i in range(cate):
            seed=random.random()
            random.seed(seed)
            try:
                eveniment=random.choice(self._service_eveniment.get_all())
                id_eveniment=eveniment.get_identificator()
                persoana=random.choice(self._service_persoana.get_all())
                id_persoana=persoana.get_identificator()
                try:
                    self.creaza_valideaza_adauga(id_persoana,id_eveniment)
                    ok+=1
                except RepositoryError:
                    pass
                except ValidationError:
                    pass
            except IndexError:  
                raise GenerationError("Ceva nu a mers bine!!")
        if ok==0:
            raise GenerationError("Ceva nu a mers bine!!")
        return ok
    def sterge_inscriere(self,id_eveniment,id_persoana):
        """Functia de stergere inscriere a unei persoane cu id_persoana de la evenimentul cu  id_eveniment

        input:
            id_eveniment (int): id-ul evenimentului
            id_persoana (int): id-ul persoanei
        output:
            -
        Raises:
            Ridica erori RepositoryError cu mesaje specifice:
                "Inscriere inexistenta!!!\n", daca obiectul inscriere cu id-urile specificate nu exista in repo_inscrieri
        """
        self.__repo_inscriere.sterge_inscriere(id_eveniment,id_persoana)
    def get_all(self):
        """Functia care returneaza toate inscrierile
        """
        solutie=[]
        inscrieri=self.__repo_inscriere.get_all()
        lista_persoane=self._service_persoana.get_all()
        lista_evenimente=self._service_eveniment.get_all()
        for inscriere in inscrieri:
            if inscriere.get_eveniment() not in lista_evenimente or inscriere.get_persoana() not in lista_persoane:
                inscriere.e_sters()
            else: solutie.append(inscriere)
        return solutie
    def evenimente_la_care_participa_persoana(self,id_person):
        """Functia care returneaza lista de evenimente la care participa o persoana

        input:
            id_person (int): id-ul persoanei
        """
        lista=self.__repo_inscriere.get_inscrieri_dupa_persoana(id_person)
        return lista
    def creare_listaDTO(self):
        """Functia care creaza lista de obiecte DTO pentru participarile unei persoane
        returns:
            lista(list): lista de obiecte tip Participari
        """
        lista_iduri_persoane=set(self.__repo_inscriere.get_id_list_persoana())
        lista_participari=[]
        for id in lista_iduri_persoane:
            nume=self._service_persoana.cauta_persoana(id).get_nume()
            cate=len(self.__repo_inscriere.get_inscrieri_dupa_persoana(id))
            participare=Participari(nume,cate)
            lista_participari.append(participare)
        return lista_participari
    def cele_mai_inscrise_pers(self):
        """Functia care returneaza cele mai inscrise persoane la evenimente
        """
        lista=self.creare_listaDTO()
        #lista.sort(key= lambda x : x.get_nr_participari(), reverse=True)
        #selection_sort(lista,key= lambda x : x.get_nr_participari(), reversed=True)
        shake_sort(lista,key= lambda x : x.get_nr_participari(), reversed=True)
        return lista
    
    def creare_lista_DTO20(self):
        """Functia care returneaza o lista de obiecte tip NumarParticipariDTO

        Returns:
            lista_nr_participari(list) : o lista de obiecte tip NumarParticipariDTO
        """
        lista_iduri_evenimente=self.__repo_inscriere.get_id_list_event()
        lista_nr_participari=[]
        for id in lista_iduri_evenimente:
            descriere=self._service_eveniment.cauta_eveniment(id).get_descriere()
            cati=len(self.__repo_inscriere.get_inscrieri_dupa_eveniment(id))
            participare=NumarParticipantiDTO(descriere,cati)
            lista_nr_participari.append(participare)
        return lista_nr_participari
    def top20(self):
        """Functia care returneaza o lista care contine descrierea si numarul de participanti a top 20% evenimente cu cei mai multi participanti
        """
        lista=self.creare_lista_DTO20()
        #lista.sort(key=lambda x: x.get_nr_participanti(),reverse=True)
        #selection_sort(lista,key=lambda x: x.get_nr_participanti(),reversed=True)
        shake_sort(lista,key=lambda x: x.get_nr_participanti(),reversed=True)
        return lista[:math.ceil(0.2*len(lista))]
    def top20_pe_dos(self):
        """Functia care returneaza top 20% persoane cu cele mai multe participari la evenimente 
        """
        lista=self.creare_lista_DTO20()
        lista.sort(key=lambda x: x.get_nr_participanti(),reverse=True)
        return lista[:math.ceil(0.2*len(lista))]
    def cele_mai_inscrise_pers_pe_dos(self):
        """Functia care returneaza persoanele cu cele mai multe persoane
        """
        lista=self.creare_lista_DTO20()
        lista.sort(key=lambda x: x.get_nr_participanti(),reverse=True)
        return lista
class Service_Inscriere_file(Service_inscriere,):
    def __init__(self, service_persoana, service_eveniment,filepath):
        Service_inscriere.__init__(self,service_persoana, service_eveniment)
        self.__filepath=filepath
        self.__repo_inscriere=File_Repository_inscriere(self.__filepath)
        self.__translate()
    def __translate(self):
        lista_noua=[]
        if self.__repo_inscriere.get_raw_list!=[]:
            for item in self.__repo_inscriere.get_raw_list():
                persoana=self._service_persoana.cauta_persoana(item.get_id_persoana())
                eveniment=self._service_eveniment.cauta_eveniment(item.get_id_eveniment())
                inscriere=Inscriere(eveniment,persoana)
                lista_noua.append(inscriere)
            self.__repo_inscriere.clear_list()
            for item in lista_noua:
                self.__repo_inscriere.add(item)