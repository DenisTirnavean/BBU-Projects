from service.service_vm import Service

class Consola:
    def __init__(self,filepath):
        self.__service=Service(filepath)
        self.__commands={
            "cerinta_1":self.__ui_cpu_interval,
            "cerinta_2":self.__ui_pret_mediu,
            "afisare":self.__afisare
        }
    def __print_cerinta_1(self,lista):
        print("Masinile virtuale cu specificatiile cerute sunt:")
        for item in lista:
            print(f"{item.get_nume()}, {item.get_disk()}")
    def __print_cerinta_2(self,lista):
        print("Preturile medii pentru utilizarea diskurilor sunt:")
        for item in lista:
            print(f"{item.get_disk()}:{item.get_price()}$")
    def __is_invalid_interval(self,low,high):
        if low>=high:
            return True
        return False
    def __ui_cpu_interval(self):
        """Functia care afiseaza numele si tipul disk-ul masinilor virtuale cu capacitatea cpu intr-un interval citit de la tastatura
        """
        try:
            cpu_low=float(input("Margine inferioara:"))
            cpu_high=float(input("Margine superioara"))
            if self.__is_invalid_interval(cpu_low,cpu_high):
                print("interval invalid")
                return
            lista=self.__service.cpu_interval(cpu_low,cpu_high)
            if lista==[]:
                print("Nu exista VM care sa respecte specificatiile")
                return
            else:
                self.__print_cerinta_1(lista)
        except ValueError:
            print("Valori numerice invalide!!")
            return
    def __ui_pret_mediu(self):
        try:
            nr_ore=float(input("Da-ti numarul de ore:"))
            lista=self.__service.pret_mediu(nr_ore)
            if lista==[]:
                print("Lista goala!")
                return
            else:
                self.__print_cerinta_2(lista)
        except ValueError:
            print("Valoare numerica invalida")
            return
    def __afisare(self):
        """Functia de tiparire a continutului fisierului
        """
        list=self.__service.get_all()
        if list==[]:
            print("lista goala!!!")
            return
        for item in list:
            print(item)
    def run(self):
        """Functia care porneste aplicatia
        """
        while True:
            cmd=input("Da-ti comanda( cerinta_1 / cerinta_2 / afisare / x )")
            if cmd=="x":
                break
            if cmd not in self.__commands:
                print("Comanda invalida!")
            else:
                self.__commands[cmd]()
        print("Good bye!")