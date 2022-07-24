#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#define MAX 5000000
using namespace std;

typedef struct elements {
	int n;
	vector<int> pnums;
}element;

vector<int> net(MAX+1, 0);

int main() {
	ios_base::sync_with_stdio(false);
	int N; cin >> N;
	vector<element> v(N);
	vector<int>primes;
	
	for (int i = 2; i <= MAX; i++) {
		net[i] = i;
	}
	for (int i = 2; i <= sqrt(MAX); i++) {
		if (net[i] == i) {
			for (int j = i*i; j <= MAX; j+=i) {
				if (net[j] == j)
					net[j] = i;
			}
		}
	}

	for (int i = 0; i < N; i++)
		cin >> v[i].n;

	for (int i = 0; i < N; i++) {
		int num = v[i].n;
		while (num > 1) {
			if (num % net[num] == 0) {
				cout << net[num] << " ";
				num /= net[num];
			}
		}
		cout << '\n';
	}

}