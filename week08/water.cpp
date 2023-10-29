#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MAX_SIZE 1048597
using namespace std;

int invalid = -1;

struct segt {
    int val, lz;
};

segt tree[MAX_SIZE];

vector<int> g[MAX_SIZE];
int sz[MAX_SIZE], id[MAX_SIZE], parent[MAX_SIZE], N;


int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }



    int Q;
    scanf("%d", &Q);
    while (Q-- > 0) {
        int tp, v;
        scanf("%d%d", &tp, &v);
        if (tp == 1) {
        
        } else if (tp == 2) {
        
        } else {
        
        }

    }
    return 0;
}