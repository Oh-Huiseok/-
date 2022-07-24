#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

typedef struct item* item_ptr;

typedef struct item {
	int weight;
	int profit;
	double profit_per_unit;
} item_t;

bool compare_item(item_t i, item_t j) {
	if (i.profit_per_unit > j.profit_per_unit) {
		return true;
	}
	return false;
}

void knapsack (int n, int& maxprofit, int& totweight, vector<item_t> items, int W, vector<item_ptr> &t) {
	maxprofit = totweight = 0;
	for (int i = 1; i <= n; i++) {
		if (totweight + items[i].weight <= W) {
			maxprofit += items[i].profit;
			totweight += items[i].weight;
			item_ptr tmp = new item_t;
			tmp->profit = items[i].profit, tmp->weight = items[i].weight;
			t.push_back(tmp);
		}
		else {
			if (totweight == W)
				break;
			item_ptr tmp = new item_t;
			tmp->profit = (W - totweight) * items[i].profit_per_unit;
			tmp->weight = (W - totweight);
			t.push_back(tmp);

			maxprofit += (W - totweight) * items[i].profit_per_unit;
			totweight += (W - totweight);
			break;
		}
	}
}

int main() {
	int n; cin >> n;
	vector<item_t> items(n + 1);

	for (int i = 1; i <= n; i++) {
		cin >> items[i].weight;
	}
	for (int i = 1; i <= n; i++) {
		cin >> items[i].profit;
		items[i].profit_per_unit = (double)items[i].profit / (double)items[i].weight;
	}
	
	sort(items.begin()+1, items.end(), compare_item);
	
	int bn; cin >> bn;
	vector<int> bw(bn+1);
	for (int i = 1; i <= bn; i++)
		cin >> bw[i];

	vector<vector<item_ptr>> res(bn+1);
	vector<int>maxprofit(bn + 1);
	for (int i = 1; i <= bn; i++) {
		int maxp, totw;
		vector<item_ptr> t;
		knapsack(n, maxp, totw, items, bw[i],t);
		maxprofit[i] = maxp;
		res[i] = t;
	}
	int j;
	for (int i = 1; i <= bn; i++) {
		cout << maxprofit[i] << endl;
		for (j = 0; j < res[i].size()-1; j++) {
			cout << res[i][j]->weight << " " << res[i][j]->profit<<endl;
		}
		cout << res[i][j]->weight << " " << res[i][j]->profit;
		if (i < bn)
			cout << endl;
	}
}