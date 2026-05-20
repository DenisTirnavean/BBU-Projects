from domain.virtual_machines import Masina

class FileRepository:
    def __init__(self,filepath):
        self.__filepath=filepath
        self.__repo=self.__read_file()
    def __read_file(self):
        """Functia de citire din fisier
        """
        f = open(self.__filepath,'r')
        solution=[]
        lines= f.readlines()
        for line in lines:
            line=line.strip()
            args=line.split(",")
            if line!="":
                id=int(args[0])
                nume=args[1]
                cpu=float(args[2])
                disk=args[3]
                price=float(args[4])
                masina=Masina(id,nume,cpu,disk,price)
                solution.append(masina)
        return solution
    def get_all(self):
        """Functia care returneaza lista de masini virtuale din repository-ul de masini virtuale

        Returns:
            repo(list): lista de masini virtuale
        """
        return self.__repo