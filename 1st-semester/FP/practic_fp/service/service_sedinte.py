from domain.validator import *
from repository.repository_sedinte import Repository

class Service:
    """Clasa GRASP controller
    """
    def __init__(self,filepath):
        self.__repo=Repository(filepath)
        self.__validator=Validator()
    def get_all(self):
        return self.__repo.get_all()
    def creaza_valideaza_adauga(self,data,ora,subiect,tip):
        """Functia care creaza, valideaza si adauga in lista de sedinte o noua sedinta cu data,ora,subiect,tip

        Args:
            data (datetime.date): data sedintei
            ora (datetime.time): ora sedintei
            subiect (str): string nevid
            tip (str): "normal" sau "extraordinar"
        output: -
        raises: RepositoryError sau ValidationError cu mesaje specifice:
            RepositoryError:"Sedinta invalida\n", daca mai exista o sedinta cu acelasi subiect si acelasi tip
            ValidationError:
                "Data invalida\n", daca data sedintei se  afla in trecut
                "Tip invalid\n",daca tipul nu este stringul "normal" sau "extraordinar"
                "Subiect invalid\n", daca subiectul este sir vid
        """
        sedinta=Sedinta(data,ora,subiect,tip)
        self.__validator.valideaza_sedinta(sedinta)
        self.__repo.adauga_sedinta(sedinta)
    def sedinte_urmatoare(self):
        """Functia care gaseste sedintele din ziua urmatoare

        Returns:
            list: lista cu sedintele din ziua urmatoare
        """
        solutie=[]
        lista=self.get_all()
        data_curenta=datetime.date.today()
        for item in lista:
            if item.get_data()==data_curenta+datetime.timedelta(days=1):
                solutie.append(item)
        return solutie
    def setare_data(self,data):
        """Functia care filtreaza sedintele din lista de sedinte

        Args:
            data (datetime): o data
        
        returns:
        list: lista cu sedintele care vor avea loc in urmatoarele 3 zile de la data specificata
        []: daca nu exista sedinte care respecta calitatea enuntata
        """
        solutie=[]
        for item in self.get_all():
            if (item.get_data()-data).days<=3:
                solutie.append(item)
        return solutie
    def transfer(self,new_file):
        """Functia care transfera datele din fisierul curent in fisierul cu numele new_file

        Args:
            new_file (str): numele fisierului
        raises:
            IOError daca nu se poate accesa fisierul cu numele dat
        """
        f = open(new_file,'w')
        for item in self.get_all():
            f.write(f"{item.get_data().day}.{item.get_data().month},{item.get_ora().hour}:{item.get_ora().minute},{item.get_subiect()},{item.get_tip()}\n")
