#include<iostream>
#include<vector>
#include<algorithm>
#define MAX(x, y) x > y ? x : y

using namespace std;

typedef struct {
	int s;
	int e;
}conf;

bool compare(const conf& a, const conf& b) {
	return a.e < b.e;
}

int main() {
	int n;
	cin >> n;
	vector<conf> arr(n);
	for (int i = 0; i < n; i++) {
		int s, e;
		cin >> s >> e;
		arr[i].s = s;
		arr[i].e = e;
	}

	sort(arr.begin(), arr.end(), compare);
	for (conf x : arr)
		cout << x.s << " " << x.e << endl;

	int cnt=1;
	int s, e;
	//cout << endl;
	/*if (arr[0].s == arr[0].e)
		cnt--;*/
	e = arr[0].e;
	for (int i = 1; i < n; i++) {
		if (e <= arr[i].s) {
			cnt++;
			e = arr[i].e;
		}
	}
	cout << cnt;
}
