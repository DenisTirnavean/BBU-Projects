from repository.repository_sedinte import *
class Test_Repository:
    def test_incarca(self):
        f = open("teste/file_test.txt",'w')
        f.write("")
        f.write("20.02,8:00,ceva important,normal\n21.02,9:59,ceva important,extraordinar\n22.02,10:01,ceva important,normal\n18.03,8:00,ceva important,normal\n20.07,13:01,ceva important,extraordinar\n20.10,15:50,ceva important,normal\n25.12,7:39,ceva important,extraordinar")
        f.close()
        filepath="teste/file_test.txt"
        repo=Repository(filepath)
        lista=repo.get_all()
        assert len(lista)==7
    def test_adauga(self):
        filepath="teste/file_test.txt"
        data=datetime.date(2025,7,11)
        ora=datetime.time(9,30)
        subiect="ceva neimportant"
        tip="normal"
        sedinta=Sedinta(data,ora,subiect,tip)
        repo=Repository(filepath)
        repo.adauga_sedinta(sedinta)
        lista=repo.get_all()
        assert len(lista)==8
        subiect="ceva important"
        tip="normal"
        sedinta=Sedinta(data,ora,subiect,tip)
        try:
            repo.adauga_sedinta(sedinta)
            assert False
        except RepositoryError:
            assert True
    def run_teste_repo(self):
        self.test_incarca()
        self.test_adauga()