from teste.test_domain import *
from teste.test_repo import *
from service.service_sedinte import Service
class Test_Service:
    def test_get_all(self):
        f = open("teste/file_test.txt",'w')
        f.write("")
        f.write("20.02,8:00,ceva important,normal\n21.02,9:59,ceva important,extraordinar\n22.02,10:01,ceva important,normal\n18.03,8:00,ceva important,normal\n20.07,13:01,ceva important,extraordinar\n20.10,15:50,ceva important,normal\n25.12,7:39,ceva important,extraordinar")
        f.close()
        filepath="teste/file_test.txt"
        service=Service(filepath)
        lista=service.get_all()
        assert len(lista)==7
    def test_next_sedinte(self):
        f = open("teste/file_test.txt",'w')
        f.write("")
        f.write("31.01,8:00,ceva important,normal\n21.02,9:59,ceva important,extraordinar\n22.02,10:01,ceva important,normal\n18.03,8:00,ceva important,normal\n20.07,13:01,ceva important,extraordinar\n20.10,15:50,ceva important,normal\n25.12,7:39,ceva important,extraordinar")
        f.close()
        service=Service("teste/file_test.txt")
        
        lista=service.sedinte_urmatoare()
        print(len(lista))
        assert len(lista)==0
    def test_cva(self):
        f = open("teste/file_test.txt",'w')
        f.write("")
        f.write("31.01,8:00,ceva important,normal\n21.02,9:59,ceva important,extraordinar\n22.02,10:01,ceva important,normal\n18.03,8:00,ceva important,normal\n20.07,13:01,ceva important,extraordinar\n20.10,15:50,ceva important,normal\n25.12,7:39,ceva important,extraordinar")
        f.close()
        service=Service("teste/file_test.txt")
        data=datetime.date(2025,12,6)
        ora=datetime.time(8,30)
        subiect="ceva important"
        tip="extraordinar"
        try:
            service.creaza_valideaza_adauga(data,ora,subiect,tip)
            assert False
        except RepositoryError:
            assert True
        subiect="cel mai super meeting"
        tip="normal"
        service.creaza_valideaza_adauga(data,ora,subiect,tip)
    def run_test_service(self):
        self.test_get_all()
        self.test_next_sedinte()
        self.test_cva()
class Final_tester(Test_domain,Test_Repository,Test_Service):
    def run_all_tests(self):
        self.run_teste_domain()
        self.run_teste_repo()
        self.run_test_service()