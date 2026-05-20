#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	/* de adaugat */
	curent = c.prim;
	first = c.prim;
}

TElem IteratorColectie::element() const {
	/* de adaugat */
	return curent->val();
}

bool IteratorColectie::valid() const {
	/* de adaugat */
	return curent != nullptr;
}

void IteratorColectie::urmator() {
	/* de adaugat */
	curent = curent->urm();
}

void IteratorColectie::prim() {
	/* de adaugat */
	curent = first;
}
