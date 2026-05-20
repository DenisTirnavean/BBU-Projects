from validation.validator import *

class Repository_Eveniment():
    def __init__(self):
        self._lista_evenimente=[]
    def get_lista_iduri(self):
        """Functia care returneaza lista de id-uri Evenimente din obiectul de clasa Repository_Eveniment
        """
        lista=[]
        evenimente=self.get_events()
        for i in evenimente:
            lista.append(i.get_identificator())
        return lista
    def get_un_eveniment(self,eventID):
        """Functia care returneaza un Eveniment cu ID eventID
        input:
            eventID(int): un id
        returns:
            eveniment(Eveniment): obiect clasa Eveniment cu id specificat
        raises:
            Ridica eroare tip RepositoryError cu mesaj:
                "Eveniment inexistent!!!\n"
        """
        lista=self.get_events()
        for eveniment in lista:
            if eveniment.get_identificator()==eventID:
                return eveniment
        raise RepositoryError("Eveniment inexistent!!!\n") 
    def get_un_eveniment_rec(self,eventId,unde):
        if unde==[]:
            raise RepositoryError("Eveniment inexistenta!!!\n")
        if unde[0].get_identificator()==id:
            return unde[0]
        else:
            self.get_un_eveniment_rec(id,unde[1:])
    def get_un_eveniment_recursiv(self,id):
        """Functia care returneaza un Eveniment cu ID eventID recursiv"""
        self.get_un_eveniment_rec(id,self._lista_evenimente)
    def adauga_eveniment(self,event=Eveniment):
        """Functia de adaugare Eveniment in lista de Evenimente
        input:
            event: obiect clasa Eveniment
        output:
            -
        raises:
            Ridica eroare tip RepositoryError cu mesajul:
            "Id deja existent!\n", daca id-ul obiectul event este deja folosit in lista de Evenimente a obiectului curent Repository_Eveniment
        """
        id_list=self.get_lista_iduri()
        id=event.get_identificator()
        if id in id_list:
            raise RepositoryError("Id deja existent!\n")
        else:
            self._lista_evenimente.append(event)
    def get_events(self):
        """Functia care returneaza lista_Evenimente a obiectului curent din clasa Repository_Eveniment
        """
        rezultat=[]
        for i in self._lista_evenimente:
            if i.e_sters()==False:
                rezultat.append(i)
        return rezultat
    def sterge_eveniment(self,id):
        """Functia de stergere Eveniment din obiectul de clasa Repository_Eveniment
        input:
            id: id-ul unui obiect clasa Eveniment
        output:
            -
        raises:
            Ridica eroare tip RepositoryError cu mesajul:
            "Nu exista ce vrei sa elimini!\n" daca nu se gaseste obiectul event in lista_Evenimente a obiectului tip Repository_Eveniment
        """
        
        lista=self.get_lista_iduri()
        if id not in lista:
            raise RepositoryError("Nu exista ce vrei sa elimini!\n")
        else:
            self.get_un_eveniment(id).sters()
    def update_event_data(self,new_date,event=Eveniment):
        """Functia de modificare data Eveniment din lista_Evenimente a obiectului curent

        input:
            new_date(data calendaristica): noua data a Evenimentului
            event (obiect clasa Eveniment): _description_. Defaults to Eveniment.
        output:
            -  
        raises:
            Ridica eroare tip RepositoryError cu mesaj:
            "Noua data invalida!\n" daca noua data este in trecut
        """
        if new_date<DATA_AZI():
            raise RepositoryError("Noua data invalida!\n")
        else:
            event.set_data(new_date)
    def update_event_timp(self,new_timp, event=Eveniment):
        """Functia de modificare data Eveniment din lista_Evenimente a obiectului curent

        input:
            new_timp(float): noua durata a Evenimentului
            event (_type_, optional): _description_. Defaults to Eveniment.
        output:
            -
        raises:
            Ridica eroare tip RepositoryError cu mesaj:
                "Timp nou invalid!\n" daca new_timp este <=0
        """
        if new_timp<=0:
            raise RepositoryError("Timp nou invalid!\n")
        else:
            event.set_timp(new_timp)
    def update_event_descriere(self,new_descriere,event):
        """Functia de modificare descriere Eveniment din lista_Evenimente a obiectului curent

        input:
            new_descriere(string): noua descriere a Evenimentului
            event (_type_, optional): _description_. Defaults to Eveniment.
        Raises:
            Ridica eroare tip RepositoryError cu mesaj:
            "Descriere vida!\n" daca new_descriere este vida
        """
        if new_descriere=="":
            raise RepositoryError("Descriere vida!\n")
        else:
            event.set_descriere(new_descriere)
    def __len__(self):
        return len(self.get_events())
