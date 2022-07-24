#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<int>> mat;
typedef vector<int> v;

void lcs(int n, int m, string st1, string st2, mat& C, mat& P) {
	for (int i = 1; i <=n ; i++) {
		for (int j = 1; j <= m; j++) {
			
			if (st1[i] == st2[j]) {
				C[i][j] = C[i - 1][j - 1] + 1;
				P[i][j] = 1;
			}
			else {
				if (C[i][j - 1] > C[i - 1][j]) {
					C[i][j] = C[i][j - 1];
					P[i][j] = 2;
				}
				else {
					C[i][j] = C[i - 1][j];
					P[i][j] = 3;
				}
			}
		}
	}
}

void print(int i, int j, mat& P, string& str, string&res) {
	if (P[i][j] == 1) {
		res.push_back(str[i]);
		print(i - 1, j - 1, P, str, res);
	}
	else if (P[i][j] == 3) {
		print(i - 1, j, P, str, res);
	}
	else if (P[i][j] == 2) {
		print(i, j - 1, P, str, res);
	}
}

int main() {
	string str1, str2;
	cin >> str1 >> str2;
	
	string st1=" ", st2=" ";
	st1.append(str1);
	st2.append(str2);
	
	int n = st1.size();
	int m = st2.size();
	
	mat C(n, vector<int>(m, 0));
	mat P(n, vector<int>(m, 0));

	lcs(n-1, m-1, st1, st2, C, P);
	cout << C[n-1][m-1]<<endl;

	string res;
	print(n - 1, m - 1, P, st1, res);
	while (!res.empty()) {
		cout << res.back();
		res.pop_back();
	}
}