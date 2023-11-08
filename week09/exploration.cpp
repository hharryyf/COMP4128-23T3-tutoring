#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define MAX_SIZE 1211

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

int V, E, N, K;
int team[MAX_SIZE];
ll dist[MAX_SIZE][MAX_SIZE];
// if the teams can end up in at least K cities if you are given T minutes
bool check(ll T) {
    int i;
    mf.init();
    mf.s = 0, mf.t = MAX_SIZE - 1;
    for (i = 1; i <= N; ++i) {
        // add an edge between source and the city that team i is located in
        mf.addedge(mf.s, team[i], 1);
    }

    // 1~V as the in nodes
    // V + 1 ~ 2V as the out nodes

    for (i = 1; i <= V; ++i) {
        // add an edge between the "out" node of city i and the sink
        mf.addedge(i + V, mf.t, 1);
    }

    for (i = 1; i <= V; ++i) {
        for (int j = 1; j <= V; ++j) {
            if (dist[i][j] <= T) {
                mf.addedge(i, j + V, mf.INF);
            }
        } 
    }

    return mf.Dinic() >= 1ll * K;
}

int main() {
    int i, j, k;
    scanf("%d%d%d%d", &V, &E, &N, &K);
    for (i = 1; i <= N; ++i) scanf("%d", &team[i]);
    for (i = 1; i <= V; ++i) {
        for (j = 1; j <= V; ++j) {
            if (i != j) {
                dist[i][j] = mf.INF;
            }
        }
    }

    for (i = 1; i <= E; ++i) {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    // Floyd algorithm for all-pair shortest path
    for (k = 1; k <= V; ++k) {
        for (i = 1; i <= V; ++i) {
            for (j = 1; j <= V; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int ans = -1, low = 0, high = 1731311;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}