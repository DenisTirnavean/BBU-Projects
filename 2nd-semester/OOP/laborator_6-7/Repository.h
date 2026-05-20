#pragma once
#include "Domain.h"
#include "MyList.h"
#include <vector>
#include <map>
using namespace std;




class Repository {
private:
	MyVector<Carte> lista;
public:
	/*Functia care returneaza o carte de pe pozitia pozitie
	*/
	Carte& get_carte(int pozitie);

	/*Functia de adaugare carte in repo
	* throws: Eroare cu mesajul "Carte deja existenta\n" , daca exista deja o carte in repo cu titlul si autorul dat
	*/
	void adauga(const Carte& carte);

	/*Functia care returneaza dimensiunea repository-ului (numarul de elemente)
	*/
	int get_size() const noexcept;

	/*Functia de cautare carte in repo
	* @titlu : string , titlul cartii
	* @autor : string , autorul cartii
	* returns: (int) indicele cartii din repository daca aceasta exista, -1 altfel 
	*/
	int cauta_carte(const string titlu, const string autor);


	/*Functia de stergere din repository
	* @carte: Carte, cartea pe care dorim sa o stergem
	* throws: Eroare cu mesaj "Carte inexistenta\n", daca nu exista cartea pe care dorim sa o stergem
	*/
	void sterge_carte(Carte& carte);


	/*Functia de update carte
	* @carte: Carte, cartea pe care doresti sa o modifici
	* @new_carte: Carte, noile caracteristici ale cartii
	* throws: Eroare cu mesaj "Carte deja existenta\n", daca cartea dupa modificari ar coincide cu o carte deja existenta
	*/
	void modifica_carte(const int poz,const Carte& new_carte);

	MyVector<Carte> get_elems();
};