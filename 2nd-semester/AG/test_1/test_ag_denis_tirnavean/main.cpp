#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> Adj[100]; //lista de adiacenta
int visit[100];
void dfs(int n)
{
    if (visit[n] == 1) return;
    else {
        cout << n << " "; //copilul curent este vizitat
        visit[n] = 1;
    }
    vector<int>::iterator it;
    for (it = Adj[n].begin(); it != Adj[n].end(); ++it) { //vizitam vecinii nodului curent in adancime pana ce ajungem la unu deja vizitat
        dfs((*it));
    }
}
int get_unvisited(int nr_noduri)
{
    int i = 1;
    while (visit[i] == 1 && i <= nr_noduri)
        i++;
    if (i > nr_noduri)
        return -1;
    return i;
}
int main()
{
	int n, m; //n-nr_copii, m-nr_relatii
    int copil_1,copil_2;
	ifstream f("in.txt");
	f >> n >> m;
    //citim relatiile
    for (int i = 1; i <= m; i++)
    {
        f >> copil_1 >> copil_2;
        Adj[copil_1].push_back(copil_2);
        Adj[copil_2].push_back(copil_1);
    }
    int start = 1;
    int comp_conexa = 1;
    while (start != -1)
    {
        cout << "Grupul de prieteni " << comp_conexa<<" :";
        dfs(start);
        cout << endl;
        comp_conexa++;
        start = get_unvisited(n);
    }
	return 0;
}