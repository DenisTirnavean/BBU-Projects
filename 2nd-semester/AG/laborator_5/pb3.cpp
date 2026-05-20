#include <bits/stdc++.h>
using namespace std;

int n, m;

vector<int> L;
vector<vector<int>> G;
vector<pair<int,int>> M;
bitset<500000> elim;

void Euler(int k)
{
    stack<int> S;
    S.push(k);
    while(! S.empty())
    {
        k = S.top();
        if(G[k].size())
        {
            int x = G[k].back();
            G[k].pop_back();
            if(! elim[x])
            {
                elim[x] = 1;
                int p = M[x]. second;
                if(p == k) p = M[x].first;
                S.push(p);
            }
        }
        else
        {
            L.push_back(k);
            S.pop();
        }
    }
}

int main(int argc, char** argv)
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    int i , j;
    fin >> n >> m;
    G = vector<vector<int>>(n+1);
    for(int index=0;index<m;++index)
    {
        fin >> i >> j;
        M.push_back({i,j});
        int sz = M.size()-1;
        G[i].push_back(sz);
        G[j].push_back(sz);
    }
    Euler(0);
    for(auto k : L)
        fout << k << " ";
    return 0;
}