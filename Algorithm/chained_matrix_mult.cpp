#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> mat;
typedef vector<int> v;

int min(int s, int &m, int e, mat M, v d) {
	int minval = 999999, val;

	for (int i = s; i <= e-1; i++) {
		val = M[s][i] + M[i + 1][e] + d[s - 1] * d[i] * d[e];
		if (minval > val) {
			minval = val;
			m = i;
		}
	}
	return minval;
}

void minmult(int n, v &d, mat &M, mat &P) {
	for (int i = 1; i <= n; i++) {
		M[i][i] = 0;
	}
	for (int dia = 1; dia <= n - 1; dia++) {
		for (int i = 1; i <= n - dia; i++) {
			int j = i + dia;
			int k;
			M[i][j] = min(i, k, j, M, d);
			P[i][j] = k;
		}
	}

}

void order(int s, int e, mat& P, string &str) {
	if (s == e)
		str += string("(A)");
	else {
		str += string("(");
		int k = P[s][e];
		order(s, k, P, str);
		order(k + 1, e, P, str);
		str += string(")");
	}
}
int main() {
	int n;
	cin >> n;
	v d(n + 1);
	mat M(n + 1, vector<int>(n + 1, 0));
	mat P(n + 1, vector<int>(n + 1, 0));

	for (int i = 0; i <= n; i++)
		cin >> d[i];

	minmult(n, d, M, P);
	int i, j;
	for (int i = 1; i <= n; i++) {
		for (j = i; j < n; j++) {
			cout << M[i][j] << " ";
		}
		cout << M[i][j];
		cout << '\n';
	}

	for (int i = 1; i <= n; i++) {
		for (int j = i; j < n; j++) {
			cout << P[i][j] << " ";
		}
		cout << P[i][j];
		cout << '\n';
	}

	cout << M[1][n] << endl;
	string ans;
	int cnt = 1;
	order(1, n, P, ans);
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i];
		if (ans[i] == 'A') {
			cout << cnt;
			cnt++;
		}
	}
}