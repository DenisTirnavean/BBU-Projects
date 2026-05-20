#pragma once
#include "Domain.h"
#include <vector>
#include <fstream>
#include <random>
#include <chrono>
#include <algorithm>
using std::vector;

class Cos {
private:
	std::vector<Carte> continut;
	int contor;

public:
	Cos() { continut.clear(); contor = 0; }

	//Goleste cosul de carti
	void goleste_cos() noexcept;

	/*Functia de adaugare in cos
	@ carte: un obiect clasa Carte(referinta la obiect)
	* returns: nada
	#Carte se va afla in cosul de inchieri
	*/
	void add_to_cos(const Carte& carte);

	/*Functia care genereaza un cos de inchieri random
	@ cate: numar intreg, cate carti doresti sa contina cosul
	*returns: -
	*/
	void genereaza(int cate,const std::vector<Carte>& lista);

	/*Functia de export continut cos de inchieri intr-un fisier
	@ file_name: numele fisierului in care doresti sa salvezi
	*returns: -
	*/
	void export_in_fisier(const std::string& file_name);

	/*Functie care returneaza numarul de carti din cos
	*/
	int cate_carti() const;

	/*Functie care returneaza continutul cosului
	*/
	vector<Carte>& get_all_cos() noexcept;
};