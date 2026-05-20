#pragma once
#include <iostream>
using std::cout;
#define NIL -1

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

class Colectie {

	friend class IteratorColectie;

private:
	struct Nod {
		TElem e;
		int stanga;
		int dreapta;
	};

	Nod* noduri; //noduri ABC
	int radacina; 
	int capacitate; //cat incape
	int dimensiune; //cat avem

	int* urmatorLiber; //spatii libere in tabela
	int primLiber; //primul liber din tabela


	//functii utile
	 
	//functie care adauga un nou nod cu informatia utila e in arborele cu radacina nodCurent
	//nodCurent -int- index-ul radacinii arborelui
	//e -TElem- informatia utila pe care doresti sa o adaugi in colectie
	//complexitate O(h), unde h este inaltimea arborelui,
	//caz favorabil, h = log2n, O(log2n)
	//caz defavorabil, h = n, O(n)
	void adaugaRec(int& nodCurent, TElem e);

	//functie care cauta elementul cu informatia utila e in arborele cu radacina nodCurent
	//nodCurent -int- index-ul radacinii arborelui
	//e -TElem- informatia utila pe care doresti sa o cauti in colectie
	//returns: True/False - true daca e se afla in subarbore, false altfel
	//complexitate caz favorabil O(log2n)
	//complexitate caz defavorabil O(n)
	bool cautaRec(int nodCurent, TElem e) const;

	//functie care returneaza numarul de aparitii a nodului cu informatie utila e in arborele cu radacina nodCurent
	//nodCurent -int- index-ul radacinii arborelui
	//e -TElem- informatia utila pe care doresti sa o cauti in colectie
	//returns: numarul de aparitii a lui e in subarbore
	//complexitate caz favorabil Theta(1), elementul este radacina
	//complexitate caz defavorabil O(n)
	int nrAparitiiRec(int nodCurent, TElem e) const;

	//functie care sterge nodul cu informatia utila e din arborele cu radacina nodCurent
	//returns: True/False: true daca a reusit sa stearga elementul mentionat, false altfel
	//complexitate caz favorabil O(log2n)
	//complexitate caz defavorabil O(n)
	bool stergeRec(int& nodCurent, TElem e);

	//functie de redimensionare tabela
	//postconditii: o sa avem tabela mai mare
	//Theta(capacitate*2)
	void redimensionare();

	//rezerva un loc pentru un nod in tabela
	//Theta(1) amortizat
	int aloca();

	//goleste locul index din tabela, il adauga in lista de spatii libere
	void dealoca(int index);
	
public:
	//constructorul implicit
	//Theta(capacitate) - inlantuirea de spatii libere
	Colectie();

	//adauga un element in colectie
	//complexitate O(h), unde h este inaltimea arborelui,
	//caz favorabil, h = log2n, O(log2n)
	//caz defavorabil, h = n, O(n)
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	//complexitate O(h), unde h este inaltimea arborelui,
	//caz favorabil, h = log2n, O(log2n)
	//caz defavorabil, h = n, O(n)
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	//O(k+h), unde k este numarul de aparitii a elementului
	//O(n), caz defavorabil - toate elementele sunt egale
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	//Theta(1)
	int dim() const;

	//verifica daca colectia e vida;
	//Theta(1)
	bool vida() const;

	//returneaza un iterator pe colectie
	//Theta(h), operatia prim() din constructorul iteratorului=>situarea curentului pe minimul din arbore
	IteratorColectie iterator() const;

	// destructorul colectiei
	//Theta(1)
	~Colectie();

	bool stergeIterativ(TElem e);

	//returneaza diferenta dintre elementul maxim si cel minim
	//returneaza -1 daca colectia este vida
	//complexitate O(h), unde h este inaltimea arborelui
	//caz favorabil O(log2n) arbore echilibrat, caz defavorabil O(n), arbore degenerat(linie)
	int diferenta() const;

};
