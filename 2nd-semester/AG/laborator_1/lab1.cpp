//cerinta_1
/*
1. Fie un fisier ce contine un graf neorientat reprezentat sub forma : 
prima linie contine numarul nodurilor iar urmatoarele randuri muchiile grafului.
Sa se scrie un program in C / C++ care sa citeasca fisierul si sa reprezinte / stocheze un graf folosind
matricea de adiacenta, lista de adiacenta si matricea de incidenta.Sa se converteasca un graf dintr - o forma de 
reprezentare in alta.

Fisier->matrice de adiacenta->lista adiacenta->matrice de incidenta->lista adiacenta->matrice de adiacenta->lista.

exemplu fisier
in.txt
4
1 2
3 4
2 3
4 2
*/
#include <iostream>
#include <fstream>
using namespace std;
void print_matrice(int matrix[][100], int lines, int rows)
{
	/*Functie de afisare pe ecran a unei matrice cu dimensiunile lines si rows
	*/
	for (int i = 1; i <= lines; i++)
	{
		for (int j = 1; j <= rows; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}
//afiseaza lista adiacenta direct din matricea de adiacenta
void print_l_adiacenta(int matrix[][100], int nr_noduri)
{
	for (int i = 1; i <= nr_noduri; i++)
	{
		cout << i << ": ";
		for (int j = 1; j <= nr_noduri; j++)
			if (matrix[i][j])
				cout << j << " ";
		cout << endl;
	}

}
void print_lista(int lista[][100], int noduri, int vector[100])
{
	/*Functie care afiseaza pe ecran lista de adiacenta
	* noduri= numarul de noduri al grafului
	* vector= vector in care stocam pentru fiecare nod i cu cate varfuri este adiacent
	*/
	for (int i = 1; i <= noduri; i++)
	{
		cout << i << ": ";
		for (int j = 0; j < vector[i]; j++)
			cout <<lista[i][j]<<" ";
		cout << endl;
	}
}

int main()
{
	ifstream f("in.txt");
	int matrice_adiacenta[100][100] = { 0 }, lista_adiacenta[100][100], vector_numarare[100] = { 0 }, matrice_incidenta[100][100] = { 0 };
	int noduri, muchii,nod_1,nod_2;
	f >> noduri >> muchii;
	int index = 1;
	for (int i = 1; i <= muchii; i++)
	{
		f >> nod_1 >> nod_2;
		//matricea de adiacenta
		matrice_adiacenta[nod_1][nod_2] = 1;
		matrice_adiacenta[nod_2][nod_1] = 1;
		//lista de adiacenta
		lista_adiacenta[nod_1][vector_numarare[nod_1]++] = nod_2;
		lista_adiacenta[nod_2][vector_numarare[nod_2]++] = nod_1;
		//matricea de incidenta
		matrice_incidenta[nod_1][index] = 1;
		matrice_incidenta[nod_2][index] = 1;
		index++;

	}
	cout << "Matrice adiacenta: \n";
	print_matrice(matrice_adiacenta, noduri, noduri);
	cout << "\n\n\n\nLista de adiacenta:\n";
	//print_l_adiacenta(matrice_adiacenta, noduri);
	print_lista(lista_adiacenta, noduri, vector_numarare);
	cout << "\n\n\n\nMatrice de incidenta: \n";
	print_matrice(matrice_incidenta,noduri,muchii);
	return 0;
}