#include <iostream>
#include <vector>
#define MAX 200000
using namespace std;

vector<unsigned long long int> B(MAX+1, -1);

int binom(int n, int k) {
	int a, b;
	for (int i = 0; i <= n; i++) {
		int min = i > k ? k : i;
		a = B[0];
		for (int j = 0; j <= min; j++) {
			if (j == 0)
				B[j] = 1;
			if(i==j || j==1)
				B[j] = 2;
			else {
				b = B[j];
				B[j] = a + b;
				a = b;
			}
			
			cout<< B[j] << endl;
		}
	}
	return B[k];
}

int main() {
	int n, k;
	cin >> n >> k;
	cout << binom(n, k);
}