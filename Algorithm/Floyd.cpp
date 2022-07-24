#include <iostream>
#include <vector>
#define INF 999
using namespace std;

typedef vector<vector<int>> G;

void floyd2(G& D, G& P, int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				if (D[j][k] > D[j][i] + D[i][k]) {
					D[j][k] = D[j][i] + D[i][k];
					P[j][k] = i;
				}
			}
		}
	}
}

void path(G& P, int u, int v, vector<int>& p) {
	int k = P[u][v];
	if (k != 0) {	
		path(P, u, k, p);
		p.push_back(k);
		path(P, k, v, p);
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	G D(n+1, vector<int>(n + 1, INF));
	G P(n+1, vector<int>(n + 1, 0));

	int u, v, w;
	for (int i = 1; i <=n; i++) {
		D[i][i] = 0;
	}
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		D[u][v] = w;
	}

	int t;
	cin >> t;
	
	G T(t, vector<int>(2, 0));
	for (int i = 0; i < t; i++) {
		cin >> u >> v;
		T[i][0] = u;
		T[i][1] = v;
	}

	floyd2(D, P, n);

	int i, j;
	for (i = 1; i <= n; i++) {
		for (j = 1; j < n; j++){
			cout << D[i][j] << " ";
		}
		cout << D[i][j];
		if (i != n)
			cout << endl;
	}

	cout << endl;

	for (i = 1; i <= n; i++) {
		for (j = 1; j < n; j++){
			cout << P[i][j] << " ";
		}
		cout << P[i][j];
		if (i != n)
			cout << endl;
	}

	cout << endl;

	for(int i=0;i<t;i++){
		u=T[i][0];
		v=T[i][1];
		if (D[u][v] != INF) {
				cout << u << " ";
				vector <int>p;
				path(P, u, v, p);
				for(int j=0;j<p.size();j++){
					cout<<p[j]<<" ";
				}
				cout << v;
			}
		else
			cout << "NONE";
		if (i != t-1)
			cout << endl;
	}
}