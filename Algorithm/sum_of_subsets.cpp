#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, W;
vector<int> w;
vector<bool> include;
vector<vector<int>> res;

int cnt = 0;

bool promising(int i, int weight, int total) {
	if ((weight + total >= W) && (weight == W || weight + w[i + 1] <= W))
		return true;
	else
		return false;
}

void sum_of_subsets(int i, int weight, int total) {
	if (promising(i, weight, total)) {
		if (weight == W) {
			cnt += 1;
			vector<int>tmp;
			for (int j = 1; j <= i; j++) {
				if (include[j]) {
					tmp.push_back(w[j]);
				}
			}
			res.push_back(tmp);
		}
		else {
			include[i + 1] = true;
			sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
			include[i + 1] = false;
			sum_of_subsets(i + 1, weight, total - w[i + 1]);
		}
	}
}
int main() {
	int total=0;
	cin >> n >> W;
	w.resize(n + 1);
	include.resize(n + 1);

	for (int i = 1; i <= n; i++) {
		cin >> w[i];
		total += w[i];
	}

	sum_of_subsets(0, 0, total);
	
	cout << cnt << endl;
	int j;
	for (int i = 0; i < res.size(); i++) {
		for (j = 0; j < res[i].size()-1; j++) {
			cout << res[i][j] << " ";
		}
		cout << res[i][j];
		if (i != res.size() - 1)
			cout << endl;
	}
	
}