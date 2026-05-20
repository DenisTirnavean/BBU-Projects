#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

void LO::init_free()
{
	for (int i = 0; i < cap - 1; i++)
		this->links[i] = i + 1;
	this->links[cap - 1] = -1;
	//primul index liber e 0
	this->first_free = 0;
}

void LO::redim()
{
	int newCap = cap * 2;
	TElement* newElems = new TElement[newCap];
	int* newLinks = new int[newCap];

	for (int i = 0; i < cap; i++) {
		newElems[i] = elems[i];
		newLinks[i] = links[i];
	}
	//facem un init_free modificat
	for (int i = cap; i < newCap - 1; i++)
		newLinks[i] = i + 1;
	newLinks[newCap - 1] = -1;
	//primul indice liber
	first_free = cap;

	delete[] elems;
	delete[] links;
	elems = newElems;
	links = newLinks;
	cap = newCap;
}

LO::LO(Relatie r) {
	/* de adaugat */
	relation = r;
	cap = 100000;
	elems = new TElement[cap];
	links = new int[cap];
	first = -1;
	lg = 0;
	//first_free se initializeaza cu 0 in init_free()
	init_free();
}

// returnare dimensiune
int LO::dim() const {
	/* de adaugat */
	return this->lg;
}

// verifica daca LO e vida
bool LO::vida() const {
	/* de adaugat */
	return lg == 0;
}

// prima pozitie din LO
Iterator LO::prim() const {
	/* de adaugat */
	return Iterator(*this);
}

// returnare element de pe pozitia curenta
//arunca exceptie daca poz nu e valid
TElement LO::element(Iterator poz) const {
	/* de adaugat */
	if (!poz.valid())
		throw exception();
	return elems[poz.curent];
}

//sterge element de pe o pozitie poz si returneaza elementul sters
//dupa stergere poz e pozitionat pe elementul de dupa cel sters
//arunca exceptie daca poz nu e valid

TElement LO::sterge(Iterator& poz) {
	if (!poz.valid())
		throw std::exception();  // iterator invalid

	int index_de_sters = poz.curent;
	TElement val_sters = elems[index_de_sters];
	int urmator = links[index_de_sters];

	if (index_de_sters == first) {

		first = links[first];//nu am de facut refacut legaturi prin tabela
	}
	else {

		int anterior = first;
		while (links[anterior] != index_de_sters) {
			anterior = links[anterior];
		}
		links[anterior] = links[index_de_sters];
	}

	//punem spatiul anterior ocupat de acel element in capul listei de spatii libere
	links[index_de_sters] = first_free;
	first_free = index_de_sters;

	poz.curent = urmator;
	lg--;

	return val_sters;
}


// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
Iterator LO::cauta(TElement e) const {
	/* de adaugat */
	int curent = first;

	while (curent != -1 && relation(elems[curent],e)) {
		if (elems[curent] == e) {
			Iterator it(*this);
			it.curent = curent;
			return it;
		}
		curent = links[curent];
	}
	Iterator it(*this);
	it.curent = -1;
	return it;
}

// adaugare element in LO
void LO::adauga(TElement e) {
	/* de adaugat */
	//daca nu mai am spatiu redimensionez, deci cresc dim, initiez iarasi spatii libere
	if (first_free == -1) //daca primul index liber din tabela = -1 atunci e problema de razboi
		redim();

	int nou = first_free; 
	first_free = links[first_free];
	elems[nou] = e; //elementul este adaugat, facem legaturile

	//cazul in care legam elementul pe prima pozitie
	//2 cazuri: ori lista goala, ori element e in relatie cu primul
	if (first == -1 || relation(e, elems[first])) {
		links[nou] = first;
		first = nou;
	}
	//altfel cautam locul potrivit
	else {
		int curent = first;
		while (links[curent] != -1 && relation(elems[links[curent]], e)) {
			curent = links[curent];
		}
		links[nou] = links[curent];
		links[curent] = nou;
	}

	lg++;
}


//destructor
LO::~LO() {
	/* de adaugat */
	delete[] elems;
	delete[] links;
}
