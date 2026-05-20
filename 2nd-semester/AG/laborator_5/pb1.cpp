#include <bits/stdc++.h>
#include "pb1.h"
using namespace std;

int main(int argc, char** argv)
{
    ifstream fin(argv[1]);
    GrafPonderat graf;
    fin>>graf; fin.close();

    int flux = FordFulkerson(graf, 0, graf.size()-1);
    cout<<flux;
    ofstream fout(argv[2]);
    fout<<flux;
    return 0;
}
