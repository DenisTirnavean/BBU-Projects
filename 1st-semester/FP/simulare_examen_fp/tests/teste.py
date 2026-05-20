from service.service_vm import *

class Test_repo:
    def test_citire(self):
        filepath="tests/vm_test.txt"
        repo=FileRepository(filepath)
        assert len(repo.get_all())==10
    def run_all_test1(self):
        self.test_citire()
class Test_service:
    def test_cerinta_1(self):
        filepath="tests/vm_test.txt"
        service=Service(filepath)
        cpu_low=2.4
        cpu_high=5.0
        solution=service.cpu_interval(cpu_low,cpu_high)
        assert len(solution)==7
    def test_creare_dtos(self):
        pass
    def test_pret_mediu(self):
        filepath="tests/vm_test.txt"
        service=Service(filepath)
        repo=service.get_all()
        nr_ore=10
        lista=service.pret_mediu(nr_ore)
        for dto,item in lista,repo:
            assert dto.get_price()==item.get_pret*10
    def run_all_test2(self):
        self.test_cerinta_1()
class Test(Test_repo,Test_service):
    def run_all_tests(self):
        self.run_all_test1()
        self.run_all_test2()