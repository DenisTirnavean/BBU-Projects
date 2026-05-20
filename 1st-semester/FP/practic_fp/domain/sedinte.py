import datetime
from domain.erori import *
def data_curenta():
    return datetime.date.today()
def get_an(data):
    data
class Sedinta:
    """Clasa de obiecte sedinta cu data dd.mm, ora hh:mm, subiect (str), tip(extraordinara/normal)  
    """
    def __init__(self,data,ora,subiect,tip):
        self.__data=data
        self.__ora=ora
        self.__subiect=subiect
        self.__tip=tip
    def get_data(self):
        return self.__data
    def get_ora(self):
        return self.__ora
    def get_subiect(self):
        return self.__subiect
    def get_tip(self):
        return self.__tip
    def __str__(self):
        return f"{self.get_data().day}.{self.get_data().month},{self.get_ora().hour}:{self.get_ora().minute},{self.get_subiect()},{self.get_tip()}"
    def __eq__(self, other):
        return self.get_subiect()==other.get_subiect() and self.get_tip()==other.get_tip()