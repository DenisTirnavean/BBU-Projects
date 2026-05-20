from repository.repo_event import *
from repository.repo_person import *

class Repository_inscriere:
    def __init__(self):
        self._lista_inscrieri=[]
    def get_lista_inscrieri(self):
        solutie=[]
        for inscriere in self._lista_inscrieri:
            if inscriere.e_sters()==False:
                solutie.append(inscriere)
        return solutie
    def adauga_inscriere(self,inscriere):
        """Functia de adaugare inscriere in Repository_inscriere

        input:
            inscriere(Inscriere): obiect clasa inscriere
        output:
            -
        raises:
            Ridica eroare tip RepositoryError cu mesaj:
               "Inscriere deja existenta!!\n"
        """
        for inscrieri in self._lista_inscrieri:
            if inscriere==inscrieri:
                raise RepositoryError("Inscriere deja existenta!!\n")
        self._lista_inscrieri.append(inscriere)
    def get_id_list_event(self):
        """Functia care returneaza lista de id-uri inscrieri dupa eveniment
        """
        listaid=[]
        lista_inscriere=self.get_lista_inscrieri()
        for inscrieri in lista_inscriere:
            if inscrieri.get_eveniment().get_identificator() not in listaid:
                listaid.append(inscrieri.get_eveniment().get_identificator())
        return listaid
    def get_id_list_persoana(self):
        """Functia care returneaza lista de id-uri de persoana din Repository_inscriere
        """
        listaid=[]
        lista_inscriere=self.get_lista_inscrieri()
        for inscrieri in lista_inscriere:
            if inscrieri.get_persoana().get_identificator() not in listaid:
                listaid.append(inscrieri.get_persoana().get_identificator())
        return listaid
    def sterge_inscriere(self,id_event,id_pers):
        """Functia de stergere inscriere din lista de inscrieri

        input:
            id_inscriere (int): id-ul  inscrierii pe care doresti sa o elimini
        output: 
            -
        Raises:
             Ridica erori tip RepositoryError cu mesaj:
                "Inscriere inexistenta!!!\n", daca obiectul inscriere cu id-urile specificate nu exista in lista de inscrieri
        """
        inscriere=self.get_inscriere(id_pers,id_event)
        inscriere.sters()
    def get_all(self):
        """Functia care returneaza toate inscrierile nesterse
        """
        return self._lista_inscrieri
    def get_inscrieri_dupa_eveniment(self,id_event):
        """Functia care returneaza toate inscrierile care au un anumit eveniment

        Args:
            id_event (int): id-ul evenimentului cerut

        Returns:
            solutie(list): lista tuturor inscrierilor la evenimentul dat
        """
        solutie=[]
        lista_inscrieri=self.get_lista_inscrieri()
        for inscriere in lista_inscrieri:
            if inscriere.get_eveniment().get_identificator()==id_event:
                solutie.append(inscriere)
        return solutie
    def get_inscrieri_dupa_persoana(self,id_person):
        """Functia care returneaza toate inscrierile unei anumite persoane

        Args:
            id_person(int): id-ul persoanei cerute

        Returns:
            solutie(list): lista tuturor inscrierilor din care face parte respectiva persoana
        """
        solutie=[]
        lista_inscrieri=self.get_lista_inscrieri()
        for inscriere in lista_inscrieri:
            if inscriere.get_persoana().get_identificator()==id_person:
                solutie.append(inscriere)
        return solutie
    def get_inscriere(self,id_person,id_eveniment):
        """Functia care returneaza inscrierea cu persoana cu id_person si cu evenimentul cu id_eveniment

        input:
            id_person (int): id-ul persoanei
            id_eveniment (int): id-ul evenimentului
        output:
            -
        Raises:
            Ridica eroare tip RepositoryError cu mesaj:
            "Inscriere inexistenta!!!\n", daca nu exista in obiectul tip Repository_inscriere o inscriere cu argumentele specificate
        """
        ok=0
        for inscriere in self.get_lista_inscrieri():
            if inscriere.get_eveniment().get_identificator()==id_eveniment and inscriere.get_persoana().get_identificator()==id_person:
                ok=1
                return inscriere
        if ok==0: raise RepositoryError("Inscriere inexistenta!!!\n")
class File_Repository_inscriere(Repository_inscriere):
    def __init__(self,filepath):
        """Dupa initializare se recomanda folosire functiei translate
        """
        self.__filepath=filepath
        self._lista_inscrieri=self.__read_file()

    def __read_file(self):
        solution=[]
        try:
            f = open(self.__filepath,'r')
        except IOError:
            raise RepositoryError("Fisier inexistent!!!")
        lines=f.readlines()
        for line in lines:
            line=line.strip()
            if line!="":
                args=line.split(',')
                id_persoana=int(args[0])
                id_eveniment=int(args[1])
                inscriere=InscriereFile(id_persoana,id_eveniment)
                solution.append(inscriere)
        f.close()
        return solution
            
    def __write_into_file(self):
        try:
            f = open(self.__filepath,'w')
        except IOError:
            raise RepositoryError("Fisier inexistent!!!")
        for item in self._lista_inscrieri:
            f.write(f"{item.get_persoana().get_identificator()},{item.get_eveniment().get_identificator()}\n")
        f.close()
    def get_raw_list(self):
        return self._lista_inscrieri
    def clear_list(self):
        self._lista_inscrieri.clear()
    def __append_to_file(self,inscriere):
        try:
            f = open(self.__filepath,'a')
        except IOError:
            raise RepositoryError("Fisier inexistent!!!")
        f.write(f"{inscriere.get_persoana().get_identificator()},{inscriere.get_eveniment().get_identificator()}\n")
        f.close()
    def add(self,inscriere):
        Repository_inscriere.adauga_inscriere(self,inscriere)
    def adauga_inscriere(self, inscriere):
        Repository_inscriere.adauga_inscriere(self,inscriere)
        self.__append_to_file(inscriere)
    def sterge_inscriere(self, id_event, id_pers):
        Repository_inscriere.sterge_inscriere(self,id_event,id_pers)
        self.__write_into_file()