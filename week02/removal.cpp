#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;

char s[MAX_SIZE];


/*

    5
    01111001
    0000
    111111
    101010101
    011011110111

    4
    0
    6
    3
    6
*/

int main() {
    int T, N;
    scanf("%d", &T);
    while (T-- > 0) {
        int cnt = 0;
        scanf("%s", s + 1);
        N = strlen(s + 1);
        vector<int> group;
        for (int i = 1; i <= N; ++i) {
            if (s[i] == '1') {
                cnt++;
            } else {
                if (cnt > 0) {
                    group.push_back(cnt); 
                }
                cnt = 0;
            }
        }

        if (cnt > 0) {
            group.push_back(cnt);
        }

        sort(group.begin(), group.end(), greater<int>());

        int ans = 0;
        for (int i = 0 ; i < (int) group.size(); i = i + 2) {
            ans += group[i];
        }

        printf("%d\n", ans);
    }
    return 0;
}