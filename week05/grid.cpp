#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;
typedef long long ll;

struct edge {
    int u, v;
    ll c;
    bool operator < (edge &other) const {
        return c < other.c;
    }
};

vector<edge> edg;

int N;

int x[MAX_SIZE], y[MAX_SIZE], c[MAX_SIZE], k[MAX_SIZE];

int main() {
    
    return 0;
}