#include <bits/stdc++.h>

using namespace std;

int dp[16][(1 << 15) + 1];
int g[16][16];
int sm[16][(1 << 15) + 1];
char ss[111];
int N;
vector<int> rowbit;

void init() {
    rowbit.clear();
    for (int i = 0 ; i < N; ++i) {
        for (int j = 0 ; j < (1 << N); ++j) {
            sm[i][j] = 0;
            dp[i][j] = -100000000;
        }
    }
}



int main() {
    int i, j, k;
    while (fgets(ss, 111, stdin) != NULL) {
        // parse and read in the grid
        // you don't need to do something similar for the course
        N = 0;
        int curr = 0;
        for (i = 0 ; i < (int) strlen(ss); ++i) {
            if (ss[i] == ' ' || ss[i] == '\n') {
                g[0][N++] = curr;
                curr = 0;
            } else {
                curr = curr * 10 + (ss[i] - '0');
            }
        }

        for (i = 1; i < N; ++i) {
            for (j = 0; j < N; ++j) {
                scanf("%d", &g[i][j]);
            }
        }

        getchar();
        getchar();
        // assume now N is the size of the grid
        // g[i][j] stores the integer on the i-th row and j-th column of the grid
        // we do problem solving here
        init();
        
        for (i = 0; i < N; ++i) {
            // sm[i][mask] = sum(g[i][k], (mask >> k) & 1 == 1)
            for (j = 0; j < (1 << N); ++j) {
                for (k = 0 ; k < N; ++k) {
                    if (((j >> k) & 1) == 1) {
                        sm[i][j] += g[i][k];
                    }
                }
            }
        }

        // get the valid bitmasks
        // rowbit stores only the valid bitmask
        for (i = 0 ; i < (1 << N); ++i) {
            // take i & (i << 1)
            if ((i & (i << 1)) == 0) rowbit.push_back(i);
        }

        // calculate the base case
        for (auto &bt : rowbit) {
            dp[0][bt] = sm[0][bt];
        }


        for (i = 1; i < N; ++i) {
            // we want to calculate dp[i][m]
            for (auto &m : rowbit) {
                // iterate through all the possible bitmask of row i-1
                for (auto &mp : rowbit) {
                    if (m & mp) continue;
                    if ((m << 1) & mp) continue;
                    if (m & (mp << 1)) continue;
                    dp[i][m] = max(dp[i][m], dp[i-1][mp] + sm[i][m]);
                }
            }
        }

        int ans = 0;
        for (auto &m : rowbit) {
            ans = max(dp[N-1][m], ans);
        }

        printf("%d\n", ans);
    }

    return 0;
}