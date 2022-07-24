#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define INF 999

using namespace std;

typedef vector<int> ordered_set;

typedef struct node {
	int level;
	ordered_set path;
	int bound;
} node_t;

typedef struct node *node_ptr;

struct compare {
	bool operator()(node_ptr u, node_ptr v) {
		if (u->bound > v->bound)
			return true;
		return false;
	}
};

typedef priority_queue<node_ptr, vector<node_ptr>, compare> priority_queue_of_node;

int n, m;
typedef vector<vector<int>> map;
map W;

int lenght(ordered_set path) {
	ordered_set tmp;
	tmp.resize(path.size());
	copy(path.begin(), path.end(), tmp.begin());

	int len = 0;
	for (int it = 0; it < tmp.size(); it++)
		if(it<tmp.size()-1)
			len += W[tmp[it]][tmp[it + 1]];
	return len;
}

bool hasOutgoing(int v, ordered_set path) {
	ordered_set tmp;
	tmp.resize(path.size());
	copy(path.begin(), path.end(), tmp.begin());
	for (int it = 0; it <tmp.size() - 1; it++)
		if (tmp[it] == v) return true;
	return false;
}

bool hasIncoming(int v, ordered_set path) {
	ordered_set tmp;
	tmp.resize(path.size());
	copy(path.begin(), path.end(), tmp.begin());
	for (int it = 1; it < tmp.size(); it++)
		if (tmp[it] == v) return true;
	return false;
}

int bound(node_ptr v) {
	int lower = lenght(v->path);
	for (int i = 1; i <= n; i++) {
		if (hasOutgoing(i, v->path)) continue;
		int min = INF;
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (j == 1 && i == v->path[v->path.size() - 1]) continue;
			if (hasIncoming(j, v->path)) continue;
			if (min > W[i][j]) min = W[i][j];
		}
		lower += min;
	}
	return lower;
}

node_ptr create_node(int level, ordered_set path) {
	node_ptr v = new node_t;
	v->level = level;
	v->path.resize(path.size());
	copy(path.begin(), path.end(), v->path.begin());
	v->bound = bound(v);
	return v;
}

int remaining_vertext(ordered_set path) {
	int S = n * (n + 1) / 2;
	
	for (int k = 0; k < path.size(); k++) {
		S  -= path[k];
	}

	return S;
}

bool isIn(int i, ordered_set p) {
	for (int x : p) {
		if (x == i)
			return true;
	}
	return false;
}

void travel2(ordered_set& opttour, int& minlength) {
	priority_queue_of_node PQ;
	node_ptr u, v;
	
	int k;

 	minlength = INF;
	v = create_node(0, { 1 });

	cout << v->level << " " << v->bound << " ";
	for (k = 0; k < v->path.size()-1; k++) {
		cout << v->path[k] << " ";
	}
	cout << v->path[k];
	cout << endl;

	PQ.push(v);
	while (!PQ.empty()) {
		v = PQ.top();
		PQ.pop();
		if (v->bound < minlength) {
			for (int i = 2; i <= n; i++) {
				if (isIn(i, v->path)) continue;
				u = create_node(v->level + 1, v->path);
				u->path.push_back(i);
				if (u->level == n - 2) {
					u->path.push_back(remaining_vertext(u->path));
					u->path.push_back(1);
					u->bound = bound(u);
					if(u->bound > INF)
						cout << u->level << " " << "INF" << " ";
					else
						cout << u->level << " " << u->bound << " ";
					for (k = 0; k < u->path.size() - 1; k++)
						cout << u->path[k] << " ";
					cout << u->path[k];
					cout << endl;
					if (lenght(u->path) < minlength) {
						minlength = lenght(u->path);
						opttour.resize(u->path.size());
						copy(u->path.begin(), u->path.end(), opttour.begin());
					}
				}
				else {
					u->bound = bound(u);
					if (u->bound > INF)
						cout << u->level << " " << "INF" << " ";
					else
						cout << u->level << " " << u->bound << " ";
					for (k = 0; k < u->path.size() - 1; k++)
						cout << u->path[k] << " ";
					cout << u->path[k];
					cout << endl;
					if (u->bound < minlength) {
						
						PQ.push(u);
					}
				}
			}
		}
	}
}

int main() {
	int u, v, w, minlenght=INF;
	ordered_set opttour;
	cin >> n >> m;
	W.resize(n + 1, vector<int>(n + 1, INF));

	for (int i = 0; i <= n; i++)
		W[i][i] = 0;

	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		W[u][v] = w;
	}

	travel2(opttour, minlenght);
	cout << minlenght << endl;
	int i;
	for (i = 0; i < opttour.size() - 1; i++)
		cout << opttour[i] << " ";
	cout << opttour[i];
}