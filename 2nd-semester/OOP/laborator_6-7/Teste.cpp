
#include "Service.h"
#include "Teste.h"
#include <assert.h>
#include <iostream>
#include "MyList.h"


/// <summary>
/// TESTE DOMAIN
/// </summary>
void test_creaza() {
	//cu parametrii
	Carte carte = Carte("Analiza Matematica pentru informaticieni", "Berinde Stefan","Horror", 1988);
	assert(carte.get_autor() == "Berinde Stefan");
	assert(carte.get_gen() == "Horror");
	assert(carte.get_an() == 1988);
	assert(carte.get_titlu() == "Analiza Matematica pentru informaticieni");
	//fara parametrii
	Carte carte2;
	assert(carte2.get_autor() == "");
	assert(carte2.get_gen() == "");
	assert(carte2.get_an() == 0);
	assert(carte2.get_titlu() == "");
}
void test_operator_copiere()
{
	Carte carte = Carte("Analiza Matematica pentru informaticieni", "Berinde Stefan", "Horror", 1988);
	Carte carte2;
	carte2 = carte;
	carte = carte;

}
void test_setters()
{
	Carte carte = Carte("Amintiri din copilarie", "Creanga","biografie", 1878);
	assert(carte.get_autor() == "Creanga");
	assert(carte.get_an() == 1878);
	assert(carte.get_titlu() == "Amintiri din copilarie");
	carte.set_an(2002);
	assert(carte.get_an() == 2002);
	carte.set_autor("Gigel");
	assert(carte.get_autor() =="Gigel");
	carte.set_titlu("Amintiri");
	assert(carte.get_titlu() == "Amintiri");
	carte.set_gen("comedie");
	assert(carte.get_gen() == "comedie");
}
void test_validator()
{
	Validator valid;
	//caz valid
	valid.valideaza_carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
	//caz titlu invalid
	try {
		valid.valideaza_carte("", "Creanga", "biografie", 1878);
		assert(false);
	}
	catch (const std::exception& /*e*/)
	{
		//assert(strcmp(e.what(), "Titlu invalid\n") == 0);
		assert(true);
	}
	//caz autor invalid
	try {
		valid.valideaza_carte("Amintiri din copilarie", "", "biografie", 1878);
		assert(false);
	}
	catch (const std::exception& e)
	{

		assert(strcmp(e.what(), "Autor invalid\n") == 0);
	}
	//caz gen invalid
	try {
		valid.valideaza_carte("Amintiri din copilarie", "Creanga", "", 1878);
		assert(false);
	}
	catch (const std::exception&/*e*/)
	{
		//assert(strcmp(e.what(), "Gen invalid\n") == 0);
		assert(true);
	}
	//caz an invalid
	try {
		valid.valideaza_carte("Amintiri din copilarie", "Creanga", "biografie", 2026);
		assert(false);
	}
	catch (const std::exception& e)
	{
		if (e.what() != nullptr)
			assert(strcmp(e.what(), "An invalid\n") == 0);
	}
	//caz full option
	try {
		valid.valideaza_carte("", "", "", 2026);
		assert(false);
	}
	catch (const std::exception& e)
	{
		if (e.what() != nullptr)
			assert(strcmp(e.what(), "Titlu invalid\nAutor invalid\nGen invalid\nAn invalid\n") == 0);
	}

}
void Tester::test_domain() {
	test_creaza();
	test_setters();
	test_validator();
	test_operator_copiere();
}



