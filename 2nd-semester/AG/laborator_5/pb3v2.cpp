#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> G;
set<pair<int,int>> muchiiramase;
set<int> vfcriticerezolvate;

#define muchie(x, y) make_pair(min(x, y), max(x, y))
#define ramasa(x, y) (muchiiramase.find(muchie(x, y)) != muchiiramase.end())
#define apare(x, varfuri) (std::find(varfuri.begin(), varfuri.end(), x)!=varfuri.end())

void afis(vector<int>& v) {for(const auto& elem : v) cout<<elem<<' '; cout<<'\n';}

void read(char* file)
{
    ifstream fin(file);
    fin>>n>>m;
    G = vector<vector<int>>(n+1);
    for(int i=0;i<m;++i)
    {
        int x, y;
        fin>>x>>y;
        muchiiramase.insert(muchie(x, y));
        G[x].push_back(y);
        G[y].push_back(x);
    }
    fin.close();
}

void Ciclu(int start, vector<int>& varfuri, int& vfcritic)
{
    vfcritic = -1;
    varfuri.clear();
    varfuri.push_back(start);
    bool gata = false;
    while(!gata && !muchiiramase.empty())
    {
        int x = varfuri.back();
        if(vfcritic == -1 && G[x].size()>2 && vfcriticerezolvate.find(x) == vfcriticerezolvate.end()) {
            vfcritic = x;
        }
        bool gatafor = false;
        for(const int& y : G[x])
            if(ramasa(x, y))
            {
                muchiiramase.erase(muchie(x, y));
                if(apare(y, varfuri)) gata = true;
                varfuri.push_back(y);
                gatafor=true;
                break;
            }
        if(!gatafor)
        {
            vfcritic = vfcritic+1-1;
        }
    }
}

void Uneste(int vfcritic, vector<int>& varfuri1, vector<int> varfuri2)
{
    auto it = std::find(varfuri1.begin(), varfuri1.end(), vfcritic);
    varfuri1.erase(it);
    varfuri1.insert(it, varfuri2.begin(), varfuri2.end());
}

void Hierholzer(vector<int>& ciclu)
{
    vector<int> ciclu1, ciclu2;
    int vfcritic1, vfcritic2;
    Ciclu(0, ciclu1, vfcritic1);
    afis(ciclu1);
    while(!muchiiramase.empty())
    {
        assert(vfcritic1>-1);
        if(vfcritic1 == 3)
        {
            vfcritic2=-1;
        }
        Ciclu(vfcritic1, ciclu2, vfcritic2);
        afis(ciclu2);
        Uneste(vfcritic1, ciclu1, ciclu2);
        //for(const auto& elem : ciclu1) cout<<elem<<' '; cout<<'\n';
        vfcriticerezolvate.insert(vfcritic1);
        vfcritic1 = vfcritic2;
    }
    ciclu = ciclu1;
}

void test()
{
    vector<int> varfuri1, varfuri2;
    int vfcritic;
    Ciclu(2, varfuri1, vfcritic);
    Ciclu(vfcritic, varfuri2, vfcritic);
    Uneste(vfcritic, varfuri1, varfuri2);
    cout<<vfcritic<<'\n';
    for(const auto& elem : varfuri1)
        cout<<elem<<' ';
}

int main(int argc, char** argv) {
    read(argv[1]);
    vector<int> ciclu;
    Hierholzer(ciclu);
    ofstream fout(argv[2]);
    for(const auto& elem : ciclu)
        fout<<elem<<' ';
    fout.close();
    return 0;
}
