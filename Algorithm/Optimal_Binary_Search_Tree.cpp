#include <iostream>
#include <vector>
using namespace std;

typedef struct vector<vector<int>> mat;
typedef struct vector<int> v;

typedef struct node* node_ptr;

typedef struct node{
	node_ptr left;
	node_ptr right;
	int key;
}node_t;

int minimum(int s, int e, v& Pr, mat& A, int& mid) {
	int minval, prval=0, val;
	minval = 999999;
	for (int j = s; j <= e; j++)
		prval += Pr[j];
	for (int i = s; i <= e; i++) {
		val = A[s][i-1] + A[i + 1][e] + prval;
		if (minval > val) {
			minval = val;
			mid = i;
		}
	}
	return minval;
}

void OBST(int n, v P, mat& A, mat& Pa) {
	for (int i = 1; i <= n; i++) {
		A[i][i] = P[i];
		Pa[i][i] = i;
	}
	for (int dia = 1; dia <= n - 1; dia++) {
		for (int i = 1; i <= n-dia; i++) {
			int j = dia + i;
			int mid;
			A[i][j] = minimum(i, j, P, A, mid);
			Pa[i][j] = mid;
		}
	}
}
node_ptr create_node(int x) {
	node_ptr newNode = new node;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->key = x;
	return newNode;
}
node_ptr mktree(int s, int e, v& key, mat& P) {
	int k = P[s][e];
	if (k == 0)
		return NULL;
	else {
		node_ptr node = create_node(key[k]);
		node->left = mktree(s, k - 1, key, P);
		node->right = mktree(k + 1, e, key, P);
		return node;
	}
}
void inorder(node_ptr node, v&in) {
	if (node == NULL)
		return;
	if (node->left)
		inorder(node->left, in);
	if (node->key)
		in.push_back(node->key);
	if (node->right)
		inorder(node->right, in);
}

void preorder(node_ptr node, v &pre) {
	if (node == NULL)
		return;
	if (node->key)
		pre.push_back(node->key);
	if (node->left)
		preorder(node->left, pre);
	if (node->right)
		preorder(node->right, pre);
}
int main() {
	int n;
	cin >> n;
	v Pr(n + 1, 0);
	v K(n + 1, 0);
	mat Pa(n + 2, vector<int>(n + 2, 0));
	mat A(n + 2, vector<int>(n + 2, 0));

	for (int i = 1; i <= n; i++)
		cin >> K[i];
	for (int i = 1; i <= n; i++)
		cin >> Pr[i];

	OBST(n, Pr, A, Pa);

	int i, j;
	for (int i = 1; i <= n+1; i++) {
		for (j = i-1; j < n; j++) {
			cout << A[i][j] << " ";
		}
		cout << A[i][j]<<endl;
	}

	for (int i = 1; i <= n+1; i++) {
		for (j = i-1; j < n; j++) {
			cout << Pa[i][j] << " ";
		}
		cout << Pa[i][j]<<endl;
	}
	cout << A[1][n] << endl;
	
	node_ptr root = mktree(1, n, K, Pa);

	vector<int>in;
	vector<int>pre;

	preorder(root, pre);
	inorder(root, in);
	for (i = 0; i < pre.size() - 1; i++) {
		cout << pre[i] << " ";
	}
	cout << pre[i] << endl;
	for (i = 0; i < in.size() - 1; i++) {
		cout << in[i] << " ";
	}
	cout << in[i];

}