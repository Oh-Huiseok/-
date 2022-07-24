#include <iostream>
#include <vector>

using namespace std;

typedef struct vector<vector<int>> matrix_t;

int n, m;
matrix_t W;
vector<int> vindex;
int cnt = 0;

bool promising(int i) {
	bool flag = true;
	if (i == n - 1 && !W[vindex[n - 1]][vindex[0]])
		flag = false;
	else if (i > 0 && !W[vindex[i - 1]][vindex[i]])
		flag = false;
	else {
		int j = 1;
		while (j < i && flag) {
			if (vindex[j] == vindex[i])
				flag = false;
			j++;
		}
	}

	return flag;
}

void Hamilton(int i) {
	if (promising(i)) {
		if (i == n-1) {
			cnt += 1;
		}
		else {
			for (int j = 2; j <= n; j++) {
				vindex[i + 1] = j;
				Hamilton(i + 1);
			}
		}
	}
}
int main() {
	cin >> n >> m;
	int u, v;
	W.resize(n + 1, vector<int>(n + 1, 0));
	vindex.resize(n + 1);

	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		W[u][v] = 1;
		W[v][u] = 1;
	}
	vindex[0] = 1;

	Hamilton(0);

	cout << cnt;
}