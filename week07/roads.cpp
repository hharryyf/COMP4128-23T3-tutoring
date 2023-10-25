#include <bits/stdc++.h>
#define MAX_SIZE 311
using namespace std;
typedef long long ll;

ll dist[MAX_SIZE][MAX_SIZE];
int N, K;

int main() {
    int i, j, k;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            scanf("%lld", &dist[i][j]);
        }
    }

    // dist[i][j] stores the shortest distance between i and j
    // Floyd algorithm
    for (k = 1; k <= N; ++k) {
        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= N; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    scanf("%d", &K);
    while (K-- > 0) {
        int a, b;
        ll c;
        scanf("%d%d%lld", &a, &b, &c);
        // consider how e(a, b, c) affects the shortest distance between (i, j)
        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= N; ++j) {
                dist[i][j] = min(dist[i][j], min(dist[i][a] + dist[b][j] + c, dist[i][b] + dist[a][j] + c));
            }
        }

        ll ans = 0;
        for (i = 1; i <= N; ++i) {
            for (j = i + 1; j <= N; ++j) {
                ans = ans + dist[i][j];
            }
        }

        printf("%lld\n", ans);
    }
    return 0;
}