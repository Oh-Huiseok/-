
#include <iostream>

#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	vector <vector<int>> p(n, vector<int>(n, 0));
	vector <vector<int>> k(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++)
			cin >> p[i][j];
	}

	vector <int>tmp(n, 0);
	vector <int>cnt(n, 1);
	copy(p[n - 1].begin(), p[n - 1].end(), tmp.begin());
	int l, r;

	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			l = tmp[j] + p[i][j];
			r = tmp[j + 1] + p[i][j];
			if (l < r) {
				tmp[j] = r;
				k[i][j] = 2;
				cnt[j] = cnt[j + 1];
			}
			else {
				if (l == r) {
					cnt[j] += cnt[j + 1];
				}
				tmp[j] = l;
				k[i][j] = 1;
			}

		}
	}

	cout << tmp[0] << "\n";
	cout << cnt[0] << "\n";
	int j = 0, i;
	for (i = 0; i < n - 1; i++) {
		cout << p[i][j] << " ";
		if (k[i][j] == 2) {
			j++;
		}
	}
	cout << p[i][j];

}