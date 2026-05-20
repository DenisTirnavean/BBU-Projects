from domain.events import *

class Inscriere(Eliminabil):
    def __init__(self,eveniment,persoana):
        self.__eveniment=eveniment
        self.__persoana=persoana
        Eliminabil.__init__(self)
    def get_eveniment(self):
        return self.__eveniment
    def get_persoana(self):
        return self.__persoana
    def __str__(self):
        return f"Persoana [{self.__persoana.get_nume()}] participa la evenimentul [{self.__eveniment.get_descriere()}]"
    def __eq__(self,other):
        return self.get_eveniment()==other.get_eveniment() and self.get_persoana()==other.get_persoana()
#DTO pentru informatiile stocate in fisier
class InscriereFile:
    def __init__(self,id_persoana,id_eveniment):
        self.__id_eveniment=id_eveniment
        self.__id_persoana=id_persoana
    def get_id_eveniment(self):
        return self.__id_eveniment
    def get_id_persoana(self):
        return self.__id_persoana
#pentru top20
class NumarParticipantiDTO:
    def __init__(self,descriere,nr_participanti):
        self.__descriere=descriere
        self.__nr_participanti=nr_participanti
    def get_descriere(self):
        return self.__descriere
    def get_nr_participanti(self):
        return self.__nr_participanti


#pentru persoanele care participa la cele mai multe evenimente
class Participari:
    def __init__(self,nume_persoana,nr_participari):
        self.__nume_persoana=nume_persoana
        self.__participari=nr_participari
    def get_nume(self):
        return self.__nume_persoana
    def get_nr_participari(self):
        return self.__participari