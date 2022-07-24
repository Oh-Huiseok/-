#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> sequence_of_integer;

bool is_feasible(sequence_of_integer& k, sequence_of_integer& deadline) {
	for (int i = 1; i < k.size(); i++) {
		if (deadline[k[i]] < i)
			return false;
	}
	return true;
}

void schedule(int n, sequence_of_integer& deadline, sequence_of_integer& J) {
	sequence_of_integer K;
	J.clear();
	J.push_back(0);
	J.push_back(1);
	for (int i = 2; i <= n; i++) {
		K.resize(J.size());
		copy(J.begin(), J.end(), K.begin());
		int j = 1;
		while (j < K.size() && deadline[K[j]] <= deadline[i])
			j++;
		K.insert(K.begin() + j, i);
		if (is_feasible(K, deadline)) {
			J.resize(K.size());
			copy(K.begin(), K.end(), J.begin());
		}

	}
}

int main() {
	int n; cin >> n;
	sequence_of_integer deadline(n + 1);
	sequence_of_integer J(n + 1);
	sequence_of_integer profit(n + 1);

	for (int i = 1; i <= n; i++)
		cin >> deadline[i];
	for (int i = 1; i <= n; i++)
		cin >> profit[i];

	schedule(n, deadline, J);
	int total = 0;
	for (int q : J)
		total += profit[q];
	
	cout << total << endl;

	for (int i = 1; i < J.size(); i++) {
		cout << profit[J[i]];
		if (i != J.size())
			cout << " ";
	}
}