/// <summary>
/// TESTE REPOSITORY
/// </summary>
void test_operatori()
{
	Repository repo;
	Repository repo2;
	repo = repo2;
	Repository repo3 = repo;
	repo = repo;
}
void test_adauga_get()
{
	Repository repo;
	Carte carte = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
	repo.adauga(carte);
	assert(repo.get_size() == 1);

	assert(repo.get_carte(0).get_titlu() == carte.get_titlu());
	assert(repo.get_carte(0).get_autor() == carte.get_autor());
	assert(repo.get_carte(0).get_gen() == carte.get_gen());
	assert(repo.get_carte(0).get_an() == carte.get_an());
	try
	{
		repo.adauga(carte);
		assert(false);
	}
	catch (const exception& e)
	{
		if (e.what() != nullptr)
			assert(strcmp(e.what(), "Carte deja existenta\n") == 0);
	}
	Carte carte1 = repo.get_carte(0);
	Carte carte2;
	carte2 = repo.get_carte(0);
}
void test_cauta()
{
	Repository repo;
	Carte carte = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
	repo.adauga(carte);
	assert(repo.get_size() == 1);
	int poz = repo.cauta_carte("Amintiri din copilarie", "Creanga");
	assert(poz == 0);
	assert(repo.get_carte(poz).get_gen() == "biografie");
	assert(repo.get_carte(poz).get_an() == 1878);
	poz = repo.cauta_carte("Analiza matematica", "Berinde");
	assert(poz == -1);
	

}
void test_sterge_din_repo()
{
	Repository repo;
	Carte carte = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
	repo.adauga(carte);
	repo.sterge_carte(carte);
	assert(repo.get_size() == 0);
	try {
		repo.sterge_carte(carte);
		assert(false);
	}
	catch (const exception& e)
	{
		if (e.what() != nullptr)
		assert(strcmp(e.what(), "Carte inexistenta\n") == 0);
	}

}
void test_get_all_repo()
{
	Repository repo;
	Carte carte = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
	repo.adauga(carte);
	carte = Carte("Amintiri", "Creanga", "biografie", 1878);
	repo.adauga(carte);
	carte = Carte("copilarie", "Creanga", "biografie", 1878);
	repo.adauga(carte);
	assert(repo.get_size() == 3);
	MyVector<Carte> bibi = repo.get_elems();
	assert(bibi.size() == repo.get_size());
	
}
void Tester::test_repository() {
	test_operatori();
	test_adauga_get();
	test_cauta();
	test_sterge_din_repo();
	test_get_all_repo();
}


/// <summary>
/// TESTE SERVICE
/// </summary>

//cva = creaza_valideaza_adauga lmao
void test_cva()
{
	Service serv;
	//cazul okay
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "biografie", 1878);
	assert(serv.get_repo_size() == 1);
	//cazuri cu erori de validare
	//caz titlu invalid
	try {
		serv.creaza_valideaza_adauga("", "Creanga", "biografie", 1878);
		assert(false);
	}
	catch (const std::exception& e)
	{
		if (e.what() != nullptr)
		assert(strcmp(e.what(), "Titlu invalid\n") == 0);
	}
	//caz autor invalid
	try {
		serv.creaza_valideaza_adauga("Amintiri din copilarie", "", "biografie", 1878);
		assert(false);
	}
	catch (const std::exception& e)
	{
		if (e.what() != nullptr)
		assert(strcmp(e.what(), "Autor invalid\n") == 0);
	}
	//caz gen invalid
	try {
		serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "", 1878);
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(strcmp(e.what(), "Gen invalid\n") == 0);
	}
	//caz an invalid
	try {
		serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "biografie", 2026);
		assert(false);
	}
	catch (const std::exception& e)
	{
		if (e.what() != nullptr)
		assert(strcmp(e.what(), "An invalid\n") == 0);
	}
	//caz full option
	try {
		serv.creaza_valideaza_adauga("", "", "", 2026);
		assert(false);
	}
	catch (const std::exception& e)
	{
		if (e.what() != nullptr)
		assert(strcmp(e.what(), "Titlu invalid\nAutor invalid\nGen invalid\nAn invalid\n") == 0);
	}
	assert(serv.get_repo_size() == 1);
	serv.creaza_valideaza_adauga("Analiza Matematica pentru informaticieni", "Berinde Stefan", "Horror", 1988);
	assert(serv.get_repo_size() == 2);
}

