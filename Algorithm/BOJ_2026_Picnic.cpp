#include <iostream>
#include<algorithm>
#include <vector>

using namespace std;

typedef vector<vector<int>> mat;
vector<int> ans;

int n, k, f;
bool flag = true;
int startchk(mat &M, int s) {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (M[s][i] == 1)
			cnt++;
	}

	if (cnt >= k-1)
		return 1;
	else {
		for (int i = 1; i <= n; i++) {
			M[s][i] = 0;
			M[i][s] = 0;
		}
		return 0;
	}
}

void picnic(int s, mat &M, vector<int> comb) {
	if (!flag)
		return;;
	if (comb.size() == k) {
		ans.resize(comb.size());
		copy(comb.begin(), comb.end(), ans.begin());
		flag = false;
		return;
	}
	
	for (int i = 1; i <= n; i++) {
		if (find(comb.begin(), comb.end(), i) != comb.end())
			continue;
		if (M[s][i] == 1) {
			bool flag2 = true;
			for (int j = 0; j < comb.size(); j++) {
				if (M[i][comb[j]] != 1)
					flag2 = false;
			}
			if (flag2) {
				comb.push_back(i);
				picnic(i, M, comb);
				comb.pop_back();
			}
		}
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> k >> n >> f;

	mat m(n + 1, vector<int>(n + 1, 0));

	int s, e;
	for (int i = 0; i < f; i++) {
		cin >> s >> e;
		m[s][e] = 1;
		m[e][s] = 1;
	}


	for (int i = 1; i <= n; i++) {
		if (!startchk(m, i))
			continue;
		vector<int> comb;
		comb.push_back(i);
		picnic(i, m, comb);
		if (ans.size() == k) {
			break;
		}
	}
	if (flag)
		cout << "-1";
	else {
		for (int i = 0; i < ans.size(); i++) {
			cout << ans[i] << "\n";
		}
	}
	return 0;
}