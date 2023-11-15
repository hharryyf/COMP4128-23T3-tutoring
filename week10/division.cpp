#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        ll A, B;
        scanf("%lld%lld", &A, &B);
        vector<pair<ll, int>> prime;
        ll tmp = B;
        for (ll i = 2; i * i <= B; ++i) {
            int cnt = 0;
            while (tmp % i == 0) {
                cnt++;
                tmp /= i;
            }

            if (cnt > 0) prime.emplace_back(i, cnt);
        }

        if (tmp > 1) prime.emplace_back(tmp, 1);

        if (A % B == 0) {
            ll ans = 0;
            // M * p1 ^ (d1 - 1) * p2 ^ c2 * p3 ^ c3 * ...
            for (auto &p : prime) {
                tmp = A;
                while (tmp % p.first == 0) tmp /= p.first;
                for (int i = 1; i < p.second; ++i) {
                    tmp = tmp * p.first;
                }

                ans = max(ans, tmp);
            }

            printf("%lld\n", ans);
        } else {
            printf("%lld\n", A);
        }
    }
    return 0;
}