void test_get_element()
{
	Service serv;
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "biografie", 1878);
	assert(serv.get_repo_size() == 1);
	Carte carte = serv.get_elem(0);
	assert(carte.get_titlu() == "Amintiri din copilarie");
	assert(carte.get_autor() == "Creanga");
	assert(carte.get_gen() == "biografie");
	assert(carte.get_an() == 1878);
}
void test_cauta_carte()
{
	Service serv;
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "biografie", 1878);
	assert(serv.get_repo_size() == 1);
	int ok= serv.cauta_carte_repo("Amintiri din copilarie", "Creanga");
	assert(ok == 0);
	ok = serv.cauta_carte_repo("Analiza matematica", "Berinde");
	assert(ok == -1);
}
void test_sterge()
{
	Service serv;
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "biografie", 1878);
	assert(serv.get_repo_size() == 1);
	serv.sterge_carte_repo("Amintiri din copilarie", "Creanga");
	assert(serv.get_repo_size() == 0);
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "biografie", 1878);
	try {
		serv.sterge_carte_repo("Analiza Matematica pentru informaticieni", "Berinde Stefan");
		assert(false);
	}
	catch (const exception& e)
	{
		if (e.what() != nullptr)
		assert(strcmp(e.what(), "Carte inexistenta\n") == 0);
	}
}
void test_get_all_srv()
{
	Service serv;
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "biografie", 1878);
	serv.creaza_valideaza_adauga("Analiza Matematica pentru informaticieni", "Berinde Stefan", "horror", 2003);
	assert(serv.get_repo_size() == 2);
	MyVector<Carte> bibi = serv.get_all();
	assert(bibi.size() == 2);

}
void test_modifica()
{

	Service serv;
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "biografie", 1878);
	Carte new_carte = Carte("Analiza Matematica pentru informaticieni", "Berinde Stefan", "horror", 2003);
	serv.modifica_carte_repo("Amintiri din copilarie", "Creanga", new_carte);
	assert(serv.get_elem(0).get_titlu() == "Analiza Matematica pentru informaticieni");
	assert(serv.get_elem(0).get_autor() == "Berinde Stefan");
	assert(serv.get_elem(0).get_gen() == "horror");
	assert(serv.get_elem(0).get_an() == 2003);
	//caz inexistenta
	try
	{
		serv.modifica_carte_repo("Amintiri din copilarie", "Creanga", new_carte);
		assert(false);
	}
	catch (const exception& e)
	{
		if (e.what() != nullptr)
		assert(strcmp(e.what(), "Carte inexistenta\n") == 0);
	}
	//caz duplicare
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "biografie", 1878);
	try
	{
		serv.modifica_carte_repo("Amintiri din copilarie", "Creanga", new_carte);
		assert(false);
	}
	catch (const exception& e)
	{
		if (e.what() != nullptr)
		assert(strcmp(e.what(), "Carte deja existenta\n") == 0);
	}
}

void test_filtru()
{
	Service serv;

	serv.creaza_valideaza_adauga("zebra", "q", "biografie", 2002);
	serv.creaza_valideaza_adauga("flore", "a", "komedie", 32);
	serv.creaza_valideaza_adauga("cucuruz", "m", "comedie", 2);
	serv.creaza_valideaza_adauga("banana", "i", "rave party 1989", 7);
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "demisie", 6);
	serv.creaza_valideaza_adauga("Analiza matematica", "Creanga", "dictionar", 3);
	serv.creaza_valideaza_adauga("jocuri", "p", "baubau", 1);
	serv.creaza_valideaza_adauga("caramel", "z", "biografie", 90);
	serv.creaza_valideaza_adauga("denis", "n", "anarchy", 1878);
	serv.creaza_valideaza_adauga("mod", "denis", "carte de sah", 97);

	MyVector<Carte> rez = serv.filter(right_name,"zebra");
	assert(rez.at(0).get_titlu() == "zebra");
	assert(rez.at(0).get_autor() == "q");
	assert(rez.at(0).get_gen() == "biografie");
	assert(rez.at(0).get_an() == 2002);
	
	rez = serv.filter(right_year, "1878");
	assert(rez.size() == 1);
	assert(rez.at(0).get_titlu() == "denis");
	assert(rez.at(0).get_autor() == "n");

}

