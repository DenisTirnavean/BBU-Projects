from tests.teste import *
class Teste_Files_Evenimente:
    def run_all_tests(self):
        self.test_adaugare()
        self.test_stergere()
        self.test_modifica()

    def test_adaugare(self):
        cale_catre_fisier="tests/event_test.txt"
        open("tests/event_test.txt","w")
        repo_eveniment=File_Repository_Eveniment(cale_catre_fisier)
        iD=1
        data=datetime.date(2030,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        repo_eveniment.adauga_eveniment(event)
        assert len(repo_eveniment)==1
        iD=1
        data=datetime.date(2090,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        try:
            repo_eveniment.adauga_eveniment(event)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Id deja existent!\n"
    
    def test_stergere(self):
        cale_catre_fisier="tests/event_test.txt"
        repo_eveniment=File_Repository_Eveniment(cale_catre_fisier)
        assert len(repo_eveniment)==1
        iD=2
        data=datetime.date(2026,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        repo_eveniment.adauga_eveniment(event)
        iD=3
        data=datetime.date(2026,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        repo_eveniment.adauga_eveniment(event)
        assert len(repo_eveniment)==3
        id=3
        repo_eveniment.sterge_eveniment(id)
        assert len(repo_eveniment)==2
        id=2
        repo_eveniment.sterge_eveniment(id)
        assert len(repo_eveniment)==1
        try:
            id=2
            repo_eveniment.sterge_eveniment(id)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Nu exista ce vrei sa elimini!\n"
        id=1
        repo_eveniment.sterge_eveniment(id)
        assert len(repo_eveniment)==0

    def test_modifica(self):
        repo=File_Repository_Eveniment("tests/event_test.txt")
        new_date=datetime.date(2022,8,29)
        iD=2
        data=datetime.date(2026,7,12)
        timp=3.5
        descriere="o sa fie fain"
        event= Eveniment(iD,data,timp,descriere)
        repo.adauga_eveniment(event)
        event=repo.get_un_eveniment(2)
        try:
            repo.update_event_data(new_date,event)
            assert False
        except RepositoryError:
            assert True
        new_date=datetime.date(2030,7,11)
        repo.update_event_data(new_date,event)
        new_descriere=""
        try:
            repo.update_event_descriere(new_descriere,event)
            assert False
        except RepositoryError:
            assert True
        new_descriere="mers la mare cu gasca"
        repo.update_event_descriere(new_descriere,event)
        assert event.get_descriere()==new_descriere
class Teste_Files_Persoane:
    def test_adaugare(self):
        f = open("tests/person_test.txt",'w')
        f.write("")
        repo=File_Repository_Persoana("tests/person_test.txt")
        assert repo.get_persoane()==[]
        personID=2
        nume="Adrian"
        adresa="Calea Turzii"
        person=Persoana(personID,nume,adresa)
        repo.adauga_persoana(person)
        assert len(repo.get_persoane())==1
        try:
            repo.adauga_persoana(person)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Id deja existent!\n"
    def test_stergere(self):
        repo=File_Repository_Persoana("tests/person_test.txt")
        repo.sterge_persoana(2)
        assert repo.get_persoane()==[]
        personID=2
        nume="Adrian"
        adresa="Calea Turzii"
        person=Persoana(personID,nume,adresa)
        #caz repo gol
        try:
            repo.sterge_persoana(personID)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Nu exista ce vrei sa elimini!\n"
        repo.adauga_persoana(person)
        personID=13
        nume="Alexandru"
        adresa="undeva"
        new_person=Persoana(personID,nume,adresa)
        #caz stergere ceva ce nu se gaseste in repo
        try:
            repo.sterge_persoana(personID)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Nu exista ce vrei sa elimini!\n"
        repo.adauga_persoana(new_person)
        repo.sterge_persoana(personID)
        assert len(repo.get_persoane())==1
    def test_modifica(self):
        f = open("tests/person_test.txt",'w')
        f.write("")
        repo=File_Repository_Persoana("tests/person_test.txt")
        assert repo.get_persoane()==[]
        iD=1
        nume="ion"
        adresa="aici"
        person=Persoana(iD,nume,adresa)
        repo.adauga_persoana(person)
        new_name="Johnathan"
        repo.update_nume_persoana(new_name,person)
        assert person.get_nume()==new_name
        new_name=""
        try:
            repo.update_nume_persoana(new_name,person)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Noul nume invalid!\n"
        new_adresa="acolo"
        repo.update_adresa_persoana(new_adresa,person)
        assert person.get_adresa()==new_adresa
        new_adresa=""
        try:
            repo.update_adresa_persoana(new_adresa)
            assert False
        except RepositoryError as msg:
            assert str(msg)=="Noua adresa invalida!\n"
    def test_raport(self):
        scrie_evenimente()
        scrie_persoane()
        service_eveniment=Service_Eveniment(File_Repository_Eveniment("tests\event_test.txt"))
        service_persoana=Service_Persoana(File_Repository_Persoana("tests\person_test.txt"))
        service_inscriere=Service_inscriere(service_persoana,service_eveniment)
        #id_persoana,id_eveniment
        service_inscriere.creaza_valideaza_adauga(1,1)
        service_inscriere.creaza_valideaza_adauga(2,1)
        service_inscriere.creaza_valideaza_adauga(3,1)
        service_inscriere.creaza_valideaza_adauga(4,3)
        service_inscriere.creaza_valideaza_adauga(5,8)
        service_inscriere.creaza_valideaza_adauga(6,2)
        service_inscriere.creaza_valideaza_adauga(7,7)
        service_inscriere.creaza_valideaza_adauga(8,6)
        service_inscriere.creaza_valideaza_adauga(1,6)
        service_inscriere.creaza_valideaza_adauga(2,4)
        service_inscriere.creaza_valideaza_adauga(2,8)
        #am avea in total 11 inscrieri deci 20% din 11 este aprox 2
        #cel mai eveniment ar avea 3 participanti (eveniment 1) , al doilea ar avea 2 participanti (eveniment 8)
        l=service_inscriere.top20()
        assert len(l)==2
        assert l[0].get_nr_participari()==3
        assert l[1].get_descriere()=="meci"
    def run_all_tests(self):
        self.test_adaugare()
        self.test_stergere()
        self.test_modifica()
        
def scrie_evenimente():
    f = open("tests/event_test.txt",'w')
    f.write("1,2030-07-11,3.5,mers la mare cu gasca\n")
    f.write("2,2030-07-11,3.5,mers la munte cu gasca\n")
    f.write("3,2030-07-11,3.5,mers la profi cu gasca\n")
    f.write("4,2030-07-11,3.5,mers la scoala cu gasca\n")
    f.write("5,2030-07-11,3.5,mers acasa cu gasca\n")
    f.write("6,2030-07-11,3.5,mers\n")
    f.write("7,2030-07-11,3.5,la\n")
    f.write("8,2030-07-11,3.5,meci\n")
    f.close()
def scrie_persoane():
    f = open("tests\person_test.txt",'w')
    f.write("1,Johnathan,acolo\n")
    f.write("2,Vasile,acolo\n")
    f.write("3,Ion,acolo\n")
    f.write("4,Gheorghe,acolo\n")
    f.write("5,Bula,acolo\n")
    f.write("6,Strula,acolo\n")
    f.write("7,Take,acolo\n")
    f.write("8,Ianke,acolo\n")
    f.write("9,Cadir,acolo\n")
def black_box_test():
    """Functie de testare tip black-box testint pentru functionalitatea de rapoarte (top 20%)
    specificatie functionalitate:  Functia care returneaza o lista care contine descrierea si numarul de participanti a top 20% evenimente cu cei mai multi participanti
    """
    #populare repo persoane si repo eveniment
    scrie_evenimente()
    scrie_persoane()
    service_eveniment=Service_Eveniment(File_Repository_Eveniment("tests\event_test.txt"))
    service_persoana=Service_Persoana(File_Repository_Persoana("tests\person_test.txt"))
    service_inscriere=Service_inscriere(service_persoana,service_eveniment)
    #id_persoana,id_eveniment
    service_inscriere.creaza_valideaza_adauga(1,1)
    service_inscriere.creaza_valideaza_adauga(2,1)
    service_inscriere.creaza_valideaza_adauga(3,1)
    service_inscriere.creaza_valideaza_adauga(4,3)
    service_inscriere.creaza_valideaza_adauga(5,8)
    service_inscriere.creaza_valideaza_adauga(6,2)
    service_inscriere.creaza_valideaza_adauga(7,7)
    service_inscriere.creaza_valideaza_adauga(8,6)
    service_inscriere.creaza_valideaza_adauga(1,6)
    service_inscriere.creaza_valideaza_adauga(2,4)
    service_inscriere.creaza_valideaza_adauga(2,8)
    #am avea in total 11 inscrieri deci 20% din 11 este aprox 2
    #cel mai eveniment ar avea 3 participanti (eveniment 1) , al doilea ar avea 2 participanti (eveniment 8)
    l=service_inscriere.top20()
    assert len(l)==2
    
class Final_Tester(MainTester):
    def __init__(self):
        super().__init__()
        self.test5=Teste_Files_Evenimente()
        self.test6=Teste_Files_Persoane()
    def run_test(self):
        super().run_test()
        self.test5.run_all_tests()
        self.test6.run_all_tests()
        black_box_test()