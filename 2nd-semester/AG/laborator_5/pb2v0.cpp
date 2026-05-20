#include <bits/stdc++.h>
using namespace std;

struct Muchie
{
    int flow, capacity;
    int v;
};

class Graf{
private:
    int n;
    vector<vector<Muchie>> G;
    vector<int> e_flow;
    vector<int> h;

    bool push(int u);
    void relabel(int u);
    void preflow(int start);
    void updateReverseMuchieFlow(int x, int y, int flow);

    int overFlowNod(int start, int stop);

public:
    Graf(int V) : n(V) {
        G = vector<vector<Muchie>>(V+1);
        e_flow = vector<int>(n+1, 0);
        h = vector<int>(n+1, 0);
    }
    void addEdge(int u, int v, int capacity) {
        Muchie m;
        m.v = v;
        m.flow = 0;
        m.capacity = capacity;
        G[u].push_back(m);
    }
    int getMaxFlow(int start, int stop);
};

void Graf::preflow(int start) {
    // sursa are inaltimea n
    h[start] = n;
    for(Muchie& m : G[start]){
        m.flow = m.capacity;
        e_flow[m.v] += m.flow;
        Muchie reverse_m;
        reverse_m.v = start;
        reverse_m.flow = -m.flow;
        reverse_m.capacity = 0;
        G[m.v].push_back(reverse_m);
    }
}

int Graf::overFlowNod(int start, int stop)
{
    for (int i = start + 1; i < stop - 1; i++)
        if (e_flow[i] > 0)
            return i;

    // -1 if no overflowing Vertex
    return -1;
}

void Graf::updateReverseMuchieFlow(int x, int y, int flow) {
    int gasit = 0;
    for(auto& m : G[y])
        if(m.v==x)
        {
            m.flow -= flow;
            return;
        }
    // daca nu exista, o adaugam
    Muchie m;
    m.v = x;
    m.flow = flow;
    m.capacity = 0;
    G[y].push_back(m);
}

// dam push din varful u care da overflow
bool Graf::push(int u) {
    for(auto& m : G[u])
    {
        // push imposibil
        if(m.flow == m.capacity)
            continue;

        // push e posibil daca inaltimea nodului curent
        // e mai mare decat inaltimea nodului vecin
        if(h[u] > h[m.v])
        {
            // fluxul pompat este minimul din cat a mai ramas
            // pe muchie si cat flux am in exces pe nod
            int flow = min(m.capacity - m.flow,
                           e_flow[u]);

            // reduc fluxul exces din nod
            e_flow[u] -= flow;

            // cresc fluxul exces din nodul adiacent
            e_flow[m.v] += flow;

            // adaug fluxul in graful rezidual
            m.flow += flow;
            updateReverseMuchieFlow(u, m.v, flow);
            return true;
        }
    }
    return false;
}

// reetichetez nodul u
void Graf::relabel(int u) {
    int mh = INT_MAX; // inaltimea minima
    for(auto& m : G[u])
    {
        // daca fluxul e maxim nu reetichetam
        if(m.flow == m.capacity)
            continue;

        // actualizam inaltimea minima
        int hadj = h[m.v];
        if(hadj < mh)
        {
            mh = hadj;
            // actualizam inaltimea nodului u
            h[u] = mh + 1;
        }
    }
}

int Graf::getMaxFlow(int start, int stop) {
    preflow(start);
    int nod_excess;
    while((nod_excess=overFlowNod(start, stop)) != -1)
    {
        if(!push(nod_excess))
            relabel(nod_excess);
    }
    return e_flow[stop];
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