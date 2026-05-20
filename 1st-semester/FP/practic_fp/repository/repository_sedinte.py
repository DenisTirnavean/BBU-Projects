from domain.sedinte import *

class Repository:
    def __init__(self,filepath):
        self.__repo=[]
        self.__filepath=filepath
        self.__repo=self.__load_from_file()
    def __load_from_file(self):
        """Functia incarca inregistrarile din fisier in repository
        raises:
            IOError daca nu s-a putut realiza deschiderea fisierului
        """
        solutie=[]
        f = open(self.__filepath,'r')
        lines=f.readlines()
        for line in lines:
            line=line.strip()
            if line!=[]:
                args=line.split(',')
                data=args[0]
                ora=args[1]
                subiect=args[2]
                tip=args[3]
                data_desfasurata=data.split(".")
                zi=int(data_desfasurata[0])
                luna=int(data_desfasurata[1])
                an_curent=datetime.datetime.today()
                an_curent=an_curent.year
                data=datetime.date(an_curent,luna,zi)
                ora=ora.split(':')
                hour=int(ora[0])
                minut=int(ora[1])
                ora=datetime.time(hour,minut)
                sedinta=Sedinta(data,ora,subiect,tip)
                solutie.append(sedinta)
        f.close()
        return solutie
    def __write_into_file(self):
        """Functia de actualizare inregistrari din fisier
        raises:
            IOError daca nu s-a putut realiza deschiderea fisierului
        """
        f = open(self.__filepath,'w')
        f.write("")
        for item in self.__repo:
            f.write(f"{item.get_data().day}.{item.get_data().month},{item.get_ora().hour}:{item.get_ora().minute},{item.get_subiect()},{item.get_tip()}\n")
        f.close()
    def adauga_sedinta(self,new_sedinta):
        """Functia adauga o noua sedinta in lista de sedinte si actualizeaza continutul fisierului

        Args:
            new_sedinta (Sedinta): o noua sedinta
        returns: -
        raises: 
            RepositoryError cu mesaj:
                "Sedinta invalida\n", daca mai exista o sedinta cu acelasi subiect si acelasi tip
        """
        lista=self.get_all()
        for item in lista:
            if item==new_sedinta:
                raise RepositoryError("Sedinta invalida\n")
        self.__repo.append(new_sedinta)
        self.__write_into_file()
    def get_all(self):
        return self.__repo