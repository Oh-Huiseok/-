#include <iostream>
#include <vector>
#include<map>
#include<algorithm>


using namespace std;

typedef struct item* temp_ptr;
typedef struct item {
	int id;
	int weight;
	int profit;
	int profit_per_unit;
}item_t;

int n, T, W;
vector<item_t>items;
map<pair<int, int>, int> P;

bool cmp_item(item_t i, item_t j) {
	if (i.profit_per_unit > j.profit_per_unit)
		return true;
	return false;
}

int knapsack(int n, int W, map<pair<int, int>, int> &P, vector<item_t>items) {
	if (n == 0 || W <= 0)
		return 0;

	int lval = (P.find(make_pair(n - 1, W)) != P.end()) ? P[make_pair(n - 1, W)] : knapsack(n - 1, W, P, items);
	int rval = (P.find(make_pair(n - 1, W - items[n].weight)) != P.end()) ? P[make_pair(n - 1, W)] : knapsack(n - 1, W - items[n].weight, P, items);
	P[make_pair(n, W)] = (items[n].weight > W) ? lval : max(lval, items[n].profit + rval);
	return P[make_pair(n, W)];
}

int main() {
	cin >> n;
	items.resize(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> items[i].weight;
	for (int i = 1; i <= n; i++)
		cin >> items[i].profit;
	for (int i = 1; i <= n; i++) {
		items[i].id = i;
		items[i].profit_per_unit = items[i].profit / items[i].weight;
	}

	sort(items.begin()+1, items.end(), cmp_item);

	cin >> T;
	vector<int> W;
	W.resize(T + 1);
	for (int i = 1; i <= T; i++)
		cin >> W[i];
	
	for (int i = 1; i <= T; i++) {
		cout << knapsack(n, W[i], P, items) << endl;
		int c = 0;
		for (auto k : P) {
			cout << k.first.first << " " << k.first.second << " " << k.second;
			if (c < P.size()-1)
				cout << endl;
			c += 1;
		}
		if (i < T)
			cout << endl;
		P.clear();
	}
}