#include <bits/stdc++.h>
#define MAX_SIZE 211
typedef long double ld;
using namespace std;

ld dp[MAX_SIZE][MAX_SIZE][2];

// Answer: 0.83648556

ld f(int i, int j, int turn) {
    if (i >= 100) return 1 - turn;
    if (j >= 100) return turn;
    if (dp[i][j][turn] != -1) return dp[i][j][turn];
    if (turn == 0) {
        return dp[i][j][turn] = (0.5 * (1 - f(i + 1, j, 1)) + 0.5 * (1 - f(i, j, 1)));
    } else {
        ld ans = 0;
        for (int t = 1; t <= 8; ++t) {
            ld score = f(i, j + (1 << (t - 1)), 0), p = 1.0 / (1 << t);
            ans = max(ans, (p * 2) / (1.0 + p) * (1 - score) + 1.0 * (1 - p) / (1 + p) * f(i + 1, j, 1));
        }

        return dp[i][j][turn] = ans;
    }
}

int main() {
    for (int i = 0 ; i < MAX_SIZE; ++i) {
        for (int j = 0 ; j < MAX_SIZE; ++j) {
            dp[i][j][0] = dp[i][j][1] = -1;
        }
    }
    printf("%.8Lf\n", 1 - f(0, 0, 0));
    return 0;
}