void test_sort()
{
	Service serv;

	serv.creaza_valideaza_adauga("zebra", "q", "biografie", 2002);
	serv.creaza_valideaza_adauga("flore", "a", "komedie", 32);
	serv.creaza_valideaza_adauga("cucuruz", "m", "comedie", 2);
	serv.creaza_valideaza_adauga("banana", "i", "rave party 1989",7);
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "demisie", 6);
	serv.creaza_valideaza_adauga("Analiza matematica", "Creanga", "dictionar", 3);
	serv.creaza_valideaza_adauga("jocuri", "p", "baubau", 1);
	serv.creaza_valideaza_adauga("caramel", "z", "biografie", 90);
	serv.creaza_valideaza_adauga("denis", "n", "anarchy", 1878);
	serv.creaza_valideaza_adauga("mod", "denis", "carte de sah", 97);
	/*
	serv.creaza_valideaza_adauga("c", "denis", "carte de sah", 1878);
	serv.creaza_valideaza_adauga("b", "denis", "carte de sah", 1878);
	serv.creaza_valideaza_adauga("a", "denis", "carte de sah", 1878);
	*/

	//primul tip de sortare my dear grasshoper
	{
		const MyVector<Carte>& sorted = serv.sort(compare_name, 0);
		assert(sorted.at(9).get_titlu() == "zebra");
	}
	{
		const MyVector<Carte>& sorted = serv.sort(compare_name, 1);
		assert(sorted.at(9).get_titlu() == "Amintiri din copilarie");
	}
	//al doilea tip de sortare
	{
		const MyVector<Carte>& sorted = serv.sort(compare_author, 0);

		assert(sorted.at(0).get_autor() == "Creanga");
	}
	{
		const MyVector<Carte>& sorted = serv.sort(compare_name, 1);
		assert(sorted.at(9).get_autor() == "Creanga");
	}
	{

		//al treilea tip de sortare
		const MyVector<Carte>& sorted = serv.sort(compare_genre, 0);

		assert(sorted.at(0).get_gen() == "anarchy");
	}
	{
		const MyVector<Carte>& sorted = serv.sort(compare_genre, 1);
		assert(sorted.at(9).get_gen() == "anarchy");
	}


	//al patrulea tip de sortare
	{
		const MyVector<Carte>& sorted = serv.sort(compare_year, 0);

		assert(sorted.at(0).get_an() == 1);
	}
	{
		const MyVector<Carte>& sorted = serv.sort(compare_year, 1);
		assert(sorted.at(9).get_an() == 1);
	}
}
void Tester::test_service() {
	test_cva();
	test_get_element();
	test_cauta_carte();
	test_sterge();
	test_modifica();
	test_get_all_srv();
	test_filtru();
	test_sort();
}

///Teste vector dinamic
void test_vector()
{
	MyVector<Carte> repo;
	Carte carte = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
	///test push_back() + at()
	repo.push_back(carte);
	assert(repo.size() == 1);

	assert(repo.at(0).get_titlu() == carte.get_titlu());
	assert(repo.at(0).get_autor() == carte.get_autor());
	assert(repo.at(0).get_gen() == carte.get_gen());
	assert(repo.at(0).get_an() == carte.get_an());

	Carte carte1 = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
	repo.push_back(carte1);
	assert(repo.size() == 2);

	Carte carte2 = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
	repo.push_back(carte2);
	assert(repo.size() == 3);
	Carte carte3 = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
	repo.push_back(carte3);
	assert(repo.size() == 4);
	Carte carte4 = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
	repo.push_back(carte4);
	assert(repo.size() == 5);
	Carte carte5 = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
	repo.push_back(carte5);
	assert(repo.size() == 6);
	///test erase
	repo.erase(0);
	assert(repo.size() == 5);

	///test iteratori
	auto it = repo.begin();
	int poz = 0;
	while (it.valid())
	{
		assert(it.element() == repo.at(poz++));
		it.next();
	}
	MyVector<Carte> repo2 = repo;
	MyVector<Carte> repo3{ repo };
	MyVector<Carte> repo4;
	repo4 = repo3;
	MyVector<Carte> repo5{ repo4 };
	std::vector<MyVector<Carte>> v;
	v.push_back(MyVector<Carte>{});

}
///

/// <summary>
/// TESTER FINAL BOSS
/// </summary>
void Tester::test_all() {
	test_domain();
	test_repository();
	test_service();
	test_vector();
}
