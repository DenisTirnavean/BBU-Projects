
from domain.participari import *
class ValidationError(Exception):
    """Erori de validare
    """

class Validator:
    """Clasa validator
    """
    def valideaza_eveniment(self,Eveniment=Eveniment):
        """Validator pentru Evenimente
        Ridica erori tip ValidatorError cu mesajele:
            "ID numeric invalid!\n" , daca ID al obiectului din clasa Eveniment <=0
            "Data invalida!\n", daca data noului Eveniment este situata in trecut
            "Timp invalid!\n", daca durata Evenimentului este nula/ mai mica ca zero
            "Descriere invalida!\n", daca descrierea este vida
        """
        errors=""
        id=Eveniment.get_identificator()
        data=Eveniment.get_data()
        timp=Eveniment.get_timp()
        desc=Eveniment.get_descriere()
        if id<=0:
            errors+="ID numeric invalid!\n"
        current_date=DATA_AZI()
        if data<current_date:
            errors+="Data invalida! Data evenimentului trebuie sa fie in viitor\n"
        if timp<=0:
            errors+="Timp invalid!\n"
        if desc=="":
            errors+="Descriere invalida!\n"
        if len(errors)==0:
            pass
        else:
            raise ValidationError(errors)
    def valideaza_persoana(self,Persoana=Persoana):
        """Validator pentru Persoana
        Ridica erori tip ValidatorError cu mesajele:
            "ID numeric invalid!\n" , daca ID al obiectului din clasa Persoana <=0
            "Nume invalid!\n", daca numele este vid
            "Adresa invalida!\n", daca adresa este vida
        """
        errors=""
        id=Persoana.get_identificator()
        nume=Persoana.get_nume()
        adresa=Persoana.get_adresa()
        if id<=0:
            errors+="ID numeric invalid!\n"
        if nume=="":
            errors+="Nume invalid!\n"
        if adresa=="":
            errors+="Adresa invalida!\n"
        if len(errors):
            raise ValidationError(errors)
    def valideaza_inscriere(self,inscriere=Inscriere):
        """
            Functia de validare inscriere
        input:
            inscriere (Inscriere): obiect clasa Inscriere
        """
        persoana=inscriere.get_persoana()
        eveniment=inscriere.get_eveniment()
        if persoana.e_sters()==True or eveniment.e_sters()==True:
            raise ValidationError("Inscriere invalida!!!\n")