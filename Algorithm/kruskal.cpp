#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef struct edge_t {
    int u, v, w;
}edge_t;

typedef vector <int> dset;
typedef vector <edge_t> set_of_edges;


bool cmp(const edge_t a, const edge_t b) {
    if (a.w < b.w)
        return true;
    return false;
}
int dfind(dset D, int idx) {
    while (D[idx] != idx)
        idx = D[idx];
    return idx;
}
void dmerge(dset& D, int p, int q) {
    D[p] = q;
}

void kruskal(int n, int m, set_of_edges E, set_of_edges& F, dset &D) {
    int p, q;
    edge_t e;
    F.clear();

    for (int i = 0; i < n; i++) {
        p = dfind(D, E[i].u);
        q = dfind(D, E[i].v);
        if (p != q) {
            dmerge(D, p, q);
            F.push_back(E[i]);
        }
    }
}

int main() {
    int n, m, u, v, w; cin >> n >> m;
    set_of_edges E;
    set_of_edges F;
    dset D(n+1);
    for (int i = 1; i <= n; i++) {
        D[i] = i;
    }
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        edge_t e;
        e.u = u;
        e.v = v;
        e.w = w;
        E.push_back(e);        
    }
    sort(E.begin(), E.end(), cmp);
    kruskal(n, m, E, F, D);

    for (int i = 0; i < n-1; i++) {
        cout << F[i].u << " " << F[i].v << " " << F[i].w;
        if (i != n - 2)
            cout << endl;
    }
}