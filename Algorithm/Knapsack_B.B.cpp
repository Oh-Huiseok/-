#include <iostream>
#include <queue>
#include <vector>
#include<algorithm>
using namespace std;

typedef struct node* node_ptr;
typedef struct item* item_ptr;

typedef struct item {
	int weight;
	int profit;
	double profit_per_weight;
} item_t;

typedef struct node {
	int level;
	int weight;
	int profit;
	float bound;
} node_t;

struct compare {
	bool operator()(node_ptr u, node_ptr v) {
		if (u->bound < v->bound)
			return true;
		return false;
	}
};

typedef priority_queue<node_ptr, vector<node_ptr>, compare> priority_queue_of_node;


int n, W;
int maxprofit;
vector<item_t> items;

float bound(node_ptr u) {
	int j, k, totweight;
	float result;

	if (u->weight >= W)
		return 0;
	else {
		result = u->profit;
		j = u->level + 1;
		totweight = u->weight;
		while (j <= n && totweight + items[j].weight <= W) {
			totweight += items[j].weight;
			result += items[j].profit;
			j++;
		}
		k = j;
		if (k <= n)
			result += (W - totweight) * ((float)items[k].profit / items[k].weight);
		return result;
	}
}

node_ptr create_node(int level, int weight, int profit) {
	node_ptr v = (node_ptr)malloc(sizeof(node_t));
	v->level = level;
	v->weight = weight;
	v->profit = profit;
	v->bound = bound(v);
	return v;
}

bool compare_item(item_t i, item_t j) {
	if (i.profit_per_weight > j.profit_per_weight) {
		return true;
	}
	return false;
}


void ksnapsck6() {
	priority_queue_of_node PQ;
	node_ptr u, v;
	maxprofit = 0;
	PQ.push(create_node(0, 0, 0));
	v = PQ.top();
	cout << v->level << " " << v->weight << " " << v->profit << " " << v->bound << '\n';
	while (!PQ.empty()) {
		v = PQ.top();
		PQ.pop();
		if (v->bound > maxprofit) {
			u = create_node(v->level + 1, v->weight + items[v->level + 1].weight, v->profit + items[v->level + 1].profit);
			cout << u->level << " " << u->weight << " " << u->profit << " " << u->bound << '\n';
			if (u->weight <= W && u->profit > maxprofit)
				maxprofit = u->profit;
			if (u->bound > maxprofit)
				PQ.push(u);
			u = create_node(v->level + 1, v->weight, v->profit);
			cout << u->level << " " << u->weight << " " << u->profit << " " << u->bound << '\n';
			if (u->bound > maxprofit)
				PQ.push(u);
		}
	}
}


int main() {
	cin >> n >> W;
	items.resize(n + 1);

	for (int i = 1; i <= n; i++)
		cin >> items[i].weight;
	for (int i = 1; i <= n; i++)
		cin >> items[i].profit;
	for (int i = 1; i <= n; i++)
		items[i].profit_per_weight = (float)items[i].profit / items[i].weight;

	sort(items.begin()+1, items.end(), compare_item);

	ksnapsck6();
	cout << maxprofit;
}