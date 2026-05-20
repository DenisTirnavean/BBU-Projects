class Masina:
    def __init__(self,id,nume,cpu_capacity,disk,price):
        """Functia constructor masini virtuale

        Args:
            id (int): idul masinii
            nume(str): numele masinii
            cpu_capacity (): _description_
            disk (_type_): _description_
            price (_type_): _description_
        """
        self.__id=id
        self.__nume=nume
        self.__cpu=cpu_capacity
        self.__disk=disk
        self.__price=price
    def get_id(self):
        return self.__id
    def get_nume(self):
        return self.__nume
    def get_cpu(self):
        return self.__cpu
    def get_disk(self):
        return self.__disk
    def get_price(self):
        return self.__price
    def __str__(self):
        return f"<{self.get_id()}>,{self.get_nume()},{self.get_cpu()}Gh,{self.get_disk()},{self.get_price()}$"