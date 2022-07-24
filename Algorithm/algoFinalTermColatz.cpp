#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int main() {
	int s, e;
	int cnt = 0;
	cin >> s >> e;

	set<int> colatz;

	for (int i = s; i <= e; i++) {
		int num = i;
		colatz.clear();
		while (1) {
			if (count(colatz.begin(), colatz.end(), num)) {
				if (num != 2)
					cnt += 1;
				break;
			}
			else {
				cout << num << " ";
				colatz.insert(num);
				if (num % 2 == 0)
					num /= 2;
				else 
					num = num * 3 - 1;
				
			}
		}
		cout << endl;
	}
	cout << cnt;
} // 순환을 하면 마지막에 1로 안끝남.