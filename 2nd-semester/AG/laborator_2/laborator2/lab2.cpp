/*2.2. Sa se determine inchiderea transitiva a unui graf orientat.
(Inchiderea tranzitiva poate fi reprezentata ca matricea care descrie, 
pentru fiecare vârf în parte, care sunt varfurile accesibile din acest varf.
Matricea inchiderii tranzitive arata unde se poate ajunge din fiecare varf.)
ex. figura inchidere_tranzitiva.png - pentru graful de sus se construieste matricea de jos
care arata inchiderea tranzitiva.

*/

#include <iostream>
#include <queue>
#include <fstream>


using namespace std;

ifstream f("C:/Users/Denis/Desktop/AG/02_laborator/grafuri.txt");

vector<int> Adj[100];

int matrice[100][100];


/*
void Moore(int matrice[][100], int nr_noduri, int nod_sursa)
{
	lg_drum[nod_sursa] = 0;
	for (int i = 1; i <= nr_noduri; i++)
		if (i != nod_sursa)
			lg_drum[i] = INT_MAX;
	Q.push(nod_sursa);
	while (!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for (int i = 1; i <= nr_noduri; i++)
			if (matrice[x][i] == 1)
			{
				if (lg_drum[i] == INT_MAX)
				{
					parinte[i] = x;
					lg_drum[i] = lg_drum[x] + 1;
					Q.push(i);
				}
			}
	}
}

void reconfig(int from, int dest)
{
	if (from == dest) {
		cout << from << " ";
		return;
	}
	reconfig(from, parinte[dest]);
	cout << dest << " ";
}
*/
int citire_fisier(int matrice[][100], int nr_noduri)
{
	int nod_1, nod_2;
	f >> nr_noduri;
	while (f)
	{
		f >> nod_1 >> nod_2;
		matrice[nod_1][nod_2] = 1;
	}
	return nr_noduri;
}
void afisare_matrice(int mat[][100], int linii, int coloane)
{
	for (int i = 1; i <= linii; i++)
	{
		for (int j = 1; j <= coloane; j++)
			cout << mat[i][j] << " ";
		cout << endl;
	}

}
void copy_matrice(int matrice_1[][100], int dim, int matrice_2[][50])
{
	for (int i = 1; i <= dim; i++)
		for (int j = 1; j <= dim; j++)
			matrice_2[i][j] = matrice_1[i][j];
}
int main()
{
	int nr_noduri;
	ifstream f("C:/Users/Denis/Desktop/AG/02_laborator/grafuri.txt");
	f >> nr_noduri;
	
	for(int i=1;i<=nr_noduri;i++)
		matrice[i][i] = 1;//consideram ca fiecare nod este accesibil din el insusi
	
	int nod_1, nod_2;
	while (f >> nod_1 >> nod_2) 
	{
		
		matrice[nod_1][nod_2] = 1;
		Adj[nod_1].push_back(nod_2);
	}
	for (int k = 1; k <= nr_noduri; ++k) {
		for (int i = 1; i <= nr_noduri; ++i) {
			for (int j = 1; j <= nr_noduri; ++j) {
				if (matrice[i][k] && matrice[k][j]) {
					matrice[i][j] = 1;
				}
			}
		}
	}
	afisare_matrice(matrice, nr_noduri, nr_noduri);
	return 0;
}