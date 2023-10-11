#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE];
// depth[v] is the depth of vertex v in the dfs tree of the graph
// f[v] is the parent node of v in the dfs tree
int depth[MAX_SIZE], f[MAX_SIZE];
int N, M, K;

void dfs(int v, int pre) {
    depth[v] = depth[pre] + 1;
    f[v] = pre;
    // (v, back_vertex) is a backedge in the dfs
    // we want to find the back_vertex connected to v that has the greatest depth
    int back_vertex = -1;

    for (auto nv : g[v]) {
        if (nv != pre) {
            // some vertex is connected to v and has been visited 
            if (depth[nv] > 0) {
                // nv is a back_vertex, (v, nv) is a backedge
                if (back_vertex == -1 || depth[back_vertex] < depth[nv]) {
                    back_vertex = nv;
                }
            }
        }
    }

    if (back_vertex != -1) {
        // we know we have a cycle without edges crossing in the middle
        int curr = v;
        vector<int> ret;
        while (curr != back_vertex) {
            ret.push_back(curr);
            curr = f[curr];
        }

        ret.push_back(curr);

        if ((int) ret.size() > K) {
            printf("1\n");
            for (int i = 0, j = 0 ; i < (int) ret.size() && j < (K + 1) / 2; i = i + 2, ++j) {
                printf("%d ", ret[i]);
            }
            printf("\n");
        } else {
            printf("2\n%d\n", (int) ret.size());
            for (auto v : ret) {
                printf("%d ", v);
            }

            printf("\n");
            
        }

        exit(0);
    }

    for (auto nv : g[v]) {
        if (depth[nv] == 0) {
            dfs(nv, v);
        }
    }
}

int main() {
    int i;
    // N vertices, M edges, K is the K in the problem statement
    scanf("%d%d%d", &N, &M, &K);    
    for (i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    vector<int> odd, even;

    for (i = 1; i <= N; ++i) {
        if (depth[i] % 2 == 1) {
            odd.push_back(i);
        } else {
            even.push_back(i);
        }
    }

    if (odd.size() < even.size()) {
        swap(odd, even);
    }

    printf("3\n");
    for (int i = 0, j = 0 ; i < (int) odd.size() && j < (K + 1) / 2; ++i, ++j) {
        printf("%d ", odd[i]);
    }
    printf("\n");

    return 0;
}