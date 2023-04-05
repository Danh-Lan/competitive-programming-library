#include <bits/stdc++.h>

using namespace std;

int n = 2e5; 
vector<vector<int>> graph(n, vector<int>());
vector<int> depth(n, 0);

void getDepth(int u, vector<bool>& vis) {
    if (vis[u]) return;
    vis[u] = true;

    for (int v : graph[u]) {
        if (!vis[v]) {
            depth[v] = depth[u] + 1;
            getDepth(v, vis);
        }
    }
}

// number of leaves wrt to the set of nodes 
int dfs(int u, vector<bool>& vis, vector<bool>& nodes) {
    if (vis[u]) return false;
    vis[u] = true;

    int leafCnt = 0;
    bool lower = false;
    for (int v : graph[u]) {
        if (!vis[v]) {
            leafCnt += dfs(v, vis, nodes);
            if (nodes[v]) lower = true;
        }
    }

    if (lower) nodes[u] = true;
    if (nodes[u] && !lower) leafCnt = 1;
    return leafCnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int tt = 1; 
    //cin>>tt;
    for (int test = 1; test <= tt; test++) {
        cin>>n;
        graph.resize(n);
        depth.resize(n);
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin>>u>>v;
            --u; --v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        vector<bool> vis(n, false);
        getDepth(0, vis);
        int q; cin>>q;
        for (int query = 0; query < q; ++query) {
            fill(vis.begin(), vis.end(), false);
            vector<bool> nodes(n, false);
            int k; cin>>k;
            int mx = 0;
            for (int i = 0; i < k; ++i) {
                int x; cin>>x;
                --x;

                if (depth[x] > depth[mx]) mx = x;
                nodes[x] = true;
            }

            int ans = dfs(mx, vis, nodes);
            if (ans == 1) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }

    return 0;
}