#include <iostream>
#include<algorithm>
#include <vector>

using namespace std;

typedef struct {
	vector<vector<int>> mat;
	int x, y;
	bool possible;
} gamecover;

int temp = 0;

typedef struct {
	int y, x;
}block;

vector<int> ans;
int score = 0;

const block blocktypes[4][3] = {
	{{0, 0}, {1, 0}, {0, 1}}, 
	{{0, 0}, {0, 1}, {1, 1}},
	{{0 ,0}, {1, 0}, {1, 1}},
	{{0, 1}, {1, 1}, {1, 0}}
};

bool chk(gamecover g) { // 원래 덮혀있었으면 1, 안덮었으면 0
	for (int i = 0; i < g.y; i++) {
		for (int j = 0; j < g.x; j++) {
			if (g.mat[i][j] == 0)
				return false;
		}
	}
	return true;
}

bool inrange(gamecover g, int y, int x) {
	if ((y >= 0 && y < g.y) && (x >= 0 && x < g.x))
		return true;
	else
		return false;
}

void print(gamecover g) {
	for (int i = 0; i < g.y;  i++) {
		for (int j = 0; j < g.x; j++) {
			cout << g.mat[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

bool possible(gamecover g, int y, int x, int t) {
	for (int i = 0; i < 3; i++) {
		int py = y + blocktypes[t][i].y;
		int px = x + blocktypes[t][i].x;

		if (py < 0 || px < 0 || py >= g.y || px >= g.x || g.mat[py][px] == 1)
			return false;
	}
	return true;
}

void boardcover(gamecover g, int y, int x) {//재귀함수 초반에 가장 가까운 0 찾는 알고리즘 추가하기
	if (chk(g)) {
		score++;
		return;
	}

	int posy, posx;

	for (int i = 0; i < 4; i++) {
		if (possible(g, y, x, i)) {
			for (int j = 0; j < 3; j++) {
				posy = blocktypes[i][j].y + y;
				posx = blocktypes[i][j].x + x;
				g.mat[posy][posx] = 1;
			}
			print(g);
			boardcover(g, y, x);
			for (int j = 0; j < 3; j++) {
				posy = blocktypes[i][j].y + y;
				posx = blocktypes[i][j].x + x;
				g.mat[posy][posx] = 0;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int c, cnt;
	cin >> c;

	vector<gamecover> games(c);

	for (int i = 0; i < c; i++) {
		int x, y;
		cin >> y >> x;
		games[i].x = x;
		games[i].y = y;
		games[i].mat.resize(y, vector<int>(x));
		games[i].possible = true;

		string temp;
		cnt = 0;

		for (int j = 0; j < y; j++) {
			cin >> temp;
			for (int k = 0; k < temp.length(); k++) {
				if (temp[k] == '#')
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
		if (games[i].possible == false) {
			ans.push_back(0);
		}
		else {
			for (int j = 0; i < games[i].y; j++) {
				for (int k = 0; j < games[i].x; k++) {
					boardcover(games[i], j, k);
				}
			}
			ans.push_back(score);
		}
		score = 0;
	}

	for (int x : ans) {
		cout << x << endl;
	}
	return 0;
}