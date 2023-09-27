#include <bits/stdc++.h>
#define MAX_SIZE 524312
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
using namespace std;

// f[i] stores the father node of i in the union-find
int f[MAX_SIZE];
// id[i] is the index of team i in the range tree
int id[MAX_SIZE];
// visited[index] means every nodes in the subtree of index have been merged into a single CC
int visited[MAX_SIZE];
int N, Q;

// find the great parent of node x
int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

// merge node x with node y
void unionset(int x, int y) {
    int fx = find(x), fy = find(y);
    f[fx] =  fy;
}

void build(int l, int r, int index) {
    // all nodes in the tree belongs to a size-1 connected component
    f[index] = index;
    if (l == r) {
        // the index of team l in the range tree
        id[l] = index;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
}

// merge all nodes in the subtree of index
// [1, 5] is the range we want to merge
// merge [1, 5] with [1, 3], [1, 5] with [4, 5]
// merge [1, 3] with [1, 2], [1, 3] with [3]
// merge [4, 5] with [4], [4, 5] with [5]
// merge [1, 2] with [1] and [1, 2] with 2
void pushdown(int l, int r, int index) {
    // if the range is invalid l > r return
    // if the range has already been merged in previous queries, return
    if (l > r || visited[index]) return;
    // set visited[index] to true, means [l, r] has been merged into a single CC
    visited[index] = 1;
    if (l == r) return;
    // merge [l, r] with [l, MID] and [l, r] with [MID + 1, r]
    unionset(index, LEFT);
    unionset(index, RIGHT);
    // recursively merge until we reach the leaf
    pushdown(l, MID, LEFT);
    pushdown(MID + 1, r, RIGHT);
}

// merge idx with range [start, end] in the range tree
void update(int start, int end, int l, int r, int index, int idx) {
    if (start > end || l > r || start > r || l > end) return;
    if (start <= l && r <= end) {
        // merge idx with the range [l, r], call unionset idx with index
        unionset(idx, index);
        pushdown(l, r, index);
        return;
    }

    // normal range tree search
    if (end <= MID) {
        update(start, end, l, MID, LEFT, idx);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, idx);
    } else {
        update(start, end, l, MID, LEFT, idx);
        update(start, end, MID + 1, r, RIGHT, idx);
    }
}

int main() {
    scanf("%d%d", &N, &Q);
    build(1, N, 1);
    while (Q-- > 0) {
        int tp, x, y;
        scanf("%d%d%d", &tp, &x, &y);
        if (tp == 1) {
            // merge team x with team y
            unionset(id[x], id[y]);
        } else if (tp == 2) {
            // merge team x with the range [x+1, y]
            update(x + 1, y, 1, N, 1, id[x]);
        } else {
            // check if team x and y are in the same CC
            printf("%s\n", find(id[x]) == find(id[y]) ? "YES" : "NO");
        }
    }
    return 0;
}