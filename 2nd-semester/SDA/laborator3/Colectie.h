#pragma once

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class Nod;
typedef Nod* PNod;

class Nod {
private:
	friend class Colectie;
	PNod urmator, precedent;
	TElem valoare;
public:
	Nod(TElem elem, PNod prec, PNod urm);
	PNod urm();
	PNod prec();
	TElem val();
};


class IteratorColectie;
class Colectie {
	friend class IteratorColectie;
private:
	/* aici e reprezentarea */
	PNod prim;
	PNod ultim;
	int size;
	Relatie relatie;

public:
	//constructorul implicit
	//complexitate theta(1)
	Colectie();

	//adauga un element in colectie
	//complexitate O(n) - iteram in cel mai rau caz prin toate elementele ldi
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	//complexitate O(n) - cautare O(n) + stergere efectiva theta(1)
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	//complexitate O(n) - in cel mai rau caz iteram prin toata ldi si tot nu gasim elem
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	//complexitate O(n) - in cel mai rau caz toate elementele sunt egale, si coincid cu elem
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	//complexitate theta(1)
	int dim() const;

	//verifica daca colectia e vida;
	//complexitate theta(1)
	bool vida() const;

	//returneaza un iterator pe colectie
	//complexitate theta(1)
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();
	
	//returneaza diferenta dintre valoarea maxima si minima
	int diferenta() const;



};

