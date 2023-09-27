#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    freopen("ghostin.txt", "r", stdin);
    freopen("ghostout.txt", "w", stdout);
    int N, K;
    // N is the number of ghosts, 1 / K is the speed 
    // cnt means how many times each K * X[i] - T[i] appears
    map<ll, int> cnt;
    scanf("%d%d", &N, &K);
    for (int i = 1; i <= N; ++i) {
        int x, t;
        scanf("%d%d", &x, &t);
        cnt[1ll * K * x - t]++;
    }

    // picking the most frequent number in cnt
    int ans = 0;
    for (auto &p : cnt) {
        ans = max(ans, p.second);
    }

    printf("%d\n", ans);
    return 0;
}