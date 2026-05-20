
#include "Service.h"
#include "Teste.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include "Cos.h"



/// <summary>
/// TESTE DOMAIN
/// </summary>
void test_creaza() {
	//cu parametrii
	Carte carte = Carte("Analiza Matematica pentru informaticieni", "Berinde Stefan", "Horror", 1988);
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
	Carte carte3 = Carte("Analiza Matematica pentru informaticieni", "Berinde Stefan", "Horror", 1988);
	assert(carte == carte3);
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
	Carte carte = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
	assert(carte.get_autor() == "Creanga");
	assert(carte.get_an() == 1878);
	assert(carte.get_titlu() == "Amintiri din copilarie");
	carte.set_an(2002);
	assert(carte.get_an() == 2002);
	carte.set_autor("Gigel");
	assert(carte.get_autor() == "Gigel");
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
	Carte& carte1 = repo.get_carte(0);
	(void)carte1;
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
	bool ok = repo.cauta("Amintiri din copilarie", "Creanga");
	assert(ok == true);
	ok = repo.cauta("Analiza matematica", "Berinde");
	assert(ok == false);

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
	vector<Carte>& bibi = repo.get_elems();
	assert(bibi.size() == repo.get_size());

}
void test_new_repo()
{
	{
		Repository_map repo{ 0 };
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
		Carte& carte1 = repo.get_carte(0);
		(void)carte1;
		Carte carte2;
		carte2 = repo.get_carte(0);
	}
	{
		Repository_map repo{ 0 };
		Carte carte = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
		repo.adauga(carte);
		carte = Carte("Amintiri", "Creanga", "biografie", 1878);
		repo.adauga(carte);
		carte = Carte("copilarie", "Creanga", "biografie", 1878);
		repo.adauga(carte);
		assert(repo.get_size() == 3);
		vector<Carte>& bibi = repo.get_elems();
		assert(bibi.size() == repo.get_size());

	}
	{
		Repository_map repo{ 0 };
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
	{
		Repository_map repo{0};
		Carte carte = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
		repo.adauga(carte);
		assert(repo.get_size() == 1);
		int poz = repo.cauta_carte("Amintiri din copilarie", "Creanga");
		assert(poz == 0);
		assert(repo.get_carte(poz).get_gen() == "biografie");
		assert(repo.get_carte(poz).get_an() == 1878);
		poz = repo.cauta_carte("Analiza matematica", "Berinde");
		assert(poz == -1);
		bool ok = repo.cauta("Amintiri din copilarie", "Creanga");
		assert(ok == true);
		ok = repo.cauta("Analiza matematica", "Berinde");
		assert(ok == false);
	}
	{
		Repository_map repo{ 0 };
		Carte carte = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
		repo.adauga(carte);
		assert(repo.get_size() == 1);
		Carte n_carte("Zebra","Darwin","Atlas",2010);
		repo.modifica_carte(0, n_carte);
		assert(repo.get_carte(0).get_titlu() == "Zebra");
		assert(repo.get_carte(0).get_autor() == "Darwin");
		assert(repo.get_carte(0).get_gen() == "Atlas");
		assert(repo.get_carte(0).get_an() == 2010);

	}
	{
		Repository_map repo{ 0 };
		Carte carte = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
		repo.adauga(carte);
		carte = Carte("Amintiri", "Creanga", "biografie", 1878);
		repo.adauga(carte);
		carte = Carte("copilarie", "Creanga", "biografie", 1878);
		repo.adauga(carte);
		Carte n_carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
		try {
			repo.modifica_carte(1, n_carte);
		}
		catch (const RepositoryException&)
		{
			assert(true);
		}
	}
	{
		Repository_map repo{ 1 };
		Carte carte = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
		try {
			repo.adauga(carte);
		}
		catch (const RepositoryException& e)
		{
			assert((string)e.what()=="\n:) guess what\n");
		}
		assert(repo.get_size() == 0);
	}
	{
		Repository_map repo{ 0 };
		Carte carte = Carte("Amintiri din copilarie", "Creanga", "biografie", 1878);
		repo.insert(carte,0);
		assert(repo.get_size() == 1);
	}
}
void Tester::test_repository() {
	test_operatori();
	test_adauga_get();
	test_cauta();
	test_sterge_din_repo();
	test_get_all_repo();
	test_new_repo();
}


/// <summary>
/// TESTE SERVICE
/// </summary>

//cva = creaza_valideaza_adauga lmao
void test_cva()
{
	auto* repo = new Repository;
	Service serv{repo};
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
	delete repo;
}

void test_get_element()
{
	auto* repo = new Repository;
	Service serv{ repo };
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "biografie", 1878);
	assert(serv.get_repo_size() == 1);
	Carte& carte = serv.get_elem(0);
	assert(carte.get_titlu() == "Amintiri din copilarie");
	assert(carte.get_autor() == "Creanga");
	assert(carte.get_gen() == "biografie");
	assert(carte.get_an() == 1878);
	delete repo;
}
void test_cauta_carte()
{
	auto* repo = new Repository;

	Service serv{ repo };
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "biografie", 1878);
	assert(serv.get_repo_size() == 1);
	int ok = serv.cauta_carte_repo("Amintiri din copilarie", "Creanga");
	assert(ok == 0);
	ok = serv.cauta_carte_repo("Analiza matematica", "Berinde");
	assert(ok == -1);
	delete repo;
}
void test_sterge()
{
	auto* repo = new Repository;

	Service serv{repo};
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
	delete repo;
}
void test_get_all_srv()
{
	auto* repo = new Repository;

	Service serv{repo};
	serv.creaza_valideaza_adauga("Amintiri din copilarie", "Creanga", "biografie", 1878);
	serv.creaza_valideaza_adauga("Analiza Matematica pentru informaticieni", "Berinde Stefan", "horror", 2003);
	assert(serv.get_repo_size() == 2);
	const vector<Carte>& bibi = serv.get_all();
	assert(bibi.size() == 2);
	delete repo;
}
void test_modifica()
{
	auto* repo = new Repository;

	Service serv{repo};
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
	delete repo;
}

