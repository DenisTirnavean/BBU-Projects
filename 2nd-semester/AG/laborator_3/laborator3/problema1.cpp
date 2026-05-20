#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

const int INF = (1 << 30);

typedef struct {
    int d;
    int p;
}Nod;

typedef struct {
    int from;
    int to;
    int pondere;
}Arc;

vector<Arc>A;

vector<Nod>dist;


void initializare(int n, int start) {
    for (int i = 0; i < n; ++i) {
        dist[i].d = INF;
        dist[i].p = -1;
    }
    dist[start].d = 0;
    dist[start].p = 0;

}

void relax(Arc elem) {
    if (dist[elem.to].d > dist[elem.from].d + elem.pondere) {
        dist[elem.to].d = dist[elem.from].d + elem.pondere;
        dist[elem.to].p = elem.from;
    }
}

bool BellmanFord(int n, int m, int start) {
    initializare(n, start);

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            relax(A[j]);
        }
    }

    for (int i = 0; i < m; ++i) {
        if (dist[A[i].to].d > dist[A[i].from].d + A[i].pondere) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    int n, m, start;
    //ifstream fin(argv[1]);
    //ofstream fout(argv[2]);
    ifstream fin("C:/Users/Denis/Desktop/AG/Laboratoare/lab3/03_laborator/03_laborator/1/2-in.txt");
    ofstream fout("out.txt");
    fin >> n >> m >> start;
    A.resize(m);
    dist.resize(n);
    for (int i = 0; i < m; ++i) {
        fin >> A[i].from >> A[i].to >> A[i].pondere;
    }

    BellmanFord(n, m, start);
    for (int i = 0; i < n; ++i) {
         if (dist[i].d == INF)
            fout << "INF ";
         else
            fout << dist[i].d << " ";
    }
    fin.close();
    fout.close();
    return 0;
}