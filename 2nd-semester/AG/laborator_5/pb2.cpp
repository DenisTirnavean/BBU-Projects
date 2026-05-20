#include <bits/stdc++.h>
using namespace std;

struct Nod{
    int h;
    int e_flow;
};

struct Muchie
{
    int flow, capacity;
    int u, v;
};

class Graf{
private:
    int n;
    vector<Nod> noduri;
    vector<Muchie> muchii;

    bool push(int u);
    void relabel(int u);
    void preflow(int start);
    void updateReverseMuchieFlow(int i, int flow);

public:
    Graf(int V) : n(V) {
        for(int i=0;i<V;++i)
            noduri.push_back({0, 0});
    }
    void addEdge(int u, int v, int capacity) {
        muchii.push_back({0, capacity, u, v});
    }
    int getMaxFlow(int start, int stop);
};

void Graf::preflow(int start) {
    // sursa are inaltimea n
    noduri[start].h = n;
    for(int i=0;i<muchii.size();++i)
    {
        if(muchii[i].u == start)
        {
            muchii[i].flow = muchii[i].capacity;
            noduri[muchii[i].v].e_flow += muchii[i].flow;
            muchii.push_back({-muchii[i].flow, 0, muchii[i].v, start});
        }
    }
}

int overFlowNod(vector<Nod>& noduri)
{
    for (int i = 1; i < noduri.size() - 1; i++)
        if (noduri[i].e_flow > 0)
            return i;

    // -1 if no overflowing Vertex
    return -1;
}

void Graf::updateReverseMuchieFlow(int i, int flow) {
    int u = muchii[i].v, v = muchii[i].u;
    for(int j=0;j<muchii.size();++j)
        if(muchii[j].v == v && muchii[j].u == u)
        {
            muchii[j].flow -= flow;
            return;
        }
    // daca nu exista, o adaugam
    Muchie m{0, flow, u, v};
    muchii.push_back(m);
}

// dam push din varful u care da overflow
bool Graf::push(int u) {
    for(int i=0;i<muchii.size();++i)
        if(muchii[i].u == u) // muchiile adiacente nodului u
        {
            // push imposibil
            if(muchii[i].flow == muchii[i].capacity)
                continue;

            // push e posibil daca inaltimea nodului curent
            // e mai mare decat inaltimea nodului vecin
            if(noduri[u].h > noduri[muchii[i].v].h)
            {
                // fluxul pompat este minimul din cat a mai ramas
                // pe muchie si cat flux am in exces pe nod
                int flow = min(muchii[i].capacity - muchii[i].flow,
                               noduri[u].e_flow);

                // reduc fluxul exces din nod
                noduri[u].e_flow -= flow;

                // cresc fluxul exces din nodul adiacent
                noduri[muchii[i].v].e_flow += flow;

                // adaug fluxul in graful rezidual
                muchii[i].flow += flow;
                updateReverseMuchieFlow(i, flow);
                return true;
            }
        }
    return false;
}

// reetichetez nodul u
void Graf::relabel(int u) {
    int mh = INT_MAX; // inaltimea minima
    for(int i=0;i<muchii.size();++i)
        if(muchii[i].u==u)
        {
            // daca fluxul e maxim nu reetichetam
            if(muchii[i].flow == muchii[i].capacity)
                continue;

            // actualizam inaltimea minima
            int hadj =noduri[muchii[i].v].h;
            if(hadj < mh)
            {
                mh = hadj;
                // actualizam inaltimea nodului u
                noduri[u].h = mh + 1;
            }
        }
}

int Graf::getMaxFlow(int start, int stop) {
    preflow(start);
    int nod_excess;
    while((nod_excess=overFlowNod(noduri)) != -1)
    {
        if(!push(nod_excess))
            relabel(nod_excess);
    }
    return noduri.back().e_flow;
}

int main(int argc, char** argv)
{
    ifstream fin(argv[1]);
    int n, m;
    fin>>n>>m;
    Graf g(n);
    for(int i=0;i<m;++i)
    {
        int x, y, capacity;
        fin>>x>>y>>capacity;
        g.addEdge(x, y, capacity);
    }
    fin.close();
    cout<<g.getMaxFlow(0, n-1);
    return 0;
}