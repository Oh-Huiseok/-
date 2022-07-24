#include <iostream>
using namespace std;
typedef unsigned long long ull;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ull N, left, right;
    int testCase; cin >> testCase;
    for (int tc = 1; tc <= testCase; ++tc) {
        cin >> N;

        left = (N - 1) * (N - 1) * 2 + 1;
        right = N * N * 2 - 1;

        // 정답 출력
        printf("#%d %llu %llu\n", tc, left, right);
    }
}