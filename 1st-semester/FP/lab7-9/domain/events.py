import datetime
import random
import math
from string import digits,ascii_lowercase
def DATA_AZI():
    """Functie care returneaza data de astazi

    Returns:
        azi(data calendaristica): data calendaristica din clasa datetime.date() de forma YYYY-MM-DD
    """
    azi=datetime.datetime.today()
    astazi=azi.date()
    return astazi
class Identificabil:
    """Clasa obiectelor identificabile dupa un numar intreg unic numit identificator(id)
    """
    def __init__(self,identificator):
        self.__identificator=identificator
    def get_identificator(self):
        """Functia care returneaza id-ul unui obiect

        Returns:
            identificator(int): id, numar intreg unic indentificabil
        """
        return self.__identificator
class Eliminabil:
    """Clasa obiectelor eliminabile
    """
    def __init__(self):
        self.__e_sters=False
    def sters(self):
        """Functia de marcare obiect ca fiind sters
        """
        self.__e_sters=True
    def e_sters(self):
        """Functia care returneaza statusul unui obiect

        Returns:
            True: obiectul a fost sters
            False: obiectul nu a fost sters
        """
        return self.__e_sters  
class RepositoryError(Exception):
    """Erori de repository
    """
class GenerationError(Exception):
    pass
class Eveniment(Identificabil,Eliminabil):
    def __init__(self,ID,data,timp,descriere):
        """Functia constructor de Evenimente cu ID,data, timp, descriere
            Un Eveniment poate avea mai multe persoane din clasa Persoana
        input:
            ID (int): id-ul unic al eveminentului
            data (data calendaristica): data desfasurarii Evenimentului
            timp (float): durata in ore a Evenimentului
            descriere (string): descrierea succinta a desfasurarii Evenimentului
        """
        Identificabil.__init__(self,ID)
        Eliminabil.__init__(self)
        self.__data=data
        self.__descriere=descriere
        self.__timp=timp

    def get_data(self):
        """Functia getter de data
        Returneaza data unui Eveniment
        Returns:
            data: data desfasurarii Evenimentului
        """
        return self.__data
    def get_timp(self):
        """Functia getter de timp

        Returns:
            timp: durata desfasurarii Evenimentului
        """
        return self.__timp
    def get_descriere(self):
        """Functia getter de descriere

        Returns:
            descriere: descrierea Evenimentului
        """
        return self.__descriere

    def set_data(self,new_date):
        """Functia setter pentru data
        """
        self.__data=new_date
    def set_timp(self,new_time):
        """Functia setter pentru timp
        """
        self.__timp=new_time
    def set_descriere(self,new_description):
        """Functia setter pentru descriere
        """
        self.__descriere=new_description
    
    def __eq__(self, other):
        return self.get_identificator()==other.get_identificator()
    def __str__(self):
        return f"[{self.get_identificator()}]   Data:{self.__data}  Timp:{self.__timp} ore  Descriere:<{self.__descriere}>"
class Persoana(Identificabil,Eliminabil):
    """Clasa Persoana care poseda un personID, nume si adresa 
    """
    def __init__(self,personID,nume,adresa):
        """Functia constructor de persoane cu id personID, nume nume si adresa adresa

        input:
            personID (int): id-ul unic al persoanei
            nume (string): numele persoanei
            adresa (string): adresa persoanei
        """
        Identificabil.__init__(self,personID)
        Eliminabil.__init__(self)
        self.__nume=nume
        self.__adresa=adresa

    def get_nume(self):
        """Functia getter de nume
        Returneaza numele unei persoane
        Returns:
            nume: numele persoanei
        """
        return self.__nume
    def get_adresa(self):
        """Functia getter de adresa

        Returns:
            adresa: adresa unei persoane
        """
        return self.__adresa

    def set_nume(self,new_name):
        """Functia setter pentru nume
        """
        self.__nume=new_name
    def set_adresa(self,new_adress):
        """Functia setter pentru adresa
        """
        self.__adresa=new_adress
    def __eq__(self, other):
        return self.get_identificator()==other.get_identificator()
    def __str__(self):
        return f"[{self.get_identificator()}]   Nume:{self.__nume}  Adresa:{self.__adresa}"
