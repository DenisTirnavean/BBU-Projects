#include "UI.h"

void Consola::add()
{
	cout << "===========================================\n";
	cout << "||              ADAUGARE		||\n";
	cout << "===========================================\n\n";
	int an;
	string titlu, autor, gen, an_str;

	cout << "Titlul cartii: ";
	getline(cin, titlu);
	cout << "Autorul cartii: ";
	getline(cin, autor);
	cout << "Genul cartii: ";
	getline(cin, gen);
	cout << "Anul aparitiei: ";
	cin >> an_str;
	cin.get();
	try {
		an = stoi(an_str);
	}
	catch (exception)
	{
		cout << "\nAi vrut sa strici aplicatia :(\n\n";
		return;
	}
	this->service.creaza_valideaza_adauga(titlu, autor, gen, an);
	cout << "\nCarte adaugata cu succes!!!\n\n";
}
void Consola::print_elem(const Carte& carte) const
{
	cout << "{TITLU}: " << carte.get_titlu() << "		" << "{AUTOR}: " << carte.get_autor() << "		" << "{GEN}" << carte.get_gen() << "		" << "{AN}: " << carte.get_an() << endl;
}
void Consola::show()
{
	cout << "===========================================\n";
	cout << "||                AFISARE                 ||\n";
	cout << "===========================================\n\n";
	if (service.get_repo_size() == 0)
		cout << "\nLista este goala, nimic de afisat inca\n\n";
	else {
		for (int i = 0; i < service.get_repo_size(); i++)
		{
			const Carte& carte = service.get_elem(i);
			print_elem(carte);
		}
		cout << endl;
	}
}
void Consola::print_meniu()
{
	cout<<"Bine ati venit in Biblioteca!!\n";
	cout << "Optiuni disponibile:\n";
	cout << "0. EXIT\n";
	cout << "1. Adauga carte\n";
	cout << "2. Afiseaza inventarul\n";
	cout << "3. Cauta carte dupa titlu si autor\n";
	cout << "4. Sterge carte\n";
	cout << "5. Modificare carte\n";
	cout << "6. Filtrare dupa titlu sau anul aparitiei\n";
	cout << "7. Sortare dupa orice criteriu\n>>>";
}
void Consola::sterge()
{
	cout << "===========================================\n";
	cout << "||                STERGERE               ||\n";
	cout << "===========================================\n\n";
	string titlu, autor;
	cout << "Titlul cartii pe care vrei sa o stergi: ";
	getline(cin, titlu);
	cout << "Autorul cartii pe care vrei sa o stergi: ";
	getline(cin, autor);
	service.sterge_carte_repo(titlu,autor);
	cout << "\nCarte stearsa cu succes!!\n\n";
}
void Consola::cauta()
{
	cout << "===========================================\n";
	cout << "||                CAUTARE               ||\n";
	cout << "===========================================\n\n";
	string titlu, autor;
	cout << "Titlul cartii cautate: ";
	getline(cin, titlu);
	cout << "Autorul cartii cautate: ";
	getline(cin, autor);
	const int poz=service.cauta_carte_repo(titlu, autor);
	if (poz == -1)
	{
		cout << "\nNu exista cartea cautata!!!\n\n";
	}
	else
	{
		cout << "\nCartea cautata este: ";
		const Carte& carte = service.get_elem(poz);
		print_elem(carte);
		cout << endl;
	}


}
void Consola::modifica()
{
	cout << "===========================================\n";
	cout << "||                MODIFICA              ||\n";
	cout << "===========================================\n\n";
	string titlu, autor;
	cout << "Titlul cartii pe care vrei sa o modifici: ";
	getline(cin, titlu);
	cout << "Autorul cartii pe care vrei sa o modifici: ";
	getline(cin, autor);
	service.cauta_carte_repo(titlu, autor);
	string n_titlu, n_autor, n_gen;
	int an;
	cout << "Titlul modificat: ";
	getline(cin, n_titlu);
	cout << "Autorul modificat: ";
	getline(cin, n_autor);
	cout << "Genul modificat: ";
	getline(cin, n_gen);
	cout << "Anul modificat: ";
	string an_str;
	cin >> an_str;
	cin.get();
	try {
		an = stoi(an_str);
	}
	catch (exception)
	{
		cout << "\nAi vrut sa strici aplicatia :(\n\n";
		return;
	}
	Carte new_carte = Carte(n_titlu, n_autor, n_gen, an);
	service.modifica_carte_repo(titlu, autor, new_carte);
	cout << "\nModificare facuta cu succes!\n\n";
}
void Consola::filtreaza()
{

	cout << "===========================================\n";
	cout << "||                FILTREAZA            ||\n";
	cout << "===========================================\n\n";
	cout << "Criteriul dupa care filtrezi?\n";
	cout << "<1> Anumit nume\n";
	cout << "<2> Anumit an de aparitie\n>>>";
	int crt;
	string nume,an;
	cin >> crt;
	if (crt > 2 || crt < 1)
		cout << "Comanda invalida\n\n";
	else {
		switch (crt) {
		case 1:
		{
			cout << "Numele cartii: ";
			cin >> nume;
			MyVector<Carte> rez = this->service.filter(right_name, nume);
			if (rez.size() == 0)
				cout << "Filtrarea nu a reusit!!\n\n";
			else {
				cout << "Rezultatele filtrarii:\n";
				auto it = rez.begin();
				while (it.valid())
				{
					print_elem(it.element());
					it.next();
				}
			}
			break;
		}
		case 2:
		{
			cout << "Anul aparitiei: ";
			cin >> an;
			MyVector<Carte> rez = this->service.filter(right_year, an);
			if (rez.size() == 0)
				cout << "Filtrarea nu a reusit!!\n\n";
			else {
				cout << "Rezultatele filtrarii:\n";
				auto it = rez.begin();
				while (it.valid())
				{
					print_elem(it.element());
					it.next();
				}
			}
			break;
		}
		}
	}
}
void sort_meniu()
{
	cout << "SORTARE DUPA CRITERIU:\n";
	cout << "<1> Titlu\n";
	cout << "<2> Autor\n";
	cout << "<3> Gen\n";
	cout << "<4> An aparitie\n>>>";
}
void Consola::sorteaza()
{

	cout << "===========================================\n";
	cout << "||                SORTEAZA              ||\n";
	cout << "===========================================\n\n";
	sort_meniu();
	int crt;
	bool descrescator;
	string criteriu;
	cin >> crt;
	if (crt > 4 || crt < 1) {
		cout << "Comanda invalida!\n\n";
	}
	else {
		cout << "<0> Crescator      <1>Descrescator\n>>>";
		cin >> descrescator;
		MyVector<Carte> rez;
		switch (crt)
		{
		case 1:
		{
			rez = this->service.sort(compare_name,descrescator);
			break;
		}
		case 2:
		{
			rez = this->service.sort(compare_author, descrescator);
			break;
		}
		case 3:
		{
			rez = this->service.sort(compare_genre, descrescator);
			break;
		}
		case 4:
		{
			rez = this->service.sort(compare_year, descrescator);
			break;
		}
		default:
			break;
		}
		if (rez.size() == 0)
			cout << "Lista goala!!\n\n";
		else {
			cout << "Rezultatele sortarii:\n";
			auto it = rez.begin();
			while (it.valid())
			{
				print_elem(it.element());
				it.next();
			}
		}
	}
}
void Consola::run()
{
	string command;
	int cmd=0,ok=1;
	while (ok)
	{
		print_meniu();
		try
		{
			cin >> command;
			cin.get();
			cmd = stoi(command);
		}
		catch (exception&) {
			cout << "\n\nLasa vrajeala! scrie un numar ca ma supar\n";
			cmd = 101;
		}
		switch (cmd)
		{
		case 0:
			cout << "BYEEEEE\n";
			ok = 0;
			break;
			
		case 1:
			try {
				add();
			}
			catch (const exception& e)
			{
				cout << "ERRORS:   " << e.what()<<endl<<endl;
			}
			break;
		case 2:
			show();
			break;
		case 3:
			cauta();
			break;
		case 4:
			try
			{
				sterge();

			}
			catch (const exception& e)
			{
				cout << "\nEroare: " << e.what() << endl;
			}
			break;
		case 5:
			try
			{
				modifica();
				
			}
			catch (const exception& e)
			{
				cout << "Eroare: " << e.what();
			}
			
			break;
		case 6:
			filtreaza();
			break;
		case 7:
			sorteaza();
			break;
		default:
			cout << "Comanda invalida\n";
			break;
		}
		


	}
}