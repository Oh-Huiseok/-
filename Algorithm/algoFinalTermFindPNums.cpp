#include <iostream>
#include <vector>
#include <set>
#include <math.h>
#define MAX 5000000
using namespace std;

vector<int> net(MAX + 1, 0);

int main() {
	ios_base::sync_with_stdio(false);

	for (int i = 2; i <= MAX; i++) {
		net[i] = i;
	}
	for (int i = 2; i <= sqrt(MAX); i++) {
		if (net[i] == i) {
			for (int j = i * i; j <= MAX; j += i) {
				if (net[j] == j)
					net[j] = i;
			}
		}
	}// 4에 2, 6에 2, 8에 2... 9에 3 15에 3 .... 각 숫자마다 최소의 소인수 보유.

	int s, e, chk;
	int cnt = 0;
	set<int>pnums;

	cin >> s >> e;

	for (int i = s; i <= e; i++) {
		if (i != net[i]) { // 소수 아니면
			int num = i;
			chk = 0;
			pnums.clear();
			while (num > 1) {
				auto it = pnums.find(net[num]);
				if (it == pnums.end()) { // 인수가 pnums에 없으면
					pnums.insert(net[num]);
					chk++;
				}
				if (chk == 4)
					break;
				num /= net[num];
			}
			if (chk == 3) {
				cnt += 1;/*
				cout << i << endl;
				for (int x : pnums)
					cout << x << " ";
				cout << endl;*/
			}
		}
	}

	cout << cnt;
	
}   