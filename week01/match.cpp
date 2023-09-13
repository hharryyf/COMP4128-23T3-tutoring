#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

/*
    4 2
    1 3 3 7

    2

    5 5
    10 9 5 8 7

    1
*/

int x[MAX_SIZE];
int N, Z;

bool check(int K) {
    for (int i = 1; i <= K; ++i) {
        if (i + N - K > N) return false;
        if (x[i+N-K] - x[i] < Z) return false;
    }

    return true;
}

int main() {
    int i;
    scanf("%d%d", &N, &Z);
    for (i = 1; i <= N; ++i) scanf("%d", &x[i]);
    sort(x + 1, x + 1 + N);
    int low = 1, high = N / 2, ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            low = mid + 1;
            ans = mid;
        } else {
            high = mid - 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}