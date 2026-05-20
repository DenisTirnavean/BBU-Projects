from domain.validator import *
class Test_domain:
    def test_creare(self):
        data=datetime.date(2025,12,6)
        ora=datetime.time(8,30)
        subiect="ceva important"
        tip="extraordinar"
        sedinta=Sedinta(data,ora,subiect,tip)
        assert sedinta.get_data()==data
        assert sedinta.get_ora()==ora
        assert sedinta.get_subiect()==subiect
        assert sedinta.get_tip()==tip
        other_sedinta=Sedinta(data,ora,subiect,tip)
        assert sedinta==other_sedinta
        tip='normal'
        other_sedinta=Sedinta(data,ora,subiect,tip)
        assert sedinta!=other_sedinta
    def test_validare(self):
        data=datetime.date(2025,12,6)
        ora=datetime.time(8,30)
        subiect="ceva important"
        tip="extraordinar"
        sedinta=Sedinta(data,ora,subiect,tip)
        validator=Validator()
        validator.valideaza_sedinta(sedinta)
        tip="smeker"
        sedinta=Sedinta(data,ora,subiect,tip)
        try: 
            validator.valideaza_sedinta(sedinta)
            assert False
        except ValidationError:
            assert True
        data=datetime.date(2024,12,6)
        tip="extraordinar"
        sedinta=Sedinta(data,ora,subiect,tip)
        try: 
            validator.valideaza_sedinta(sedinta)
            assert False
        except ValidationError:
            assert True
        subiect=""
        data=datetime.date(2026,12,6)
        sedinta=Sedinta(data,ora,subiect,tip)
        try: 
            validator.valideaza_sedinta(sedinta)
            assert False
        except ValidationError:
            assert True
    def run_teste_domain(self):
        self.test_creare()