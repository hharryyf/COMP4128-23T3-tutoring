#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;
typedef long long ll;

struct edge {
    // u, v means the end points of the edge
    int u, v;
    // c means the weight of the edge
    ll c;
    bool operator < (edge &other) const {
        return c < other.c;
    }
};

vector<edge> edg;

// line 19 - 34, you can copy directly, Union-find data structure
// father/root of point i
int f[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int fx = find(x), fy = find(y);
    f[fx] = fy;
}

void init() {
    for (int i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
}



int N;

int x[MAX_SIZE], y[MAX_SIZE], c[MAX_SIZE], k[MAX_SIZE];



int main() {
    init();
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d", &x[i], &y[i]);
    }   

    for (int i = 1; i <= N; ++i) scanf("%d", &c[i]);
    for (int i = 1; i <= N; ++i) scanf("%d", &k[i]);

    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            edg.push_back({i, j, 1ll * (k[i] + k[j]) * (abs(x[i] - x[j]) + abs(y[i] - y[j]))});
        }
    }

    for (int i = 1; i <= N; ++i) {
        edg.push_back({0, i, c[i]});
    }

    sort(edg.begin(), edg.end());

    // stores the connection between cities
    vector<pair<int, int>> conn;
    // stores the cities directly connected to power
    vector<int> pw;
    // ans is the minimum cost
    ll ans = 0;

    for (auto &e : edg) {
        // means e.u and e.v belong to different connected component
        // adding this edge will not create a cycle
        if (find(e.u) != find(e.v)) {
            ans += e.c;
            unionset(e.u, e.v);
            if (e.u == 0 || e.v == 0) {
                pw.push_back(e.u + e.v);
            } else {
                conn.emplace_back(e.u, e.v);
            }
        }
    }

    printf("%lld\n", ans);

    printf("%d\n", (int) pw.size());

    for (auto &p : pw) {
        printf("%d ", p);
    }

    printf("\n%d\n", (int) conn.size());

    for (auto &p : conn) {
        printf("%d %d\n", p.first, p.second);
    }

    return 0;
}