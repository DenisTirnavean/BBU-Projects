#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

int capacity[200][200];
vector<int> adj[200];
bool visited[200];

bool dfs(int u, int t, int& flux) {
    if (u == t) 
        return true;

    visited[u] = true;

    for (auto v : adj[u]) {
        if (!visited[v] && capacity[u][v] > 0) {
            int minCap = min(flux, capacity[u][v]);
            if (dfs(v, t, minCap)) {
                capacity[u][v] -= minCap;
                capacity[v][u] += minCap;
                flux = minCap;
                return true;
            }
        }
    }

    return false;
}

int Ford_Fulkerson(int s, int t) {
    int flux = 0;
    int newFlow;

    while (true) {
        memset(visited, false, sizeof(visited));
        newFlow = INF;

        if (!dfs(s, t, newFlow))
            break;

        flux += newFlow;
    }

    return flux;
}

int main() {
    int N, M, E;
    ifstream fin("in.txt");
    fin >> N >> M >> E;

    int sursa = 0;
    int destinatia = N + M + 1;
    
    for (int i = 0; i < E; i++) {
        int u, v;
        fin >> u >> v;
        v += N;

        capacity[u][v] = 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    //legam sursa
    for (int i = 1; i <= N; ++i) {
        capacity[sursa][i] = 1;
        adj[sursa].push_back(i);
        adj[i].push_back(sursa);
    }
    //legam destinatia
    for (int i = 1; i <= M; i++) {
        int node = i + N;
        capacity[node][destinatia] = 1;
        adj[node].push_back(destinatia);
        adj[destinatia].push_back(node);
    }
    ofstream fout("out.txt");
    fout << Ford_Fulkerson(sursa, destinatia) << endl;
    fout.close();
    fin.close();
    return 0;
}