#include "Service.h"
#include <stdio.h> 
#include <string.h>

void meniu()
{
	printf("Bine ati venit!\n");
	printf("Optiuni disponibile: \n");
	printf("0. Exit\n");
	printf("1. Adauga materie prima\n");
	printf("2. Afiseaza materii prime\n");
	printf("3. Modifica materii prime\n");
	printf("4. Sterge materie prima\n");
	printf("5. Filtreaza\n");
	printf("6. Sorteaza\n");
}
void adauga(Lista* lista)
{
	char nume[30];
	char prod[30];
	int cant;
	printf("Numele materiei: ");
	scanf_s("%s", nume, 30);
	printf("Numele producatorului: ");
	scanf_s("%s", prod, 30);
	printf("Cantitatea de materie prima: ");
	scanf_s("%d", &cant);
	if (exista_materie(lista, nume, prod) && cant > 0)
	{
		for (int i = 0; i < lista->lungime; i++)
			if (strcmp(((Materie_prima*)lista->elems[i])->nume, nume) == 0)
				((Materie_prima*)lista->elems[i])->cantitate = cant;
		printf("Cantitate modificata!!\n\n");
	}
	else {
		int ok = creaza_valid_adaug(lista, nume, prod, cant);
		if (ok == 0)
			printf("Materie prima adaugata cu succes!!\n\n");
		else
		{
			if (ok == 1) {
				printf("Nu s-a adaugat materia prima :(\n");
				printf("Nume invalid!!\n\n");
			}
			if (ok == 2) {
				printf("Nu s-a adaugat materia prima :(\n");
				printf("Producator invalid!!\n\n");
			}
			if (ok == 3) {
				printf("Nu s-a adaugat materia prima :(\n\n");
				printf("Cantitate invalida!!\n\n");
			}
		}
	}
}

void afiseaza(Lista* lista)
{
	if (lista->lungime != 0)
		{
			for (int i = 0; i < lista->lungime; i++)
				printf("%d.  Nume:{ %s }; Producator:{ %s }; Cantitate:{ %d }\n",i, ((Materie_prima*)lista->elems[i])->nume, ((Materie_prima*)lista->elems[i])->producator, ((Materie_prima*)lista->elems[i])->cantitate);
		}
	else printf("Lista goala!\n");
		printf("\n");
}

void modifica(Lista* lista)
{
	char nume[30], prod[30], new_nume[30], new_prod[30];
	int new_cant;
	printf("Ce materie prima doresti sa modifici?\n");
	printf("Numele materiei:");
	scanf_s("%s", nume, 30);
	printf("Numele producatorului:");
	scanf_s("%s", prod, 30);
	Materie_prima* mat= creaza_materie(nume, prod, 10);
	int poz = get_pozitie(lista,mat);
	distruge_materie(mat);
	if (poz != -1)
	{
		printf("Noul nume al materiei:");
		scanf_s("%s", new_nume, 30);
		printf("Noul nume al producatorului:");
		scanf_s("%s", new_prod, 30);
		printf("Noua cantitate:");
		scanf_s("%d", &new_cant);
		int ok = valideaza_materie(new_nume, new_prod, new_cant);
		if (ok == 0)
		{
			mat = creaza_materie(new_nume, new_prod, new_cant);
			modifica_element(lista, poz, (TElem)mat,distruge_materie);
			printf("Materie modificata cu succes!!\n\n");
		}
		else printf("Parametrii invalizi!!\n\n");
	}
	else {
		printf("Nu exista materia prima pe care o doresti!!\n\n");
	}
}

void sterge(Lista* lista)
{
	char nume[30], prod[30];
	printf("Ce materie doresti sa stergi?\n");
	printf("Numele materiei:");
	scanf_s("%s", nume, 30);
	printf("Numele producatorului:");
	scanf_s("%s", prod, 30);
	Materie_prima* mat = creaza_materie(nume, prod, 10);
	int poz = get_pozitie(lista, mat);
	distruge_materie(mat);
	if (poz != -1)
	{
		sterge_element(lista, poz,distruge_materie);
		printf("Materie stearsa cu succes!!\n\n");
	}
	else printf("Nu exista materia pe care doresti sa o stergi!!\n\n");


}

void filtru(Lista* lista)
{

	printf("Comenzi filtrare: nume, cantitate\n");

	char cmd[30];
	printf("Comanda: ");
	scanf_s("%s",cmd,30);

	char val[30];
	printf("Valoarea dupa care se filtreaza: ");
	scanf_s("%s", val,30);
	Lista* filt = filter(lista, cmd, val, (fil_fct)functia_filtru);
	if (filt->lungime== 0) {
		printf("Filtrarea nu a reusit :(\n");
	}
	else {
		afiseaza(filt);
	}
	distruge_lista(filt,distruge_materie);

}

void sorteaza(Lista* lista)
{

	int ok = 0;
	printf("Criterii sortare disponibile: nume, cantitate\n");
	printf("Comanda: ");
	char op[30];
	scanf_s("%s", op, 30);
	printf("0 - crescator\n1 - descrescator\n");
	int ord = 0;
	printf("Optiunea dvs: ");
	scanf_s("%d", &ord);
	Lista* sortata;
	if (op[strlen(op)] == '\0');
	if (strcmp(op, "nume") == 0) {
		sortata = sort(lista, (sort_fct)comp_nume, ord); ok = 1;
		afiseaza(sortata);
		distruge_lista(sortata, distruge_materie);
	}
	
	else if (strcmp(op, "cantitate") == 0) {
		sortata = sort(lista, (sort_fct)comp_cant, ord); ok = 1;
		afiseaza(sortata);
		distruge_lista(sortata, distruge_materie);
	}
	else {
		printf("\nCriteriu de sortare invalid:(\n");
	}
	if (ok == 0)
	{
		printf("\nNu am putut sorta!!\n");
	}

}

void run()
{
	Lista* lista = creaza_lista();
	int ok = 1;
	while (ok)
	{
		meniu();
		printf("Da-ti comanda:");
		scanf_s("%d", &ok);
		switch (ok)
		{
		case 0:
			break;
		case 1:
			printf("\n");
			adauga(lista);
			break;
		case 2:
			printf("\n");
			afiseaza(lista);
			break;
		case 3:
			printf("\n");
			modifica(lista);
			break;
		case 4:
			printf("\n");
			sterge(lista);
			break;
		case 5:
			printf("\n");
			filtru(lista);
			break;
		case 6:
			printf("\n");
			sorteaza(lista);
			break;
		default:
			printf("Comanda invalida\n\n");
		}


	}
	distruge_lista(lista,distruge_materie);
	printf("Bye\n");
}