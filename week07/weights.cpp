#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
typedef long long ll;

int N, M, A, B, C;

vector<int> g[MAX_SIZE];
ll p[MAX_SIZE];

// dist[0][v] = the shortest distance between A and v
// dist[1][v] = the shortest distance between B and v
// dist[2][v] = the shortest distance between C and v
ll dist[3][MAX_SIZE];
int visited[MAX_SIZE];

void BFS(int src, int dim) {
    int i;
    for (i = 1; i <= N; ++i) {
        dist[dim][i] = 1000000000000ll;
        visited[i] = 0;
    }

    queue<int> q;

    q.push(src);
    dist[dim][src] = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (visited[v]) continue;
        visited[v] = 1;
        for (auto nv : g[v]) {
            if (!visited[nv] && dist[dim][nv] > dist[dim][v] + 1) {
                dist[dim][nv] = dist[dim][v] + 1;
                q.push(nv);
            }
        }
    }
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d%d%d%d", &N, &M, &A, &B, &C);
        for (i = 1; i <= M; ++i) scanf("%lld", &p[i]);
        sort(p + 1, p + 1 + M);

        for (i = 1; i <= N; ++i) g[i].clear();

        for (i = 1; i <= M; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }

        BFS(A, 0);
        BFS(B, 1);
        BFS(C, 2);

        for (i = 1; i <= M; ++i) {
            p[i] = p[i-1] + p[i];
        }

        ll ans = 1e17;
        for (i = 1; i <= N; ++i) {
            // we iterate through the vertex i
            // i is the vertex v on the slide
            // we go from a -> v -> b -> v -> c
            // smallest dist(b, i) many edges from p as k2
            // smallest dist(a, i) + dist(b, i) + dist(c, i) many edges as k1/k2/k3
            if (dist[0][i] + dist[1][i] + dist[2][i] <= M) {
                ans = min(ans, p[dist[1][i]] + p[dist[0][i] + dist[1][i] + dist[2][i]]);
            }
        }

        printf("%lld\n", ans);
    }
    return 0;
}