#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
typedef vector<vector<int>> mat;

typedef struct node* node_ptr;
typedef struct node {
	char symbol;
	int frequency;
	node_ptr left;
	node_ptr right;
}node_t;

struct compare {
	bool operator()(node_ptr p, node_ptr q) {
		return p->frequency > q->frequency;
	}
};

typedef priority_queue <node_ptr, vector<node_ptr>, compare> PriorityQueue;

int SIZE = 0;

node_ptr create_node(char symbol, int frequency) {
	node_ptr N = new node_t;
	N->symbol = symbol;
	N->frequency = frequency;
	N->left = NULL;
	N->right = NULL;
	return N;
}

void huffman(int n, PriorityQueue& PQ) {
	for (int i = 1; i <= n - 1; i++) {
		node_ptr p = PQ.top(); 
		PQ.pop();
		node_ptr q = PQ.top();
		PQ.pop();
		node_ptr r = create_node(' ', (p->frequency + q->frequency));
		r->left = p;
		r->right = q;
		PQ.push(r);
		SIZE += 1;
	}
}

void decode(node_ptr root, vector<int>& code, map<char, vector<int>>& decoder) {
	if (root->symbol != ' ') {
		vector<int> ret;
		ret.resize(code.size());
		copy(code.begin(), code.end(), ret.begin());
		decoder.insert(make_pair(root->symbol, ret));
	}
	else if (root != NULL) {
		code.push_back(0);
		decode(root->left, code, decoder);
		code.pop_back();
		code.push_back(1);
		decode(root->right, code, decoder);
		code.pop_back();
	}
}

void inorder(node_ptr node, int& chk, int size) {
	if (node == NULL)
		return;
	if (node->left)
		inorder(node->left, chk, size);
	if (node->symbol == ' ') {
		cout << "+:" << node->frequency;
		if (chk < size) {
			cout << " ";
			chk += 1;
		}
	}
	else if(node->symbol != ' ') {
		cout << node->symbol << ":" << node->frequency;
		if (chk < size) {
			cout << " ";
			chk += 1;
		}
	}
	if (node->right)
		inorder(node->right, chk, size);
}

void preorder(node_ptr node, int& chk, int size) {
	if (node == NULL)
		return;
	if (node->symbol == ' ') {
		cout << "+:" << node->frequency;
		if (chk < size) {
			cout << " ";
			chk += 1;
		}
	}
	else if(node->symbol != ' ') {
		cout << node->symbol << ":" << node->frequency;
		if (chk < size) {
			cout << " ";
			chk += 1;
		}
	}
	if (node->left)
		preorder(node->left, chk, size);
	if (node->right)
		preorder(node->right, chk, size);
}
int main() {
	int n; cin >> n;
	char c[100];
	for (int i = 1; i <= n; i++)
		cin >> c[i];
	int F[500];
	for (int i = 1; i <= n; i++)
		cin >> F[i];
	PriorityQueue PQ;
	for (int i = 1; i <= n; i++) {
		node_ptr nd = create_node(c[i], F[i]);
		PQ.push(nd);
	}
	huffman(n, PQ);
	
	node_ptr root = PQ.top();

	vector<int> code;
	map<char, vector<int>> decoder;
	decode(root, code, decoder);
	
	int n1; cin >> n1;
	vector<string> S(n1);
	for (int i = 0; i < n1; i++) {
		cin >> S[i];
	}

	int n2;  cin >> n2;
	vector<vector<int>> R(n2);
	for (int i = 0; i < n2; i++) {
		string stmp;
		cin >> stmp;
		vector<int> vtmp(stmp.size());
		for (int j = 0; j < stmp.size(); j++) {
			vtmp[j] = stmp[j] - 48;
		}
		R[i] = vtmp;
	}

	SIZE += n;

	int cnt = 0;
	preorder(root, cnt, SIZE);
	cout << endl;

	cnt = 0;
	inorder(root, cnt, SIZE);
	cout << endl;

	for (int i = 0; i < S.size(); i++) {
		for (char c : S[i]) {
			auto code = decoder.find(c);
			for (int i : code->second)
				cout << i;
		}
		cout << endl;
	}

	vector<vector<char>> C(n2);
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < R[i].size(); j++) {
			for (auto k : decoder) {
				int cnt = 0;
				for (int q = 0; q < k.second.size(); q++)
					if (j + q < R[i].size() && R[i][j + q] == k.second[q])
						cnt++;
				if (cnt == k.second.size()) {
					C[i].push_back(k.first);
					j += k.second.size() - 1;
					break;
				}
			}
		}
	}

	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < C[i].size(); j++) {
			cout << C[i][j];
		}
		if (i != n2 - 1)
			cout << endl;
	}
    
	
	/*
	for (auto k : decoder) {
		cout << k.first << " ";
		for (int q : k.second)
			cout << q;
		cout << endl;
	}*/
	
}