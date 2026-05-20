#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
/// problema 9, lab01
/// 9. Citeste un sir de numere naturale nenule terminat cu 0 si determina
/// numarul cifrelor 0 in care se termina numarul produs al numerelor citite.
/// 
/// problema 16, lab01
/// 16. Determina toate numerele naturale mai mici decat un numar naturtal
///nenul dat n si care sunt relativ prime cu n.


/*Functia care gaseste numarul mai mic
* args: (int) a , un numar intreg ; (int) b, un numar intreg
* returns: (int), numarul mai mic dintre a si b
*/
int mai_mic(int a, int b)
{
    if (a <= b)
        return a;
    return b;
}

/*Functia care calculeaza exponentul lui 2 din descompunerea in factori primi
* args: (int) numar , un numar natural >0
* returns: (int), puterea lui 2 din descompunerea in factori primi a lui numar
*/
int exponent_2(int numar)
{
    int exponent=0;
    while (numar % 2 == 0)
    {
        exponent += 1;
        numar /= 2;
    }
    return exponent;
}

/*Functia care calculeaza exponentul lui 5 din descompunerea in factori primi
* args: (int) numar , un numar natural >0
* returns: (int), puterea lui 5 din descompunerea in factori primi a lui numar
*/
int exponent_5(int numar)
{
    int exponent = 0;
    while (numar % 5 == 0)
    {
        exponent += 1;
        numar /= 5;
    }
    return exponent;
}


/*Functia de afisare meniu aplicatie
* args: -
* returns: -
*/
void print_meniu()
{
    printf("Optiuni disponibile:\n");
    printf("0. Iesire din program----> 0\n");
    printf("1. Numarul de zerouri din produsul al unui sir de numere(terminat cu 0!!!)----> 1\n");
    printf("2. Toate numerele mai mic decat un numar relativ prime cu acesta----> 2\n");
    printf("Da-ti optiunea dorita:");

}

/*Functia care afiseaza nr zerouri din produs (optiunea 1 din meniu)
* args: -
* returns: -
*/
void optiunea_1()
{
    int numar_curent=-1, putere_2 = 0, putere_5 = 0, cifre_de_zero;
    printf("Numerele pe care le citim: ");
    while (numar_curent != 0)
    {
        scanf("%d", &numar_curent);

        if (numar_curent != 0)
        {
            putere_2 += exponent_2(numar_curent);
            putere_5 += exponent_5(numar_curent);
        }
    }
    cifre_de_zero = mai_mic(putere_2, putere_5);
    printf("Numarul de cifre zero de la finalul produsului este: %d\n", cifre_de_zero);
}
/*Functia care verifica daca a si b sunt relativ prime
* args: (int) a, numar natural nenul, (int) b, numar natural nenul
* returns: 1, daca a si b sunt prime intre ele(relativ prime), 0 altfel
*/
int relativ_prime(int a, int b)
{
    int rest;
    while (b != 0)
    {
        rest = a % b;
        a = b;
        b = rest;
    }
    if (a == 1)
        return 1;
    else return 0;
}
/*Functia care afiseaza numerele relativ prime cu un numar citit (optiunea 2 din meniu)
* args: -
* returns: -
*/
void optiunea_2()
{
    int numar_curent, numar_verificat,ok=0;
    printf("Numarul pe care il citim: n=");
    scanf("%d", &numar_curent);
    numar_verificat = numar_curent - 1;
    printf("Numerele relativ prime cu %d sunt: ", numar_curent);
    while (numar_verificat != 0)
    {
        if (relativ_prime(numar_curent, numar_verificat) == 1)
        {
            printf("%d ", numar_verificat);
            ok = 1;
        }
        numar_verificat-=1;
    }
    if (ok == 0)
        printf("Nu exista numere relativ prime cu %d\n", numar_curent);
    else printf("\n");
}
/*Functia main
*/
int main()
{    
    int ok = 1;
    while (ok)
    {
        print_meniu();
        scanf("%d", &ok);
        if (ok == 1)
            optiunea_1();
        else
            if (ok == 2)
                optiunea_2();
            else if (ok != 0)
                printf("Nu exista optiunea dorita! Try again\n");
    }
    
    return 0;
}