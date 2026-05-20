from tests.teste_files import *
import unit_teste

class Tests_domain(Test_Event,Test_Persoana,unittest.TestCase):
    def setUp(self):
        self.id=1
        self.nume='Ionica'
        self.adresa='Calea Turzii'
        self.person=Persoana(self.id,self.nume,self.adresa)
        self.id_e=1
        self.data=datetime.date(2025,7,11)
        self.durata=5.7
        self.descriere="ok"
        self.eveniment=Eveniment(self.id_e,self.data,self.durata,self.descriere)
    def test_creare(self):
        self.assertEqual(self.person.get_identificator(),self.id)
        self.assertEqual(self.person.get_nume(),self.nume)
        self.assertEqual(self.person.get_adresa(),self.adresa)
        self.assertEqual(self.eveniment.get_identificator(),self.id_e)
        self.assertEqual(self.eveniment.get_data(),self.data)
        self.assertEqual(self.eveniment.get_timp(),self.durata)
        self.assertEqual(self.eveniment.get_descriere(),self.descriere)
        eveniment2=Eveniment(self.id_e,self.data,self.durata,self.descriere)
        self.assertEqual(self.eveniment,eveniment2)
        persoana2=Persoana(self.id,self.nume,self.adresa)
        self.assertEqual(self.person,persoana2)
    def test_valideaza(self):
        persoana_invalida=Persoana(-1,"","")
        eveniment_invalid=Eveniment(-1,datetime.date(2011,7,11),-12.9,"")
        validator=Validator()
        validator.valideaza_eveniment(self.eveniment)
        validator.valideaza_persoana(self.person)
        self.assertRaises(ValidationError,validator.valideaza_eveniment,eveniment_invalid)
        self.assertRaises(ValidationError,validator.valideaza_persoana,persoana_invalida)
        
    def tearDown(self):
        return super().tearDown()
class Tests_repo(unittest.TestCase):
    def setUp(self):
        f = open("tests\event_test.txt",'w')
        f.write("")
        f.close()
        f = open("tests\person_test.txt")
        f.write("")
        f.close()
        self.repo_eveniment=File_Repository_Eveniment("tests\event_test.txt")
        self.repo_persoana=File_Repository_Persoana("tests\person_test.txt")
    def test_adauga(self):
        id=1
        nume='Ionica'
        adresa='Calea Turzii'
        persoana=Persoana(id,nume,adresa)
        self.repo_persoana.adauga_persoana(persoana)
        self.assertEqual(len(self.repo_persoana),1)
        id_e=1
        data=datetime.date(2025,7,11)
        durata=5.7
        descriere="ok"
        eveniment=Eveniment(id_e,data,durata,descriere)
        self.repo_eveniment.adauga_eveniment(eveniment)
        self.assertEqual(len(self.repo_eveniment),1)
    def test_sterge(self):
        id=1
        nume='Ionica'
        adresa='Calea Turzii'
        persoana=Persoana(id,nume,adresa)
        self.repo_persoana.adauga_persoana(persoana)
        self.assertEqual(len(self.repo_persoana),1)
        self.repo_persoana.sterge_persoana(id)
        self.assertEqual(len(self.repo_persoana),0)
        self.assertRaises(RepositoryError,self.repo_persoana.sterge_persoana,id)
        id_e=1
        data=datetime.date(2025,7,11)
        durata=5.7
        descriere="ok"
        eveniment=Eveniment(id_e,data,durata,descriere)
        self.repo_eveniment.adauga_eveniment(eveniment)
        self.assertEqual(len(self.repo_eveniment),1)
        self.repo_eveniment.sterge_eveniment(id_e)
        self.assertEqual(len(self.repo_eveniment),0)
        self.assertRaises(RepositoryError, self.repo_eveniment.sterge_eveniment,id_e)
    def test_modifica(self):
        id=1
        nume='Ionica'
        adresa='Calea Turzii'
        persoana=Persoana(id,nume,adresa)
        self.repo_persoana.adauga_persoana(persoana)
        self.assertEqual(len(self.repo_persoana),1)
        new_adress="undeva"
        self.repo_persoana.update_adresa_persoana(new_adress,persoana)
        p=self.repo_persoana.get_o_persoana(id)
        self.assertEqual(p.get_adresa(),new_adress)
        new_nume="undeva"
        self.repo_persoana.update_nume_persoana(new_adress,persoana)
        p=self.repo_persoana.get_o_persoana(id)
        self.assertEqual(p.get_nume(),new_nume)
        id_e=1
        data=datetime.date(2025,7,11)
        durata=5.7
        descriere="ok"
        eveniment=Eveniment(id_e,data,durata,descriere)
        self.repo_eveniment.adauga_eveniment(eveniment)
        self.assertEqual(len(self.repo_eveniment),1)
    def tearDown(self):
        return super().tearDown()
if __name__=="__main__":
    unittest.main()