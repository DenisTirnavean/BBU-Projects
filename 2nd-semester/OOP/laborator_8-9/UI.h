#pragma once
#include "Service.h"
#include <iostream>
using namespace std;
class Consola {
private:
	Service& service;
	/*Printeaza meniul aplicatiei in consola
	*/
	void print_meniu();

	/*Printeaza element din lista de carti
	*/
	void print_elem(const Carte& carte) const;

	/*Functionalitatea de adauga
	*/
	void add();

	/*Printeaza toate elementele din lista de carti
	*/
	void show();

	/*Functionalitatea de cautare
	*/
	void cauta();

	/*Functionalitate de stergere
	*/
	void sterge();

	/*Functionalitatea de modificare
	*/
	void modifica();

	/*Functionalitatea de filtrare
	*/
	void filtreaza();

	/*Functionalitatea de sortare
	*/
	void sorteaza();

	/*Functionalitate undo
	*/
	void undo();

	/*Cos de inchirieri
	*/
	void cos_stuff();

	void cos_show();

	void cos_add();

	void cos_empty();

	void cos_save();

	void cos_generate();

public:

	explicit Consola(Service& srv) :service{ srv } {}
	void run();
};