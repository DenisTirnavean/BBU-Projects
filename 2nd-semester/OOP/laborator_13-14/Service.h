#pragma once
#include "Repository.h"
#include "Validator.h"
#include "UndoAct.h"
#include <algorithm>
#include "Observer.h"
#include "Cos.h"
typedef bool(*fltr_fct)(const Carte& a, const string atribut);
typedef bool(*sort_fct)(const Carte& a, const Carte& b);
//functii pentru sortari


/*Returns true if titlu a  > titlu b
* False elsewhere
*/
bool compar_nume(const Carte& a, const Carte& b);

/*Returns true if autor a  > autor b
* False elsewhere
*/
bool compar_autor(const Carte& a, const Carte& b);

/*Returns true if gen a  > gen b
* False elsewhere
*/
bool compar_gen(const Carte& a, const Carte& b);

/*Returns true if an a  > an b
* False elsewhere
*/
bool compar_an(const Carte& a, const Carte& b);


//functii pentru filtrare

bool right_name(const Carte& a, const string nume);


bool right_year(const Carte& a, const string an);


class Service:public Observable{
private:
	Repository_abstract* reposit;
	Cos cosulet;
	Validator valid;
	vector<unique_ptr<ActUndo>> undo_act;

public:

	Service(Repository_abstract* r) :reposit{ r } {
		undo_act.clear();
	}

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
	void creaza_valideaza_adauga(const string titlu, const string autor, const string gen, const int an);


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

	/*Functie care returneaza toate elementele din repository
	*/
	vector<Carte>& get_all() noexcept;

	/*Functia de sortare dupa un anumit criteriu
	* cmp - functie de compararare
	* descrescator - ordinea in care se vor ordona elementele : crescator(false) sau descrescator(true)
	* returns: un vector(MyVector) cu elementele sortate
	*/
	vector<Carte> sort(sort_fct cmp, const bool descrescator);


	/*Functia de filtrare dupa un anumit criteriu
	* filtru - functia de filtrare
	* what - criteriul de filtrare, trust me bro
	* returns: un vector(MyVector) cu elementele care
	*/
	vector<Carte> filter(fltr_fct filtru, const string what);

	/*Functie care returneaza numarul de carti din cosul de inchirieri
	*/
	int how_many_basket() const;

	/*Functie care genereaza o configuratie random de cos de inchirieri
	*/
	void generate(const int cate);

	/*Functie care adauga in cos de inchieri o carte specificata
	* throws: BasketException daca nu regasim carte in repository-ul instantei curent de service
	*/
	void adauga_in_cos(const string& titlu, const string& autor);

	/*Functie care goleste cosul de inchirieri
	*/
	void empty_cos() noexcept;

	/*Functie care salveaza continutul cosului intr-un fisier specificat
	*/
	void save_cos(const string& file_name);

	/*Functie de get all pentru continut cos
	*/
	vector<Carte>& get_cos() noexcept;

	/*Functia care reface ultima actiune efectuata asupra elementelor din repository
	* aduce elementele din repository la o starea anterioara
	* throws: ServiceException cu mesaj "Undo invalid\n" daca nu avem operatii de refacut
	*/
	void serv_undo();

};