class File_Repository_Eveniment(Repository_Eveniment):
    def __init__(self,cale_catre_fisier):
        self.__cale_catre_fisier = cale_catre_fisier
        self._lista_evenimente=self.__citeste_evenimente_din_fisier()
    def __citeste_evenimente_din_fisier(self):
        """Functia de citire evenimente din fisier
        """
        with open(self.__cale_catre_fisier,'r') as f:
            solution=[]
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    informatie = line.split(',')
                    id_eveniment = int(informatie[0])
                    timp=float(informatie[2])
                    descriere=str(informatie[3])
                    data=informatie[1].split('-')
                    data_eveniment=datetime.date(int(data[0]),int(data[1]), int(data[2]))
                    eveniment=Eveniment(id_eveniment,data_eveniment,timp,descriere)
                    solution.append(eveniment)
            return solution
    def __append_eveniment_in_fisier(self,eveniment):
        """Functia de adaugare a unui eveniment in fisier
        """

        with open(self.__cale_catre_fisier,'a') as f:
            f.write(f"{eveniment.get_identificator()},{eveniment.get_data()},{eveniment.get_timp()},{eveniment.get_descriere()}\n")
    def __scrie_evenimente_in_fisier(self):
        """Functia de scriere evenimente in fisier
        """
        with open(self.__cale_catre_fisier,'w') as f:
            for eveniment in self._lista_evenimente:
                if eveniment.e_sters()==False:
                    f.write(f"{eveniment.get_identificator()},{eveniment.get_data()},{eveniment.get_timp()},{eveniment.get_descriere()}\n")
    def adauga_eveniment(self, event=Eveniment):
        """Functia de adaugare eveniment in lista de evenimente
        input:
            event: obiect clasa Eveniment
        output:
            -
        raises:
            Ridica eroare tip RepositoryError cu mesajul:
            "Id deja existent!\n", daca id-ul obiectul event este deja folosit in lista de Evenimente a obiectului curent Repository_Eveniment
        """
        Repository_Eveniment.adauga_eveniment(self,event)
        self.__append_eveniment_in_fisier(event)
    def sterge_eveniment(self, id):
        """Functia de stergere eveniment din lista de evenimente
        input:
            id: id-ul unui obiect clasa Eveniment
        output:
            -
        raises:
            Ridica eroare tip RepositoryError cu mesajul:
            "Nu exista ce vrei sa elimini!\n" daca nu se gaseste obiectul event in lista_Evenimente a obiectului tip Repository_Eveniment
        """
        Repository_Eveniment.sterge_eveniment(self,id)
        self.__scrie_evenimente_in_fisier()
    def get_un_eveniment(self, eventID):
        """Functia care returneaza un Eveniment cu ID eventID
        input:
            eventID(int): un id
        returns:
            eveniment(Eveniment): obiect clasa Eveniment cu id specificat
        raises:
            Ridica eroare tip RepositoryError cu mesaj:
                "Eveniment inexistent!!!\n"
        """

        return Repository_Eveniment.get_un_eveniment(self,eventID)
    
    def get_lista_iduri(self):
        """Functia care returneaza lista de id-uri Evenimente
        """

        return Repository_Eveniment.get_lista_iduri(self)
    def get_events(self):
        return Repository_Eveniment.get_events(self)
    def update_event_data(self, new_date, event=Eveniment):

        Repository_Eveniment.update_event_data(self,new_date,event)
        self.__scrie_evenimente_in_fisier()
    def update_event_descriere(self, new_descriere, event):
  
        Repository_Eveniment.update_event_descriere(self,new_descriere, event)
        self.__scrie_evenimente_in_fisier()
    def update_event_timp(self, new_timp, event=Eveniment):
      
        Repository_Eveniment.update_event_timp(self,new_timp, event)
        self.__scrie_evenimente_in_fisier()
    def __len__(self):
       
        return Repository_Eveniment.__len__(self)