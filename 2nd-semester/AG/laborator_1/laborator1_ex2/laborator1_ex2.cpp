//cerinta 2
/*
* 2. Fie un graf reprezentat sub o anumita forma (graful este citit dintr-un fisier). Sa se rezolve:
a. sa se determine nodurile izolate dintr-un graf.
b. sa se determine daca graful este regular.
	(toate varfurile acelasi grad)
c. pentru un graf reprezentat cu matricea de adiacenta sa se determine matricea distantelor.
	(matrice cu distanta, lungimea drumului cel mai scurt dintre nodurile i si j)
d. pentru un graf reprezentat cu o matrice de adiacenta sa se determine daca este conex.
	(exista drum intre oricare 2 noduri)
*/
#include <iostream>
#include <fstream>
using namespace std;

int vector[100], c[100],matrice_distante[100][100];
/*Functia de cautare a primului varf nevizitat din graf
* args: vector - un vector binar care memoreaza daca nodul a fost vizitat ,noduri - nr noduri
* returns: primul nod nevizitat (int) sau 0 daca nu exista
*/
int unvisited(int vector[100], int noduri)
{
	for (int i = 1; i <= noduri; i++)
		if (vector[i] == 0)
			return i;
	return 0;
}
/*Functia de parcurgere in latime a unui graf
* args: matrice - matricea de adiacenta, noduri - numarul de noduri din graf, ns - nodul sursa( de unde incepe parcurgerea)
*/
void breadthfirst(int matrice[][100],int noduri, int ns)
{
	int distanta[100] = { 0 }, prim, ultim;
	vector[ns] = 1;
	prim = ultim = 1;
	c[ultim] = ns;
	distanta[ns] = 1;
	while (prim <= ultim)
	{
		for(int i=1;i<=noduri;i++)
			if(matrice[c[prim]][i]==1 && distanta[i]==0)
				{
					ultim++;
					c[ultim] = i;
					vector[i] = 1;
					distanta[i] = distanta[c[prim]] + 1;
				}
		prim++;
	}
	for (int i = 1; i <= ultim; i++)
		matrice_distante[ns][c[i]]=distanta[c[i]] - 1;

}
/*Functia de initializare matrice a distantelor
*/
void init_mat_distante(int mat[][100], int noduri)
{
	for (int i = 1; i <= noduri; i++)
		for (int j = 1; j <= noduri; j++)
			mat[i][j] = -1;
	
}
/*Functia de tiparire matrice patratica
* args: mat - matrice patratica de noduri linii noduri coloane, noduri-dimensiunea matricei
* returns: -
*/
void afisare_matrice(int mat[][100], int noduri)
{
	for (int i = 1; i <= noduri; i++)
	{
		for (int j = 1; j <= noduri; j++)
			if (mat[i][j] == -1)
				cout << "# ";
			else
				cout << mat[i][j] << " ";
		cout << "\n";
	}
}
int main()
{
	int noduri,matrice[100][100]={0}, grad, degree, varfuri_izolate[100]={0}, index=0;
	bool regular = 1;
	fstream f("C:/Users/Denis/Desktop/AG/laborator1_ex2/in.txt");
	f >> noduri;
	init_mat_distante(matrice_distante, noduri);
	for (int i = 1; i <= noduri; i++)
	{
		degree = 0; 
		for (int j = 1; j <= noduri; j++)
		{
			f >> matrice[i][j];
			degree += matrice[i][j];
		}
		//subpunct a
		if (degree == 0) varfuri_izolate[++index] = i; //grad=0 => varf izolat
		//subpunct b
		if (i == 1)
			grad = degree;//luam gradul primul varf ca referinta pentru restul gradelor
		else
			if (grad != degree)
				regular = 0;//daca gasim doua varfuri cu grade diferite => graful nu e regular
	}
	//subpunct a
	if (index == 0)
		cout << "a)Nu exista varfuri izolate in graf\n\n";
	else
	{
		cout << "a)Varfurile izolate sunt: ";
		for (int i = 1; i <=index; i++)
			cout << varfuri_izolate[i] << " ";
		cout << "\n\n";
	}
	//subpunct b
	if (regular != 1)
		cout << "b)Graful nu este regular\n\n";
	else cout << "b)Graful este regular\n\n";

	//subpunct c + d
	bool conditie_conex = 1;
	for (int i = 1; i <= noduri; i++)
		for (int j = 1; j <= noduri; j++)
			matrice_distante[i][j] = -1;
	for (int i = 1; i <= noduri; i++)
	{
		breadthfirst(matrice, noduri, i);
		//daca nu am parcurs tot graful( varfuri nevizitate ) atunci nu este conex
		if (unvisited(vector, noduri) != 0)
			conditie_conex = 0;
	}
	cout << "c)Matricea distantelor este: \n";
	afisare_matrice(matrice_distante, noduri);
	cout << endl;
	//subpunctul d
	if (conditie_conex)
		cout << "d)Graful este conex\n\n";
	else cout << "d)Graful nu este conex\n\n";
	f.close();
	return 0;
}