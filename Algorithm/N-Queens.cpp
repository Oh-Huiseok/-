#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
vector<int> res;
int cnt = 0;

int cmp(vector<int>a, vector<int>b);

vector<int> makeV(vector<int>a) {
	vector<int>V;
	for (int k : a) {
		if (k > 9) {
			V.push_back(k / 10);
			V.push_back(k % 10);
		}
		else {
			V.push_back(k);
		}
	}
	return V;
}

bool promising(int i, vector<int> col) {
	int k = 1;
	bool flag = true;
	while (k < i && flag) {
		if ((col[i] == col[k]) || (abs(col[i] - col[k]) == i - k))
			flag = false;
		k++;
	}
	return flag;
}

void queen(int i, vector<int> col) {
	int j;

	if (promising(i, col)) {
		if (i == n) {
			cnt++;
			vector<int>tmp = makeV(col);
			if (cmp(tmp, res) > 0) {
				res.resize(tmp.size());
				copy(tmp.begin(), tmp.end(), res.begin());
			}
		}
		else {
			for (j = 1; j <= n; j++) {
				col[i + 1] = j;
				queen(i + 1, col);
			}
		}
	}
}
int cmp(vector <int>a, vector<int>b) {
	int i = 0, j = 0;
	int chk = 1;
	while (i < a.size() && j < b.size() && chk) {
		if (a[i] > b[j]) {
			return 1;
			break;
		}
		else if (a[i] < b[j]) {
			return -1;
			break;
		}
		i++;
		j++;
	}
	return chk;
}
int main() {
	cin >> n;
	vector<int> V(n+1);
	res.resize(n+1);
	queen(0, V);
	cout << cnt << endl;
	for (int i = 1; i < res.size(); i++)
		cout << res[i];
}