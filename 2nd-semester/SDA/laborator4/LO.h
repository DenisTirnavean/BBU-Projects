#pragma once
#include <exception>
class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;

typedef bool (*Relatie)(TElement, TElement);

#define NULL_TELEMENT -1

class LO {
private:
	friend class Iterator;
private:
	/* aici reprezentarea */
	Relatie relation;
	TElement* elems;
	int* links;
	int first, first_free; //indexul primului element ocupat,indexul primului spatiu liber 
	int cap, lg;
	/*Functia de initializare spatiu liber
	*/
	void init_free();
	void redim();

public:
	// constructor
	LO(Relatie r);

	// returnare dimensiune
	//theta(1)
	int dim() const;

	// verifica daca LO e vida
	//theta(1)
	bool vida() const;

	// prima pozitie din LO
	//theta(1)
	Iterator prim() const;

	// returnare element de pe pozitia curenta
	//arunca exceptie daca poz nu e valid
	//theta(1)
	TElement element(Iterator poz) const;

	// adaugare element in LO a.i. sa se pastreze ordinea intre elemente
	//O(n), adaugare efectiva theta(1) amortizat
	// crearea legaturilor este costisitoare pana ce gasesc locul potrivit
	void adauga(TElement e);

	// sterge element de pe o pozitie poz si returneaza elementul sters
	//dupa stergere poz e pozitionat pe elementul de dupa cel sters
	//arunca exceptie daca poz nu e valid
	//O(n), stergere efectiva theta(1), cautarea nodului anterior este O(n)
	TElement sterge(Iterator& poz);

	// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
	//O(n), in cel mai rau caz iterez tot
	Iterator cauta(TElement e) const;

	//destructor
	~LO();

};
