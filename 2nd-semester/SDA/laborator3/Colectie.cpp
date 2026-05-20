#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) return true;
	return false;
}

Colectie::Colectie() {
	/* de adaugat */
	
	this->prim = nullptr;
	this->ultim = nullptr;
	this->size = 0;
	this->relatie = rel;
}

void Colectie::adauga(TElem e) {
	/* de adaugat */
	PNod new_elem = new Nod(e, nullptr, nullptr);
	if (this->size == 0)
	{
		//daca nu avem nimic in colectie
		this->prim = new_elem;
		this->ultim = new_elem;
	}
	else {
		PNod head = this->prim;
		while (head != nullptr)
		{
			if (rel(head->val(), e))
			{//iteram printre elemente pana ce gasim dupa cine inseram  ([element] RELATIE [e] RELATIE [element_urmator])
				if (head->urm() == nullptr || rel(e, head->urm()->val()))
					break;
			}
			head = head->urm();
		}
		//cazul in care inseram pe prima pozitie adica nu avem elem in relatie cu e, deci trebuie sa avem e in relatie cu elem
		if (head == nullptr)
		{
			new_elem->urmator = prim;
			this->prim->precedent = new_elem;
			this->prim = new_elem;
		}
		//cazul oarecare
		else if (head != this->ultim)
		{
			new_elem->precedent = head;
			new_elem->urmator = head->urmator;
			head->urmator->precedent = new_elem;
			head->urmator = new_elem;
		}
		//cazul in care inseram pe ultima pozitie
		else {
			new_elem->precedent = head;
			this->ultim->urmator = new_elem;
			this->ultim = new_elem;
		}
	}
	size++;
}


bool Colectie::sterge(TElem e) {
	/* de adaugat */
	if (!cauta(e))
		return false;
	if (this->prim == nullptr)
		return false;
	PNod head = this->prim;
	
	//verificare interval de valori
	if (rel(e, head->val()) && !rel(head->val(), e)) 
		return false;
	if (rel(this->ultim->val(), e) && !rel(this->ultim->val(), e)) 
		return false;


	while (head != nullptr && rel(head->val(), e))
	{
		if (head->val() == e)
		{
			if (head->precedent != nullptr)
			{
				if (head->urmator != nullptr)
				{
					//cazul oarecare
					head->precedent->urmator = head->urmator;
					head->urmator->precedent = head->precedent;
				}
				else
				{
					//cazul stergerii ultimului element
					head->precedent->urmator = nullptr;
					ultim = head->precedent;
				}
			}
			else
			{
				if (head->urmator != nullptr)
				{
					//cazul stergerii primului element
					prim = head->urmator;
					head->urmator->precedent = nullptr;
				}
				else
				{
					//combo: prim = ultim = oarecare
					prim = nullptr;
					ultim = nullptr;
				}
			}

			delete head;
			size--;
			return true;
		}
		head = head->urm();
	}
	return false;
}


bool Colectie::cauta(TElem elem) const {
	/* de adaugat */
	if (this->prim == nullptr)
		return 0;

	PNod head = this->prim;

	if (rel(elem, head->val()) && !rel(head->val(), elem)) // daca elem rel prim, inseamna ca nu avem, elem ar trebuit atunci sa fie exact primul
		return false;
	if (rel(this->ultim->val(), elem) && !rel(this->ultim->val(), elem)) // daca ultim rel elem, inseamna ca nu avem
		return false;

	while (head != nullptr && rel(head->val(), elem))
	{
		if (head->val() == elem)
			return true;
		head = head->urm();
	}
	return false;
}


int Colectie::nrAparitii(TElem elem) const {
	/* de adaugat */
	int nrAp = 0;
	if (this->prim == nullptr)
		return 0;
	PNod head = this->prim;
	//verificari pt reducerea complexitatii
	if (rel(elem, head->val()) && !rel(head->val(),elem)) // daca elem rel prim, inseamna ca nu avem, elem ar trebuit atunci sa fie exact primul
		return 0;
	if (rel(this->ultim->val(), elem) && !rel(this->ultim->val(), elem)) // daca ultim rel elem, inseamna ca nu avem
		return 0;
	//cautare efectiva
	while (head != nullptr && rel(head->val(),elem))
	{
		if (head->val() == elem)
			nrAp++;
		head = head->urm();
	}
	return nrAp;
}



int Colectie::dim() const {
	/* de adaugat */
	return size;
}


bool Colectie::vida() const {
	/* de adaugat */

	return size == 0;
}


IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	/* de adaugat */
	PNod head;
	while (this->prim != nullptr)
	{
		head = this->prim->urm();
		delete prim;
		this->prim = head;
	}
}
//complexite theta(1)
int Colectie::diferenta() const
{
	if (this->vida())
		return -1;
	return this->ultim->val() - this->prim->val();
}

Nod::Nod(TElem elem, PNod prec, PNod urm)
{
	this->valoare = elem;
	this->urmator = urm;
	this->precedent = prec;

}

PNod Nod::urm()
{
	return this->urmator;
}

PNod Nod::prec()
{
	return this->precedent;
}

TElem Nod::val()
{
	return this->valoare;
}
