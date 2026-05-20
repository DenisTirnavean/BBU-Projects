#pragma once
#include "Repository.h"
#include "Validator.h"

typedef bool(*fltr_fct)(const Carte& a,const string atribut);
typedef int(*sort_fct)(const Carte& a,const Carte& b);
//functii pentru sortari


/*Returns true if titlu a  > titlu b
* False elsewhere
*/
int compare_name(const Carte& a, const Carte& b);

/*Returns true if autor a  > autor b
* False elsewhere
*/
int compare_author(const Carte& a, const Carte& b);

/*Returns true if gen a  > gen b
* False elsewhere
*/
int compare_genre(const Carte& a, const Carte& b);

/*Returns true if an a  > an b
* False elsewhere
*/
int compare_year(const Carte& a, const Carte& b);


//functii pentru filtrare

bool right_name(const Carte& a, const string nume);


bool right_year(const Carte& a, const string an);


class Service {
private:
	Repository reposit;
	Validator valid;
public:
	/*Functia de creare, validare si adaugare in repository-ul curent al instantei de service
	* @titlu: string, titlul cartii, string nevid
	* @autor: string, autorul cartii, string nevid
	* @gen: string, genul cartii, string nevid
	* @an: int, anul de publicatie al cartii, -1 < an < 2026
	* returns: -
	* throws: 
	@Erori cu mesaje specifice validatorului:
	-"Titlu invalid\n" - daca titlu este string vid; 
	-"Autor invalid\n" - daca autor este sir vid; 
	-"Gen invalid\n" daca gen este sir vid;
	-"An invalid\n" daca anul este intreg negativ sau nu exista inca(>=2026)
	@Erori cu mesaje specifice repository:
	-"Carte deja existenta\n", daca exista acea carte deja in repository
	*/
	void creaza_valideaza_adauga(const string titlu,const string autor, const string gen,const int an);


	/*Functia care returneaza numarul curent de carti din repository
	* returns: (int) cate carti se afla in repository-ul instantei curente de service
	*/
	int get_repo_size() noexcept;

	/*Functia care returneaza cartea din repository de pe pozitia specificata
	* @poz: int, pozitia din repository
	* returns: (Carte), cartea de pe pozitia poz din repository
	*/
	Carte& get_elem(const int poz);

	/*Functia care cauta o carte cu titlul si autorul specificat
	* @titlu: string, titlul cartii
	* @autor: string, autorul cartii
	* returns: (int) pozitia cartii in repository daca exista, -1 daca nu exista cartea in repository
	*/
	int cauta_carte_repo(const string titlu, const string autor);

	/*Functia de stergere carte din repository-ul instantei de service
	* @titlu: string, titlul cartii
	* @autor: string, autorul cartii
	* throws: Eroare cu mesaj "Carte inexistenta\n", daca nu exista cartea in repository
	*/
	void sterge_carte_repo(const string titlu, const string autor);

	/*Functia de modificare carte din repository-ul instantei de service
	* @titlu: string, titlul cartii
	* @autor: string, autorul cartii
	* @new_carte: Carte, carte cu noile atribute dorite
	* throws: Erori cu mesaje specifice:
	* -"Carte inexistenta\n", daca nu avem carte in repository cu titlul si autorul specificate
	* -"Carte deja existenta\n", daca prin modificarea cartii cu titlu si autor specificat s-ar crea un duplicat in repository
	*/
	void modifica_carte_repo(const string titlu, const string autor, const Carte& new_carte);
	
	MyVector<Carte> get_all();

	/*Functia de sortare dupa un anumit criteriu
	* cmp - functie de compararare
	* descrescator - ordinea in care se vor ordona elementele : crescator(false) sau descrescator(true)
	* returns: un vector(MyVector) cu elementele sortate
	*/
	MyVector<Carte> sort(sort_fct cmp, const int descrescator);


	/*Functia de filtrare dupa un anumit criteriu
	* filtru - functia de filtrare
	* what - criteriul de filtrare, trust me bro
	* returns: un vector(MyVector) cu elementele care 
	*/
	MyVector<Carte> filter(fltr_fct filtru, const string what);
};