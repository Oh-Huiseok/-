#include <iostream>
#include <algorithm>
#include <vector>

#define INF 99999

using namespace std;

typedef vector<vector<int>> mat;

const mat S{
	{0, 1, 2},
	{3, 7, 9, 11},
	{4, 10, 14, 15},
	{0, 4, 5, 6, 7},
	{6, 7, 8, 10, 12},
	{0, 2, 14, 15},
	{3, 14, 15},
	{4, 5, 7, 14, 15},
	{1, 2, 3, 4, 5},
	{3, 4, 5, 9, 13}
};

bool chk(vector<int> M) {
	for (int i = 0; i < 16; i++)
		if (M[i] != 12)
			return false;
	return true;
}

int min(int a, int b) {
	return a > b ? b : a;
}
void print(vector<int> M, int curr) {
	cout << curr << "     ";
	for (int i = 0; i < 16; i++)
		cout << M[i] << " ";
	cout << endl;
}
void push(vector<int>& M, int curr) {
	for (int i = 0; i < S[curr].size(); i++) {
		M[S[curr][i]] += 3;
		if (M[S[curr][i]] == 15) {
			M[S[curr][i]] = 3;
		}
	}
}

int clocksync(vector<int>& M, int curr) {
	//print(M, curr);

	if (curr == 10)
		return chk(M) ? 0 : INF;
	int ret = INF;
	for (int i = 0; i < 4; ++i) {
		ret = min(ret, i + clocksync(M, curr+1));
		//cout << ret << endl;
		push(M, curr);

	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int C;
	cin >> C;

	mat M(C, vector<int>(16));

	for (int i = 0; i < C; i++) {
		for (int j = 0; j < 16; j++) {
			cin >> M[i][j];
		}
	}

	for (int i = 0; i < C; i++) {
		int ans = clocksync(M[i], 0);
		if (ans == INF)	ans = -1;
		cout << ans << endl;
	}

	return 0;
}