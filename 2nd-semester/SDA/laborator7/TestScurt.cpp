#include "TestScurt.h"
#include "Colectie.h"
#include "IteratorColectie.h"
#include <assert.h>

void testAll() {
	Colectie c;
	c.adauga(5);
	c.adauga(6);
	c.adauga(0);
	c.adauga(5);
	c.adauga(10);
	c.adauga(8);

	assert(c.dim() == 6);
	assert(c.nrAparitii(5) == 2);

	assert(c.sterge(5) == true);
	assert(c.dim() == 5);

	assert(c.cauta(6) == true);
	assert(c.vida() == false);

	IteratorColectie ic = c.iterator();
	assert(ic.valid() == true);
	while (ic.valid()) {
		ic.element();
		ic.urmator();
	}
	assert(ic.valid() == false);
	ic.prim();
	assert(ic.valid() == true);

}

void test_task() {
	Colectie c;
	//cazul colectie vida
	int dif = c.diferenta();
	assert(dif == -1);
	c.adauga(5);
	c.adauga(6);
	c.adauga(0);
	c.adauga(5);
	c.adauga(10);
	c.adauga(8);
	dif = c.diferenta();
	//maxim este 10, minim este 0 => dif trebuie sa fie 10-0 =10
	assert(dif == 10);

	c.adauga(18);
	c.sterge(0);
	//maxim trebuie sa fie 18-5 = 13
	dif = c.diferenta();
	assert(dif == 13);
	
}