void test_filtru()
{
	auto* repo = new Repository;
	Service serv{repo};

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
	{
		const vector<Carte>& rez = serv.filter(right_name, "zebra");
		assert(rez.at(0).get_titlu() == "zebra");
		assert(rez.at(0).get_autor() == "q");
		assert(rez.at(0).get_gen() == "biografie");
		assert(rez.at(0).get_an() == 2002);
	}
	const vector<Carte>& rez = serv.filter(right_year, "1878");
	assert(rez.size() == 1);
	assert(rez.at(0).get_titlu() == "denis");
	assert(rez.at(0).get_autor() == "n");
	delete repo;
}

void test_sort()
{
	auto* repo = new Repository;
	Service serv{repo};

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
	/*
	serv.creaza_valideaza_adauga("c", "denis", "carte de sah", 1878);
	serv.creaza_valideaza_adauga("b", "denis", "carte de sah", 1878);
	serv.creaza_valideaza_adauga("a", "denis", "carte de sah", 1878);
	*/

	//primul tip de sortare my dear grasshoper
	vector<Carte>& sorted = serv.sort(compar_nume, 0);
	assert(sorted.at(9).get_titlu() == "zebra");
	sorted = serv.sort(compar_nume, 1);
	assert(sorted.at(9).get_titlu() == "Amintiri din copilarie");
	//al doilea tip de sortare
	sorted = serv.sort(compar_autor, 0);
	assert(sorted.at(0).get_autor() == "Creanga");
	sorted = serv.sort(compar_autor, 1);
	assert(sorted.at(9).get_autor() == "Creanga");
	sorted = serv.sort(compar_autor, 0);

	//al treilea tip de sortare
	sorted = serv.sort(compar_gen, 0);

	assert(sorted.at(0).get_gen() == "anarchy");
	sorted = serv.sort(compar_gen, 1);
	assert(sorted.at(9).get_gen() == "anarchy");


	//al patrulea tip de sortare
	sorted = serv.sort(compar_an, 0);

	assert(sorted.at(0).get_an() == 1);
	sorted = serv.sort(compar_an, 1);
	assert(sorted.at(9).get_an() == 1);
	delete repo;
}
void teste_pt_cos()
{
	auto* repo = new Repository;

	Service serv{repo};

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

	assert(serv.get_repo_size() == 10);
	//adaugare
	serv.adauga_in_cos("zebra", "q");
	serv.adauga_in_cos("denis", "n");
	serv.adauga_in_cos("denis", "n");

	//cate in cos
	assert(serv.how_many_basket() == 3);
	//adaugare invalida
	try
	{
		serv.adauga_in_cos("Florica", "Dansatoarea");
		assert(false);
	}
	catch (const BasketException& e)
	{
		assert(string(e.what()) == "Carte inexistenta!\n");
	}

	//salvare in fisier
	serv.save_cos("teste.txt");

	//golire
	serv.empty_cos();
	assert(serv.how_many_basket() == 0);

	//generare
	serv.generate(100);
	assert(serv.how_many_basket() == 100);

	const vector<Carte>& carticele = serv.get_cos();
	assert(carticele.size() == 100);
	delete repo;
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
	teste_pt_cos();
}
/// <summary>
/// TESTE COS
/// </summary>

