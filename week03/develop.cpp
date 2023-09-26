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

int main() {
    
    return 0;
}