#include <iostream>
#include <vector>
#include <algorithm>
#define INF 10001
using namespace std;

int binSize;
int n;
vector<int> items;

int optimalBin = 0;

void binPacking(vector<int> items, int n) {
	int s, e;
	int itemSize = items.size();
	s = 0;
	e = itemSize - 1;
	while (s <= e) {
		if (items[s] + items[e] <= binSize)
			e--;
		s++;
		optimalBin++;
	}
}

int main() {
	cin >> n >> binSize;
	items.resize(n);
	for (int i = 0; i < n; i++) 
		cin >> items[i];

	sort(items.rbegin(), items.rend());

	binPacking(items, n);

	cout << optimalBin;

}