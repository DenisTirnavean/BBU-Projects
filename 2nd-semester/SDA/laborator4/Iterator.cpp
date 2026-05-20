#include "Iterator.h"
#include "LO.h"
using std::exception;

Iterator::Iterator(const LO& lo) : lo(lo) {
	/* de adaugat */
	curent = lo.first;
}

void Iterator::prim() {
	/* de adaugat */
	curent = lo.first;
}

void Iterator::urmator() {
	/* de adaugat */
	if (!valid())
		throw exception("o eroare\n");
	curent = lo.links[curent];
}

bool Iterator::valid() const {
	/* de adaugat */
	return curent != -1;
}

TElement Iterator::element() const {
	/* de adaugat */
	if (!valid())
		throw exception("o alta eroare\n");
	return lo.elems[curent];
}

TElement Iterator::elimina()
{
		if (!valid()) {
			throw std::exception("Iterator invalid");
		}
		return const_cast<LO&>(lo).sterge(*this);
}

	




