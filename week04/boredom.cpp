#include <bits/stdc++.h>
typedef long long ll;
// maximum possible number in the array a
#define MAX_SIZE 100011
using namespace std;

ll dp[MAX_SIZE];

int N, cnt[MAX_SIZE];

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0; i < N; ++i) {
        int v;
        scanf("%d", &v);
        cnt[v]++;
    }

    // base case
    dp[0] = 0;

    // general recursion
    for (i = 1; i < MAX_SIZE; ++i) {
        // i >= 2 ? dp[i-2] : 0 is to make sure you do not try to access dp[-1]
        dp[i] = max(dp[i-1], (i >= 2 ? dp[i-2] : 0) + 1ll * cnt[i] * i);    
    }

    printf("%lld\n", dp[MAX_SIZE - 1]);
    return 0;
}