//
// Created by Daniel on 13.05.2022.
//

#ifndef LAB5_PB1_H
#define LAB5_PB1_H
#include <bits/stdc++.h>
using namespace std;

#define inf 0x3f3f3f3f

struct Nod
{
    int nod;
    int cost;
};

class GrafPonderat{
private:
    int n;
    vector<vector<Nod>> G;
public:
    GrafPonderat(){n=0;}
    explicit GrafPonderat(int nrnod) : n(nrnod){
        G = vector<vector<Nod>>(nrnod+1);
    }
    GrafPonderat& operator=(const GrafPonderat& graf) = default;
    int size() const {return n;}
    int cost(int x, int y){
        for(Nod& nod : G[x])
            if(nod.nod == y)
                return nod.cost;
        return 0x3f3f3f3f;
    }
    void addCost(int x, int y, int cost)
    {
        bool gasit1=0;
        for(Nod& nod : G[x])
            if(nod.nod == y) {
                nod.cost += cost;
                gasit1 = 1;
                break;
            }
        if(!gasit1) add(x, y, cost);
    }
    const vector<Nod>& operator[](const int& poz) {return G[poz];}
    void add(int x, int y, int cost)
    {
        G[x].push_back(Nod{y, cost});
    }
    bool BFS(int start, int stop, vector<int>& parent)
    {
        parent.resize(n+1); parent.clear();
        queue<int> q;
        vector<bool> viz(n+1, false);
        q.push(start);
        viz[start] = 1;
        parent[start]=-1;
        int v;
        while (!q.empty())
        {
            v = q.front();
            q.pop();
            for(const Nod& nod : G[v])
                if(!viz[nod.nod] && nod.cost>0)
                {
                    parent[nod.nod] = v;
                    if(nod.nod==stop) return true;
                    q.push(nod.nod);
                    viz[nod.nod] = 1;
                }
        }
        return false;
    }
    friend istream& operator>>(istream& in, GrafPonderat& g)
    {
        int m;
        in>>g.n>>m;
        g.G = vector<vector<Nod>>(g.n+1);
        for(int i=0;i<m;++i)
        {
            int x, y, cost;
            in>>x>>y>>cost;
            g.add(x, y, cost);
        }
        return in;
    }
};

int FordFulkerson(GrafPonderat& graf, int start, int stop)
{
    GrafPonderat grezidual = graf;
    vector<int> parent;
    int max_flow = 0;
    while(grezidual.BFS(start, stop, parent))
    {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = inf;
        for(int v=stop; v!=start; v=parent[v])
        {
            int u = parent[v];
            path_flow = min(path_flow, grezidual.cost(u, v));
        }
        // update residual capacities of the edges and
        // reverse edges along the path
        for(int v=stop;v!=start;v=parent[v])
        {
            int u = parent[v];
            grezidual.addCost(u, v, -path_flow);
            grezidual.addCost(v, u, path_flow);
        }

        max_flow += path_flow;
    }
    return max_flow;
}

#endif //LAB5_PB1_H
