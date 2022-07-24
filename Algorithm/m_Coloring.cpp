#include <iostream>
#include <vector>
#include <string>

using namespace std;
typedef vector<vector<int>> matrix_t;

int n;
int cnt;
int m = 0;
bool chk = true;

bool promising(int i, matrix_t W, vector<int> vcolor) {
	int j = 1;
	bool flag = true;

	while (j < i && flag) {
		if (W[i][j] && (vcolor[i] == vcolor[j]))
			flag = false;
		j++;
	}
	return flag;
}

void m_coloring(int i, matrix_t W, vector<int> vcolor) {
	if (promising(i, W, vcolor)) {
		if (i == n) {
			cnt += 1;
			chk = false;
		}
		else {
			for (int j = 1; j <= m; j++) {
				vcolor[i+1] = j;
				m_coloring(i + 1, W, vcolor);
			}
		}
	}
}

int main() {
	int k, u, v;
	cin >> n >> k;

	matrix_t W(n + 1, vector<int>(n + 1, 0));
	
	vector<int> c(n+1);

	for (int i = 0; i <= n; i++)
		W[i][i] = 0;

	for (int i = 0; i < k; i++) {
		cin >> u >> v;
		W[u][v] = 1;
		W[v][u] = 1;
	}
	while (chk) {
		m += 1;
		m_coloring(0, W, c);
	}
	cout << m << endl << cnt;
}