#include <bits/stdc++.h>

using namespace std;


int pre[3001][3001];

int rectangle(int R,int C,int H,int W,int Q[3001][3001]) {
    int i, j;
    for (i = R; i >= 1; --i) {
        for (j = C; j >= 1; --j) {
            Q[i][j] = Q[i-1][j-1];
        }
    }

    auto check = [&](int K) -> bool {
        for (i = 1; i <= R; ++i) {
            for (j = 1; j <= C; ++j) {
                if (Q[i][j] <= K) {
                    pre[i][j] = 1;
                } else {
                    pre[i][j] = -1;
                }
            }
        }

        for (i = 1; i <= R; ++i) {
            for (j = 1; j <= C; ++j) {
                pre[i][j] += pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
            }
        }

        for (i = H; i <= R; ++i) {
            for (j = W; j <= C; ++j) {
                if (pre[i][j] + pre[i-H][j-W] - pre[i-H][j] - pre[i][j-W] > 0) {
                    return true;
                }
            }
        }

        return false;
    };

    int ans = R * C, low = 1, high = R * C;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

int a[3001][3001];

int main() {
    int R, C, H, W, i, j;
    scanf("%d%d%d%d", &R, &C, &H, &W);
    for (i = 0; i < R; ++i) {
        for (j = 0 ; j < C; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("%d\n", rectangle(R, C, H, W, a));
    return 0;
}