from validation.validator import *

class Repository_Persoana:
    def __init__(self):
        """Functia care initializeaza lista de Evenimente din repo
        """
        self._lista_persoane=[]
        
    def get_lista_iduri(self):
        """Functia care returneaza lista de id-uri persoane din obiectul de clasa Repository_Persoana
        """
        lista=[]
        persoane=self.get_persoane()
        for i in persoane:
            if i.e_sters()==False:
                lista.append(i.get_identificator())
        return lista
    
    def adauga_persoana(self,persoana=Persoana):
        """Functia de adaugare in lista de persoane a unui obiect Persoana clasa persoane
        input:
            Persoana(Persoana): o Persoana
        """
        self._lista_persoane.append(persoana)
    def get_o_persoana(self,id):
        """Functia care returneaza o persoana cu personId id din obiectul de clasa Repository_Persoana

        input:
            id (int): id-ul unei persoane

        Returns:
            persoana: persoana cu id-ul specificat
        """
        lista=self.get_persoane()
        for persoana in lista:
            if persoana.get_identificator()==id:
                return persoana
        raise RepositoryError("Persoana inexistenta!!!\n")
    def get_o_persoana_rec(self,id,unde):
        """Functia care returneaza o persoana cu personId id din obiectul de clasa Repository_Persoana recursiv
        """
        if unde==[]:
            raise RepositoryError("Persoana inexistenta!!!\n")
        if unde[0].get_identificator()==id:
            return unde[0]
        else:
            self.get_o_persoana_rec(id,unde[1:])
    def get_o_persoana_recursiv(self,id):
        self.get_o_persoana_rec(id,self._lista_persoane)
    def get_persoane(self):
        """Functie care returneaza obiectele Persoana din lista_persoane
        """
        not_removed=[]
        for persoana in self._lista_persoane:
            if persoana.e_sters()==False:
                not_removed.append(persoana)
        return not_removed
    def get_persoane_sters(self):
        """Functia care returneaza persoanele sterse
        """
        removed=[]
        for i in self._lista_persoane:
            if i.e_sters()==True:
                removed.append(i)
        return removed
    def get_persoane_full(self):
        return self._lista_persoane
    def adauga_persoana(self,person=Persoana):
        """Functia de adaugare Persoana in lista_persoane a obiectului clasa Repository_persoane

        input:
            person (_type_, optional): _description_. Defaults to Persoana.
        output:
            -   
        Raises:
            Ridica eroare tip RepositoryError cu mesajul:
            "Id deja existent!\n" daca personId al obiectului person exista deja utilizat de alta Persoana in lista_persoane
        """
        id_list=self.get_lista_iduri()
        id=person.get_identificator()
        if id in id_list:
            raise RepositoryError("Id deja existent!\n")
        else:
            self._lista_persoane.append(person)
    def sterge_persoana(self,id):
        """Functia de stergere Persoana din obiectul de clasa Repository_Persoana
        input:
            id: id-ul unui obiect clasa Persoana
        output:
            -
        raises:
            Ridica eroare tip RepositoryError cu mesajul:
            "Nu exista ce vrei sa elimini!\n" daca nu se gaseste obiectul person in lista_persoane a obiectului tip Repository_Persoana
        """
        
        lista=self.get_lista_iduri()
        if id not in lista:
            raise RepositoryError("Nu exista ce vrei sa elimini!\n")
        else:
            self.get_o_persoana(id).sters()
            
    def update_nume_persoana(self,new_name,person=Persoana):
        """Functia de modificare nume Persoana din lista_persoane a obiectului curent

        input:
            new_name(string): noul nume al persoanei
            person(obiect clasa Persoana): _description_. Defaults to Persoana.
        output:
            -  
        raises:
            Ridica eroare tip RepositoryError cu mesaj:
            "Noul nume invalid!\n" daca noul nume este vid
        """
        if new_name=="":
            raise RepositoryError("Noul nume invalid!\n")
        else:
            person.set_nume(new_name)
    def update_adresa_persoana(self,new_adress,person=Persoana):
        """Functia de modificare adresa unei persoane din lista_persoane a obiectului curent

        input:
            new_adress(string): noua adresa a persoanei
            person(obiect clasa Persoana): _description_. Defaults to Persoana.
        output:
            -  
        raises:
            Ridica eroare tip RepositoryError cu mesaj:
            "Noua adresa invalida!\n" daca noua adresa este string vid
        """
        if new_adress=="":
            raise RepositoryError("Noua adresa invalida!\n")
        else:
            person.set_adresa(new_adress)
class File_Repository_Persoana(Repository_Persoana):
    def __init__(self,filepath):
        self.__filepath=filepath
        self._lista_persoane=self.__citeste_fisier()
    def __citeste_fisier(self):
        try:
            f= open(self.__filepath,'r')
        except IOError:
            return []
        sol=[]
        lines=f.readlines()
        for line in lines:
            line=line.strip()
            if line!="":
                args=line.split(",")
                id=int(args[0])
                nume=args[1]
                adresa=args[2]
                persoana=Persoana(id,nume,adresa)
                sol.append(persoana)
        return sol
    def __scrie_fisier(self):
        f = open(self.__filepath,'w')
        for item in self._lista_persoane:
            if item.e_sters()==False:
                f.write(f"{item.get_identificator()},{item.get_nume()},{item.get_adresa()}\n")
        f.close()
    def sterge_persoana(self, id):
        
        Repository_Persoana.sterge_persoana(self,id)
        self.__scrie_fisier()
    def adauga_persoana(self, person=Persoana):
        Repository_Persoana.adauga_persoana(self,person)
        self.__scrie_fisier()
    def get_lista_iduri(self):
        return super().get_lista_iduri()
    def update_adresa_persoana(self, new_adress, person=Persoana):
        Repository_Persoana.update_adresa_persoana(self,new_adress, person)
        self.__scrie_fisier()
    def update_nume_persoana(self, new_name, person=Persoana):
        Repository_Persoana.update_nume_persoana(self,new_name, person)
        self.__scrie_fisier()