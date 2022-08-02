#include <iostream>
#include<algorithm>
#include <vector>

using namespace std;

typedef struct {
	vector<vector<int>> mat;
	int x, y;
	bool possible;
} gamecover;

typedef struct {
	int y, x;
}block;

vector<int> ans;
int score = 0;

const block blocktypes[4][3] = {
	{{0, 0}, {0, 1}, {0, 1}}, 
	{{0, 0}, {0, 1}, {1, 1}},
	{{0, 1}, {1, 1}, {1, 0}},
	{{0 ,0}, {1, 0}, {1, -1}}
};

bool chk(gamecover g) { // 원래 덮혀있었으면 1, 덮었으면 -1, 안덮었으면 0
	for (int i = 0; i < g.y; i++) {
		for (int j = 0; j < g.x; j++) {
			if (g.mat[i][j] == 0)
				return 0;
		}
	}
	return 1;
}

int cancover(gamecover g, int y, int x) {
	int cnt1, cnt2;
	int c;
	for (c = 0;  c< 4; c++) {
		for (int q = 0; q < 3; q++) {
			int posy = y + blocktypes[c][q].y;
			int posx = x + blocktypes[c][q].x;
		}
	}
}

bool inrange(gamecover g, int y, int x) {
	if ((y >= 0 && y < g.y) && (x >= 0 && x < g.x))
		return true;
	else
		return false;
}

void boardcover(gamecover g, int y, int x) {
	if (chk) {
		score++;
		return;
	}
	if (!inrange(g, y, x))
		return;
	if (g.mat[y][x] == 1 || g.mat[y][x] == -1)
		return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int c;
	cin >> c;

	vector<gamecover> games(c);

	for (int i = 0; i < c; i++) {
		int x, y;
		cin >> y >> x;
		games[i].x = x;
		games[i].y = y;

		char temp;
		int cnt = 0;

		for (int j = 0; j < y; j++) {
			for (int k = 0; k < x; k++) {
				cin >> temp;
				if (temp == '#')
					games[i].mat[j][k] = 1;
				else {
					games[i].mat[j][k] = 0;
					cnt++;
				}
			}
		}
		if (cnt % 3 != 0) {
			games[i].possible = false;
		}
	}

	for (int i = 0; i < c; i++) {
		if (games[i].possible == false)
			ans.push_back(0);
		else {
			boardcover(games[i], 0, 0);
			ans.push_back(score);
		}
		score = 0;
	}
	return 0;
}