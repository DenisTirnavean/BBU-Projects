class MasinaDTO:
    """Clasa de transfer de date pentru masina
    """
    def __init__(self,nume,disk):
        """Constructor obiect DTO

        Args:
            nume (str): numele masinii
            disk (str): tipul de disk
        """
        self.__nume=nume
        self.__disk=disk
    def get_nume(self):
        return self.__nume
    def get_disk(self):
        return self.__disk
class DiskAveragePrice:
    """Clasa de transfer de informatie pentru pretul mediu al unui disk
    """
    def __init__(self,disk,price):
        """Functia constructor pt obiect DTO

        Args:
            disk (str): tipul de disk
            average_price (float): pretul mediu
        """
        self.__disk=disk
        self.__price=price
    def get_disk(self):
        return self.__disk
    def get_price(self):
        return self.__price
    def set_price(self,new_price):
        self.__price=new_price