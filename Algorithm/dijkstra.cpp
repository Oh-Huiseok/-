#include <iostream>
#include <vector>
#include<stack>
#define INF 0xffff
using namespace std;

typedef vector<vector<int>> matrix_t;
typedef vector<pair<int, int>> set_of_edges;
typedef pair<int, int> edge_t;
typedef vector<int> V;
typedef stack<int> S;

void findPath(V P, int v, S& R) {
    if (P[v] != 1) {
        R.push(P[v]);
        findPath(P, P[v], R);
    }
}
void dijkstra(int n, matrix_t& W, set_of_edges& F, V& P)
{
    int vnear, min;
    vector<int> touch(n + 1), lenght(n + 1);
    F.clear();
    for (int i = 2; i <= n; i++) {
        touch[i] = 1;
        lenght[i] = W[1][i];
    }
    for (int i = 2; i < n; i++) {
        cout << touch[i] << " ";
    }
    cout << touch[n] << endl;
    for (int k = 0; k < n - 1; k++) {
        min = INF;
        for (int i = 2; i <= n; i++)
            if (0 <= lenght[i] && lenght[i] < min) {
                min = lenght[i];
                vnear = i;
            }
        F.push_back(make_pair(touch[vnear], vnear));
        P[vnear] = touch[vnear];
        for (int i = 2; i <= n; i++) {
            if (lenght[i] > lenght[vnear] + W[vnear][i]) {
                lenght[i] = lenght[vnear] + W[vnear][i];
                touch[i] = vnear;
            }
        }
        lenght[vnear] = -1;

        for (int i = 2; i < n; i++) {
            cout << touch[i] << " ";
        }
        cout << touch[n] << endl;
    }
}

int main() {
    int n, m, u, v, w; cin >> n >> m;
    matrix_t W(n + 1, vector<int>(n + 1, INF));
    V P(n + 1, 1);
    for (int i = 0; i <= n; i++)
        W[i][i] = 0;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        W[u][v] = w;
    }
    int Tn; cin >> Tn;
    vector<int> T(n);
    for (int i = 0; i < Tn; i++) {
        cin >> v;
        T[i] = v;
    }
    set_of_edges F;
    dijkstra(n, W, F, P);
    for (int i = 0; i < n - 1; i++) {
        int u = F[i].first;
        int v = F[i].second;
        cout << u << " " << v << " " << W[u][v] << endl;
        
    }
    
    for (int i = 0; i < Tn; i++) {
        v = T[i];
        cout << "1 ";
        S r;
        findPath(P, v, r);
        while (!r.empty()) {
            cout << r.top() << " ";
            r.pop();
        }
        cout << v;
        if (i != Tn - 1)
            cout << endl;
    }

}