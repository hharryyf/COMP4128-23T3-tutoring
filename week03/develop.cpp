#include <bits/stdc++.h>
#define MAX_SIZE 1048597
#define MAX_V 300000
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
using namespace std;

struct segt {
    int val, lz;
};

segt tree[MAX_SIZE];

int N;

vector<pair<int, int>> add[MAX_V + 5];
vector<pair<int, int>> del[MAX_V + 5];

int p[MAX_SIZE][3];

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (l != r) {
        tree[LEFT].val += tree[index].lz;
        tree[RIGHT].val += tree[index].lz;
        tree[LEFT].lz += tree[index].lz;
        tree[RIGHT].lz += tree[index].lz;
    }

    tree[index].lz = 0;
}

// add val to range [start, end] in the range tree
void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].val += val;
        tree[index].lz += val;
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, val);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, val);
    } else {
        update(start, end, l, MID, LEFT, val);
        update(start, end, MID + 1, r, RIGHT, val);
    }

    tree[index].val = max(tree[LEFT].val, tree[RIGHT].val);
}

// find_max function is going to return (maximum value in the range, index)
pair<int, int> find_max(int l, int r, int index) {
    if (l == r) return make_pair(tree[index].val, l);
    pushdown(l, r, index);
    if (tree[LEFT].val >= tree[RIGHT].val) return find_max(l, MID, LEFT);
    return find_max(MID + 1, r, RIGHT);
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        // l[i] = p[i][0], v[i] = p[i][1], r[i] = p[i][2]
        scanf("%d%d%d", &p[i][0], &p[i][1], &p[i][2]);
    }

    // each rectangle has lower left corner (l[i], v[i]), and upper right corner (v[i], r[i])
    for (i = 1; i <= N; ++i) {
        // add 1 to ranges (l[i], v[i]) at y coordinate v[i]
        add[p[i][1]].emplace_back(p[i][0], p[i][1]);
        // subtract 1 to ranges (l[i], v[i]) at y coordinate r[i]
        del[p[i][2]].emplace_back(p[i][0], p[i][1]);
    }

    int L = -1, R = -1, ans = 0;
    // i is the y-coordinate
    for (i = 1; i <= MAX_V; ++i) {
        // add events
        for (auto &e : add[i]) {
            update(e.first, e.second, 1, MAX_V, 1, 1);           
        }   

        auto curr = find_max(1, MAX_V, 1);
        if (curr.first > ans) {
            ans = curr.first;
            L = curr.second;
            R = i;
        }

        // delete events
        for (auto &e : del[i]) {
            update(e.first, e.second, 1, MAX_V, 1, -1);
        }
    }

    printf("%d\n", ans);
    for (i = 1; i <= N; ++i) {
        if (L >= p[i][0] && R <= p[i][2] && L <= p[i][1] && p[i][1] <= R) {
            printf("%d ", i);
        }
    }
    return 0;
}