from service.service_sedinte import *

class Consola:
    def __init__(self,filepath):
        self.__service=Service(filepath)
        self.__lista_secreta=[]
        self.__dictionar={
            "afisare":self.__arata_sedinte,
            "adaugare":self.__adauga_sedinta,
            "set_data":self.__seteaza_data,
            "export":self.__export
        }
    def __arata_sedinte(self,args):
        """Functia care tipareste toate sedintele
        """
        lista=self.__service.get_all()
        if len(lista)==0:
            print("Nu aveti sedinte!")
            return
        print("DATA                 ORA                 SUBIECT                 TIP")
        for item in lista:
            print(f"{item.get_data().day}.{item.get_data().month}                 {item.get_ora().hour}:{item.get_ora().minute}                 {item.get_subiect()}                 {item.get_tip()}")
    def __next_sedinte(self):
        """Functia care tipareste sedintele din ziua urmatoare
        """
        lista=self.__service.sedinte_urmatoare()
        if lista==[]:
            print("Nu eveti sedinte pe ziua urmatoare!")
            return 
        lista.sort(key=lambda x: x.get_ora().hour,reverse=True)
        for item in lista:
            print(item)
    def __adauga_sedinta(self,args):
        if len(args)!=4:
            print("Numar insuficient de argumente!!")
            return
        try:
            data=args[0]
            data_desf=data.split(".")
            zi=int(data_desf[0])
            luna=int(data_desf[1])
            an=datetime.date.today().year
            data=datetime.date(an,luna,zi)
        except Exception:
            print("Formatul datei este invalid")
            return
        ora=args[1]
        try:
            ora_desf=ora.split(":")
            ora=int(ora_desf[0])
            minut=int(ora_desf[1])
            hour=datetime.time(ora,minut)
        except Exception:
            print("Formatul orei incorect")
            return
        subiect=args[2]
        tip=args[3]
        self.__service.creaza_valideaza_adauga(data,hour,subiect,tip)
        print("Sedinta adaugata cu succes")
    def __seteaza_data(self,args):
        if len(args)!=2:
            print("Numar insuficient de argumente!!")
            return
        try:
            data=args[0]
            data_desf=data.split(".")
            zi=int(data_desf[0])
            luna=int(data_desf[1])
            an=datetime.date.today().year
            data=datetime.date(an,luna,zi)
        except Exception:
            print("Formatul datei este invalid")
            return
        ora=args[1]
        try:
            ora_desf=ora.split(":")
            ora=int(ora_desf[0])
            minut=int(ora_desf[1])
            hour=datetime.time(ora,minut)
        except Exception:
            print("Formatul orei incorect")
            return
        solutie=self.__service.setare_data(data)
        if len(solutie)!=0:
            print("DATA                 ORA                 SUBIECT                 TIP")
            for item in solutie:
                print(f"{item.get_data().day}.{item.get_data().month}                 {item.get_ora().hour}:{item.get_ora().minute}                 {item.get_subiect()}                 {item.get_tip()}")
        else:
            print("Nu aveti sedinte in urmatoarele 3 zile de la data stabilita")
    def __export(self,args):
        if len(args)!=1:
            print("Numar incorect de argumente!!")
            return
        name=args[0]
        name=name.strip()
        name=name.lower()
        name+=".txt"
        file="repository/"
        file_name=file+name
        self.__service.transfer(file_name)
        print("Export realizat cu succes!!!")
    def run(self):
        self.__next_sedinte()
        print("Comenzi valide:")
        print("afisare \nset_data dd.mm hh:mm\nexport [file_name(fara .txt)]\nadaugare [dd.mm] [hh:mm] [subiect] [normal/extraordinar]")
        while True:
            try:
                cmd=input(">>>")
                if cmd=='x':
                    break
                argumente=cmd.split(" ")
                comanda=argumente[0]
                comanda=comanda.lower()
                if comanda=="set_data":
                    ok=1
                if comanda in self.__dictionar:
                    self.__dictionar[comanda](argumente[1:])
                    if self.__lista_secreta!=[] and ok==1:
                        print("DATA                 ORA                 SUBIECT                 TIP")
                        for item in self.__lista_secreta:
                            print(f"{item.get_data().day}.{item.get_data().month}                 {item.get_ora().hour}:{item.get_ora().minute}                 ",end="")
                            print(f"{item.get_subiect()}                 {item.get_tip()}")
                else: print("Comanda invalida")
            except ValidationError as msg:
                print(str(msg))
            except RepositoryError as msg:
                print(str(msg))
            except ValueError:
                print("Eroare de tip numeric\n")
            except IOError:
                print("Fisier invalid!!\n")
        print("bye")