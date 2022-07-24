#include <iostream>
#include <vector>
using namespace std;
int n;
void partition(int low, int high, int& pivotpoint, vector<int>& S) {
    int pivotitem = S[low];

    int j = low;
    for (int i = low + 1; i <= high; i++) {
        if (S[i] < pivotitem) {
            j++;
            swap(S[j], S[i]);
        }
    }
    pivotpoint = j;
    swap(S[low], S[pivotpoint]);

    for (int i = 1; i <= n; i++)
        cout << S[i] << " ";
    cout << endl;
}
void quicksort(int low, int high, vector<int>& S) {
    int pivotpoint;

    if (low < high) {
        partition(low, high, pivotpoint, S);
        quicksort(low, pivotpoint - 1, S);
        quicksort(pivotpoint + 1, high, S);
    }
}
int main() {
    cin >> n;
    vector <int>S(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> S[i];

    quicksort(1, n, S);

    for (int i = 1; i <= n; i++)
        cout << S[i] << " ";
}