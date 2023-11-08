#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define MAX_SIZE 211

struct Maxflow {
    const ll INF = 100000000000ll;
    struct edge {
    	int from, to;
    	ll flow, capacity;
    };
    
    // start and end point
    int s, t;
    
    // list array
    vector<edge> edg;
    
    // g reference to the ith vertex's edges
    vector<int> g[MAX_SIZE];
    
    // distance array and visited array
    int dist[MAX_SIZE], visited[MAX_SIZE];
    int cur[MAX_SIZE];
    
    void init() {
    	edg.clear();
    	int i;
    	for (i = 0 ; i < MAX_SIZE; i++) {
    		g[i].clear();
    	}
    }
    
    void addedge(int from, int to, ll capacity) {
    	edge e1 = edge{from, to, 0ll, capacity};
    	edge e2 = edge{to, from, 0ll, 0ll};
    	edg.push_back(e1), edg.push_back(e2);
    	g[from].push_back((int) edg.size() - 2);
    	g[to].push_back((int) edg.size() - 1);
    }
    
    // construct the level graph
    bool bfs() {
    	memset(visited,0,sizeof(visited));
    	memset(dist,0,sizeof(dist));
    	queue<int> q;
    	q.push(s);
    	visited[s] = 1;
    	dist[s] = 0;
    	while (!q.empty()) {
    		int v = q.front();
    		q.pop();
    		for (int i = 0 ; i < (int) g[v].size(); i++) {
    			edge &e = edg[g[v][i]];
    			int nxt = e.to;
    			if (!visited[nxt] && e.capacity > e.flow) {
    				dist[nxt] = dist[v] + 1;
    				q.push(nxt);
    				visited[nxt] = 1;
    			}  
    		}
    	}
    	
    	return visited[t];
    }
    
    ll dfs(int x, ll cp) {
    	if (x == t || cp == 0) {
    		return cp;
    	}
    	
    	ll flow = 0, newflow;
    	for (int &y = cur[x]; y < (int) g[x].size(); y++) {
    		edge &e = edg[g[x][y]];
    		if (dist[x] + 1 == dist[e.to]) {
    			ll minn = min(cp, e.capacity - e.flow);
    			newflow = dfs(e.to, minn);
    			if (newflow > 0) {
    				e.flow += newflow;
    				edg[g[x][y] ^1].flow -= newflow;
    				flow += newflow;
    				cp -= newflow;
    				
    				if (cp == 0) {
    					break;
    				}
    			}
    		}
    	}
    	
    	return flow;
    }
    
    ll Dinic(){
        ll flow=0;
        while(bfs()){
            memset(cur,0,sizeof(cur));
            flow += dfs(s,INF);
        }
        return flow;
    }
};

Maxflow mf;
int N, M;
int a[MAX_SIZE], b[MAX_SIZE];
ll ans[MAX_SIZE][MAX_SIZE];


int main() {
    int i;
    ll sm = 0, sm2 = 0;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        sm = a[i] + sm;
    }

    for (i = 1; i <= N; ++i) {
        scanf("%d", &b[i]);
        sm2 += b[i];
    }

    mf.s = 0, mf.t = MAX_SIZE - 1;

    for (i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        mf.addedge(u, v + N, mf.INF);
        mf.addedge(v, u + N, mf.INF);
    }

    for (i = 1; i <= N; ++i) {
        mf.addedge(mf.s, i, a[i]);
        mf.addedge(i + N, mf.t, b[i]);
        mf.addedge(i, i + N, mf.INF);
    }

    if (sm != sm2 || sm != mf.Dinic()) {
        printf("NO\n");
    } else {
        printf("YES\n");
        for (auto &e : mf.edg) {
            // e.flow means the total amount of flow between e.from to e.to
            if (e.from >= 1 && e.from <= N && e.to > N && e.to <= 2 * N) {
                ans[e.from][e.to - N] = e.flow;
            }
        }

        for (i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                printf("%lld ", ans[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}