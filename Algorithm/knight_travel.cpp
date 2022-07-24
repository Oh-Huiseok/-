#include<iostream>
#include<vector>
#include<map>

using namespace std;

int n, m, T;
int hamc = 0;
int hamp = 0;

int chk = false;

vector<pair<int, int>> S;
vector<int> res;

vector< vector<int>> adjlst;
vector<int> mark;
vector<pair<int, int>> pmove = { {-2, -1}, {-2, +1},{-1,+2}, {+1, +2}, {+2, +1}, {+2, -1}, {+1, -2} ,{-1, -2} };

void make_adjlist(vector<vector<int>>& adjlst) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (auto k : pmove) {
				int I = i + k.first;
				int J = j + k.second;
				if ((I < n && I >= 0) && (J < m && J >= 0))
					adjlst[i * m + j].push_back((I * m) + J);
			}
		}
	}
}

void knightTour(int i, int v, int S, vector<int> mark) {
	if (i == n * m) {
		for (int c : adjlst[v]) {
			if (c == S) {
				hamc += 1;
				break;
			}
		}
		hamp += 1;
	}
	else {
		for (int j : adjlst[v]) {
			if (mark[j] == 0) {
				mark[j] = i + 1;
				knightTour(i + 1, j, S, mark);
				mark[j] = 0;
			}
		}
	}
}

int main() {
	cin >> n >> m;	//n*m크기..

	adjlst.resize(n * m + 1);
	mark.resize(n * m + 1, 0);
	make_adjlist(adjlst);

	cin >> T;	//테스트케이스.
	S.resize(T);

	for (int i = 0; i < T; i++)
		cin >> S[i].first >> S[i].second; // 이게 x, y좌표인듯

	mark.clear();
	mark.resize(n * m, 0);
	mark[0] = 1;
	knightTour(1, 0, 0, mark);

	cout << hamc << endl; // 0,0에서 해밀턴 순환 갯수

	for (int i = 0; i < T; i++) {
		hamp = 0;
		int pos = S[i].first * m + S[i].second;
		mark.clear();
		mark.resize(n * m, 0);
		mark[pos] = 1;
		knightTour(1, pos, pos, mark);
		res.push_back(hamp); // 해밀턴 경로 갯수?
	}

	for (int i = 0; i < res.size() - 1; i++) {
		cout << res[i] << '\n';
	}
	cout << res[res.size() - 1];
}