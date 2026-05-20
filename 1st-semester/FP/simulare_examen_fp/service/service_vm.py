from repository.repo_vm import FileRepository
from domain.dtos import MasinaDTO,DiskAveragePrice


class Service:
    def __init__(self,filepath):
        self.__repo=FileRepository(filepath)
    def get_all(self):
        """Functia care retuneaza continutul repository-ului de masini virtuale al service-ului curent
        """
        return self.__repo.get_all()
    def cpu_interval(self,cpu_low,cpu_high):
        """Functia care returneaza un obiect DTO continand numele si tipul de disk pentru toate masinile cu capacitate cpu intr-un interval dat

        Args:
            cpu_low (float): partea inferioara a intervalului
            cpu_high (float): partea superioara a intervalului
        returns:
            lista(list): lista de obiecte de transfer de date cu numele si tipul diskului
        """
        lista=self.__repo.get_all()
        solution=[]
        for item in lista:
            cpu_type=item.get_cpu()
            if cpu_type <cpu_high and cpu_type>cpu_low :
                nume=item.get_nume()
                disk=item.get_disk()
                masina=MasinaDTO(nume,disk)
                solution.append(masina)
        return solution
    def __get_lista_diskuri(self):
        """Functia care returneaza lista de tipuri de diskuri fara duplicate
        returns:
        lista(list): lista de diskuri
        """
        lista_obiecte=self.get_all()
        lista=[]
        for item in lista_obiecte:
            disk=item.get_disk()
            lista.append(disk)
        lista=set(lista)
        lista=list(lista)
        return lista
    def creareDTOs(self):
        """Functia de creare obiecte DTO de tip DiskAveragePrice
        """
        lista=self.__get_lista_diskuri()
        lista_obiecte=self.get_all()
        lista_dtos=[]
        for disk in lista:
            suma=0
            cate=0
            for item in lista_obiecte:
                if item.get_disk()==disk:
                    suma+=item.get_price()
                    cate+=1
            pret_mediu=suma/cate
            obiect_DTO=DiskAveragePrice(disk,pret_mediu)
            lista_dtos.append(obiect_DTO)
        return lista_dtos
    def pret_mediu(self,nr_ore):
        """Functia care returneaza o lista de obiecte de transfer de date continand tipul de disk si pretul mediu de utillizare pentru un anumit numar de ore

        Args:
            nr_ore (float): numarul de ore

        Returns:
            lista(list): lista cu tipul fiecarui disk si pretul mediu
        """
        lista=self.creareDTOs()
        for item in lista:
            pret_pe_ora=item.get_price()*nr_ore
            item.set_price(pret_pe_ora)
        return lista