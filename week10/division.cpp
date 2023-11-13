#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        ll A, B;
        scanf("%lld%lld", &A, &B);
        if (A % B != 0) {
            printf("%lld\n", A);
        }  else {
            vector<pair<ll, int>> prime;
            for (ll i = 2; i * i <= B; ++i) {
                if (B % i == 0) prime.emplace_back(i, 0);
            }

            for (auto &p : prime) {
                while (B % p.first == 0) {
                    B = B / p.first;
                    p.second += 1;
                }
            }

            if (B > 1) prime.emplace_back(B, 1);

            ll ans = 1;
            for (auto &p : prime) {
                ll tmp = A;
                while (tmp % p.first == 0) tmp /= p.first;
                for (int i = 1; i <= p.second - 1; ++i) tmp = tmp * p.first;
                ans = max(ans, tmp);
            }

            printf("%lld\n", ans);
        }
    }
    return 0;
}