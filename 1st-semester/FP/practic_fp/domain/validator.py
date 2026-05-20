from domain.sedinte import *

class Validator:
    """Clasa obiectelor de tip Validator sedinte
    """
    def valideaza_sedinta(self,sedinta):
        """Valideaza o sedinta sedinta

        Args:
            sedinta (Sedinta): o sedinta
        returns: -
        raises:
            ValidationError cu mesaj:
                "Data invalida\n", daca data sedintei se  afla in trecut
                "Tip invalid\n",daca tipul nu este stringul "normal" sau "extraordinar"
                "Subiect invalid\n", daca subiectul este sir vid
        """
        errors=""
        tip=sedinta.get_tip()
        if tip!='normal' and tip!='extraordinar':
           errors+="Tip invalid\n"
        data=sedinta.get_data()
        if data.day<datetime.date.today().day and data.month<datetime.date.today().month:
            errors+="Data invalida\n"
        subiect=sedinta.get_subiect()
        if subiect=="":
            errors+="Subiect invalid\n"
        if errors!="":
            raise ValidationError(errors)
        
    