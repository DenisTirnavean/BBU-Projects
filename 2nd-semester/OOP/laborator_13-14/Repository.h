#pragma once
#include "Domain.h"
#include <vector>
#include <fstream>
#include "Exceptii.h"
#include <map>

using namespace std;

//clasa pur abstracta de repository
class Repository_abstract {
public:
	virtual void adauga(const Carte& a) = 0;

	virtual void modifica_carte(const int poz, const Carte& new_carte) = 0;

	virtual void sterge_carte(Carte& carte) = 0;

	virtual vector<Carte>& get_elems() = 0;

	virtual int get_size() const noexcept = 0;

	virtual bool cauta(const string& titlu, const string& autor) const = 0;

	virtual int cauta_carte(const string titlu, const string autor) = 0;

	virtual Carte& get_carte(int pozitie) = 0;

	virtual void insert(const Carte& carte, const int poz) = 0;

	virtual ~Repository_abstract() = default;
};

class Repository :public Repository_abstract {
private:
	vector<Carte> lista;

public:

	/*Functia care returneaza o carte de pe pozitia pozitie
	*/
	Carte& get_carte(int pozitie);

	/*Functia de adaugare carte in repo
	* throws: Eroare cu mesajul "Carte deja existenta\n" , daca exista deja o carte in repo cu titlul si autorul dat
	*/
	virtual void adauga(const Carte& carte) override;

	/*Functia care returneaza dimensiunea repository-ului (numarul de elemente)
	*/
	int get_size() const noexcept;

	virtual void insert(const Carte& carte, const int poz);

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
	virtual void sterge_carte(Carte& carte);


	/*Functia de update carte
	* @carte: Carte, cartea pe care doresti sa o modifici
	* @new_carte: Carte, noile caracteristici ale cartii
	* throws: Eroare cu mesaj "Carte deja existenta\n", daca cartea dupa modificari ar coincide cu o carte deja existenta
	*/
	virtual void modifica_carte(const int poz, const Carte& new_carte);


	bool cauta(const string& titlu, const string& autor) const;

	/*Functia care retrieves the Carti from current repository instance
	*returns: vector<Carte>, un vector care contine toate elementele instantei curente de Repository
	*/
	vector<Carte>& get_elems() noexcept;
	virtual ~Repository() = default;
};

class Repository_file :public Repository {
private:
	string file_name;

	/*Functia de stocare continut repo in fisierul dat de file_name
	*/
	void save_to_file();

	/*Functia de incarcare repo cu continutul fisierului file_name
	*/
	void load_from_file();
public:

	Repository_file(const string& filename) : file_name{ filename } {
		load_from_file();
	}

	void adauga(const Carte& carte) override {
		Repository::adauga(carte);
		save_to_file();
	}
	void sterge_carte(Carte& carte) override {
		Repository::sterge_carte(carte);
		save_to_file();
	}
	void modifica_carte(const int poz, const Carte& new_carte) override {
		Repository::modifica_carte(poz, new_carte);
		save_to_file();
	}
	void insert(const Carte& carte, const int poz) override {
		Repository::insert(carte, poz);
		save_to_file();
	}
	~Repository_file() override = default;
};

class Repository_map : public Repository_abstract {
private:
	map<int, Carte> dict;
	vector<Carte> continut;
	float reliability;

	void toss_the_dice();
public:
	Repository_map() = default;
	Repository_map(float prob) : reliability{ prob } {}

	/*Functia de adaugare carte in repo
	* throws: Eroare cu mesajul "Carte deja existenta\n" , daca exista deja o carte in repo cu titlul si autorul dat
	*/
	void adauga(const Carte& carte) override;


	/*Functia de update carte
	* @carte: Carte, cartea pe care doresti sa o modifici
	* @new_carte: Carte, noile caracteristici ale cartii
	* throws: Eroare cu mesaj "Carte deja existenta\n", daca cartea dupa modificari ar coincide cu o carte deja existenta
	*/
	void modifica_carte(const int poz, const Carte& new_carte) override;

	/*Functia de stergere din repository
	* @carte: Carte, cartea pe care dorim sa o stergem
	* throws: Eroare cu mesaj "Carte inexistenta\n", daca nu exista cartea pe care dorim sa o stergem
	*/
	void sterge_carte(Carte& carte) override;

	/*Functia care retrieves the Carti from current repository instance
	*returns: vector<Carte>, un vector care contine toate elementele instantei curente de Repository
	*/
	vector<Carte>& get_elems() override;

	/*Functia care returneaza dimensiunea repository-ului (numarul de elemente)
	*/
	int get_size() const noexcept override;

	bool cauta(const string& titlu, const string& autor) const override;


	void insert(const Carte& carte, const int poz) override;

	/*Functia de cautare carte in repo
	* @titlu : string , titlul cartii
	* @autor : string , autorul cartii
	* returns: (int) indicele cartii din repository daca aceasta exista, -1 altfel
	*/
	int cauta_carte(const string titlu, const string autor) override;

	Carte& get_carte(int pozitie) override;
};