#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> G;
set<pair<int,int>> muchiiramase;

typedef pair<int,int> Muchie;

#define muchie(x, y) make_pair(min(x, y), max(x, y))

void read(char* file, int& v1)
{
    v1 = -1;
    ifstream fin(file);
    fin>>n>>m;
    G = vector<vector<int>>(n+1);
    for(int i=0;i<m;++i)
    {
        int x, y;
        fin>>x>>y;
        muchiiramase.insert(muchie(x, y));
        if(v1==-1) v1 = x;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    fin.close();
}

int punte(pair<int, int> mch)
{
    queue<int> q;
    vector<bool> p(n+1);
    q.push(mch.first);
    while (!q.empty())
    {
        int vf = q.front();
        p[vf] = true;
        q.pop();
        for(const auto& y : G[vf])
            if(!p[y] && muchie(vf, y) != mch)
                q.push(y);
    }
    return !(p[mch.first] && p[mch.second]);
}

bool Fleury(int v, vector<Muchie>& muchii_rez)
{
    vector<int> varfuri;
    varfuri.push_back(v);
    start:
    if(muchiiramase.empty()) {
        return true;
    }
    for(const auto& y : G[v])
    {
        auto mch = muchie(v, y);
        bool gasit = muchiiramase.find(mch) != muchiiramase.end();
        if(gasit && !punte(mch)){
            muchii_rez.push_back(muchie(v, y));
            varfuri.push_back(y);
            muchiiramase.erase(mch);
            v = y;
            goto start;
        }
    }
    for(const auto& mch : muchiiramase)
    {
        if(std::find(varfuri.begin(), varfuri.end(), mch.first) != varfuri.end())
        {
            muchii_rez.push_back(mch);
            varfuri.push_back(mch.second);
            v = mch.second;
            goto start;
        }
        else if(std::find(varfuri.begin(), varfuri.end(), mch.second) != varfuri.end())
        {
            muchii_rez.push_back(mch);
            varfuri.push_back(mch.first);
            v = mch.first;
            goto start;
        }
    }
    return false;
}

int main(int argc, char** argv) {
    int v1;
    read(argv[1], v1);
    vector<Muchie> muchii_din_ciclu;
    ofstream fout(argv[2]);
    if(!Fleury(v1, muchii_din_ciclu))
        cerr<<"Nu exista ciclu eulerian!\n";
    vector<vector<int>> Grez(n+1);
    for(const auto& elem : muchii_din_ciclu)
    {
        Grez[elem.first].push_back(elem.second);
        Grez[elem.second].push_back(elem.first);
    }

    fout.close();
    return 0;
}