void test_genereaza()
{
	Cos new_cos;
	Repository repo_test;
	repo_test.adauga(Carte("Dictionar", "DOOM", "dictionar", 1989));
	repo_test.adauga(Carte("Ion", "Rebreanu", "roman", 1920));
	repo_test.adauga(Carte("Enigma Otiliei", "Calinescu", "roman", 1930));
	repo_test.adauga(Carte("Idiotul", "Dostoievski", "roman", 1950));
	repo_test.adauga(Carte("Crima si pedeapsa", "Dostoievski", "roman", 1989));
	repo_test.adauga(Carte("Moara cu noroc", "Slavici", "nuvela", 1889));

	new_cos.genereaza(5, repo_test.get_elems());
	assert(new_cos.cate_carti() == 5);
}
void test_add()
{
	Cos cosulet;
	cosulet.add_to_cos(Carte("Dictionar", "DOOM", "dictionar", 1989));
	assert(cosulet.cate_carti() == 1);
}
void test_empty()
{
	Cos cosulet;
	cosulet.add_to_cos(Carte("Dictionar", "DOOM", "dictionar", 1989));
	assert(cosulet.cate_carti() == 1);
	cosulet.goleste_cos();
	assert(cosulet.cate_carti() == 0);

}
void test_export()
{
	Cos cosulet;
	cosulet.add_to_cos(Carte("Dictionar", "DOOM", "dictionar", 1989));
	cosulet.add_to_cos(Carte("Ion", "Rebreanu", "roman", 1920));
	cosulet.add_to_cos(Carte("Enigma Otiliei", "Calinescu", "roman", 1930));
	cosulet.add_to_cos(Carte("Idiotul", "Dostoievski", "roman", 1950));
	cosulet.add_to_cos(Carte("Crima si pedeapsa", "Dostoievski", "roman", 1989));
	cosulet.add_to_cos(Carte("Moara cu noroc", "Slavici", "nuvela", 1889));
	cosulet.export_in_fisier("test.txt");
}
void Tester::test_cos()
{
	test_add();
	test_empty();//sau test_mt daca stii cum zic
	test_genereaza();
	test_export();
}

/// <summary>
/// TEST REPOSITORY FISIER
/// </summary>

void init_file() {
	ofstream file("test_only_read.txt");
	file << "Amintiri din copilarie;Creanga;basm;1889;\n";
	file << "Dictionar;DOOM;dictionar;2004;\n";
	file << "Analiza matematica;Berinde;horor;1989;\n";
	file << "Ion;Rebreanu;roman;1920;\n";
	file << "A;b;c;1;\n";
	file << "B;Creanga;basm;1800;\n";
	file << "C;Creanga;comedie;1689;\n";
	file << "D;Creanga;polist;1239;\n";
	file << "A;Denis;horror;50;\n";
	file.close();
}
void teste_fisiere() {
	init_file();
	//populare repo
	{
		Repository_file repo = Repository_file("test_only_read.txt");
		assert(repo.get_size() == 9);
		assert(repo.get_carte(0).get_titlu() == "Amintiri din copilarie");
	}
	//populare fisier
	{
		ofstream fil("test.txt");
		fil << "";
		fil.close();
		Repository_file repo = Repository_file("test.txt");
		repo.adauga(Carte("Dictionar", "DOOM", "dictionar", 1989));
	}
	//update si sterge
	{
		Repository_file repo = Repository_file("test.txt");
		assert(repo.get_size() == 1);
		repo.modifica_carte(0, Carte("A", "B", "C", 69));
		Carte carte = Carte("A", "B", "C", 69);
		repo.sterge_carte(carte);
	}
}



/// <summary>
/// TEST UNDO
/// </summary>
void test_undo_action()
{
	auto* repo = new Repository;

	Service serv{ repo };

	try {
		serv.serv_undo();
		assert(false);
	}
	catch (const ServiceException& e)
	{
		assert((string)e.what() == "Undo invalid\n");
	}
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

	assert(serv.get_repo_size() == 10);
	serv.serv_undo();
	assert(serv.get_repo_size() == 9);
	
	
	serv.sterge_carte_repo("zebra", "q");
	assert(serv.get_repo_size() == 8);
	serv.serv_undo();

	assert(serv.get_repo_size() == 9);
	

	
	Carte carte{ "Carte noua","Eu","bestseller",2025 };
	serv.modifica_carte_repo("zebra", "q", carte);
	assert(serv.cauta_carte_repo("Carte noua", "Eu")!=-1);
	serv.serv_undo();
	assert(serv.cauta_carte_repo("Carte noua", "Eu") == -1);
	delete repo;
}

/// <summary>
/// TESTER FINAL BOSS
/// </summary>
void Tester::test_all() {
	test_domain();
	test_repository();
	test_service();
	test_cos();
	test_undo_action();//doamne ajuta sa mearga

	teste_fisiere();
}
