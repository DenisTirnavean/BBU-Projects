from domain.pachete import *
def validare_pachet(pachet):
    """
    Functia care valideaza daca pachetul de calatorii pachet are id_pachet int>0, data_inceput data calendaristica de forma AAAA-LL-ZZ
                data_sfarsit data calendaristica de forma AAAA-LL-ZZ, destinatia str nenul, pret float>0
    input:
        pachet- pachet de calatorii
    output:
        None - daca pachetul e in regula
    Raises:
        Ridica eroare(orore) de tipul ValueError cu mesajul text:
                -"ID invalid\n" daca id_pachet <=0 
                -"Data de inceput invalida\n" daca data este eronata (zile inexistente pentru anumite luni, luni inexistente)
                -"Data de sfarsit invalida\n" daca data este eronata (zile inexistente pentru anumite luni, luni inexistente), sau 
                                                in cazul in care data_sfarsit are loc inainte de data_inceput
                -"Destinatie invalida\n" daca destinatie este str null
                -"Pret invalid" daca pret este float<=0
    """
    id_pachet=get_id_pachet(pachet)
    data_inceput=get_data_inceput_pachet(pachet)
    data_sfarsit=get_data_sfarsit_pachet(pachet)
    destinatie=get_destinatie_pachet(pachet)
    pret=get_pret_pachet(pachet)
    if id_pachet <= 0:
        raise ValueError("ID invalid\n")
    elif data_inceput>data_sfarsit:
        raise ValueError("Data de sfarsit invalida\n")
    elif destinatie=='' or destinatie==' ':
        raise ValueError("Destinatie invalida\n")
    elif pret<=0:
        raise ValueError("Pret invalid")