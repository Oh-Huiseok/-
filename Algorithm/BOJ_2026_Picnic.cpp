#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> mat;
vector<int> ans;

int n, k, f;

int startchk(mat &M, int s, vector<int>& comb) {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (M[s][i] == 1)
			cnt++;
	}

	if (cnt >= k-1)
		return 1;
	else {
		comb.clear();
		for (int i = 1; i <= n; i++) {
			M[s][i] = 0;
			M[i][s] = 0;
		}
		return 0;
	}
}

void picnic(int s, mat &M, vector<int> comb) {
	if (!startchk(M, s, comb))
		return;
	if (comb.size() == k) {
		ans.resize(comb.size());
		copy(comb.begin(), comb.end(), ans.begin());
		return;
	}
	vector<int> temp;
	temp.resize(comb.size());
 	copy(comb.begin(), comb.end(), temp.begin());

	for (int i = s+1; i <= n; i++) {
		if (M[s][i] == 1) {
			comb.push_back(i);
			picnic(i, M, comb);
		}
	}

}

int main() {

	cin >> k >> n >> f;

	mat m(n + 1, vector<int>(n + 1, 0));

	int s, e;
	for (int i = 0; i < f; i++) {
		cin >> s >> e;
		m[s][e] = 1;
		m[e][s] = 1;
	}


	for (int i = 1; i <= n; i++) {
		vector<int> comb;
		comb.push_back(i);
		picnic(i, m, comb);
		if (ans.size() == k) {
			break;
		}
	}
	
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << "\n";
	}
	return 0;
}